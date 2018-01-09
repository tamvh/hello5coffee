#include "maincontroller.h"
#include "commonfunction.h"
#include "../common/prntdataformat.h"
#include "../common/configsetting.h"
#include <QDebug>
#include <QUrl>
#include <QThread>
#include <QMessageBox>
#include <QtConcurrent>
#include <QNetworkInterface>
#include <QGuiApplication>
#include <QJsonObject>
#include <QSet>
#ifdef Q_OS_ANDROID
#include <QtAndroidExtras>
#endif

// gia lap thanh toan zalopay
// http://dev.zing.vn:8585/vpos/payment/callback/?iv=1612140004

#define REBOOT_INTERVAL 5   // 5 minutes

MainController::MainController(QObject *parent)
    : QObject(parent)
    , deviceService(Q_NULLPTR)
    , m_tmCheckUpdateFood(this)
    , machineName("hello5coffee")
    , cardWaitingPay(false)
    , httpTranspro("")
    , m_progstatus(LOGIN_NONE)
    , m_fupdatestatus(FUPDATE_NONE)
    , wscssClient(Q_NULLPTR)
{
    cmd_apiitem         = QString("/api/item/?");
    cmd_appinvce        = QString("/api/invoice/");
    cmd_getlist         = QString("getlist");
    cmd_getsession      = QString("get_session");
    cmd_paymentsuccess  = QString("payment_success");
    cmd_getlastupdate   = QString("get_last_update");

    cmd_token = CommonFunction::gVPOS1();

    httppmsid = NULL;
    http2 = NULL;
    httpBaocao = NULL;

    wsClient = 0;
    deviceId = QString(QUuid::createUuid().toRfc4122().toHex());

    setting = new ConfigSetting(false, this);
    setTransferProtocol(setting->transProtocol, false);
    merchantCode = setting->appName;
    appTitle = setting->appTitle;

    if (!setting->dockServer.isEmpty()) {
        qDebug() << "Found dock server config: " << setting->dockServer;
        connectToDock(setting->dockServer);
    } else {
        qDebug() << "Not found dock server config, do auto scan Dock ...";
        doScanDockAutosetting();
    }

    httpfood = NULL;
    payZalo = NULL;
    httpcancel = NULL;

    m_qullLUT = 0;
    m_httpCheckUpdate = NULL;

    m_startTime = QDateTime::currentDateTimeUtc().toTimeZone(QTimeZone("Asia/Ho_Chi_Minh"));

    if( setting->rebootDate )
    {      
        QObject::connect(&m_rebootTimer, SIGNAL(timeout()), SLOT(timerReboot()));
        m_rebootTimer.start(REBOOT_INTERVAL * 60000);
    }


    initialWebSocket();
    initialWsCssClient();


    // catch event filter
    qGuiApp->installEventFilter(this);

    QObject::connect(&m_idleTimer, SIGNAL(timeout()), this, SLOT(timerSystemIdle()));
    m_idleTimer.start(3000); // 3000 = 3 second
    m_lastTimeActivity = QDateTime::currentMSecsSinceEpoch();
}

MainController::~MainController()
{
    if ( setting ) {
        delete setting;
    }

    m_tmCheckUpdateFood.stop();

    if (deviceService) {
        deviceService->stopService();
        delete deviceService;
    }

    if (wsClient)
    {
        wsClient->stop();
        wsClient->wait();
    }
}

bool MainController::isDebugmode()
{
#ifdef QT_DEBUG
    return true;
#endif

    return false;
}

bool MainController::isRaspberry()
{
#ifdef USE_VT_KB
    return true;
#endif

    return false;
}

void MainController::appQuit()
{
    qApp->quit();
}

QString MainController::getAccount()
{
    QList<QPair<QString, QString>> acclist;

    sortPairList(acclist);

    QJsonArray jsarr;
    QJsonObject jso;

    for (int i=0; i<acclist.size(); i++) {
        jso["accid"] = acclist.at(i).first;
        jso["accname"] = acclist.at(i).second;
        jsarr.append(jso);
    }

    QJsonDocument doc(jsarr);
    return QString::fromUtf8(doc.toJson().data());
}

QString MainController::viet2latin(const QString &name)
{
    QString txt = CommonFunction::ViettoLatin(name).toLower();

    while ( (txt.length() > 0) && (txt.at(0) == ' ') ) {
        txt = txt.remove(0, 1);
    }
    while ( (txt.length() > 0) && (txt.at(txt.length()-1) == ' ') ) {
        txt = txt.remove(txt.length()-1, 1);
    }

    return txt;
}

void MainController::timerReboot()
{   
    QDateTime dt = QDateTime::currentDateTimeUtc().toTimeZone(QTimeZone("Asia/Ho_Chi_Minh"));

    int dayreboot = 1 << (dt.date().dayOfWeek() % 7);
    if( dayreboot == (dayreboot & setting->rebootDate) )
    {
        int t1 = dt.time().hour()*60 + dt.time().minute();
        int t2 = t1 + REBOOT_INTERVAL;

        if( (setting->rebootTime >= t1) && (setting->rebootTime < t2) )
        {
            qDebug() << "schedule to restart Pi, " << QTime::currentTime();
            restartPi();
        }
    }
}

void MainController::timerSystemIdle()
{

}

void MainController::alertPhone(const QString &listphone, const QString &content) {
    httpalertphone = new HttpBase(QString(""),this);
    QObject::connect(httpalertphone, SIGNAL(done(QVariant)), this, SLOT(onAlertPhoneDone(QVariant)), Qt::UniqueConnection);
    QObject::connect(httpalertphone, SIGNAL(error(int,QString)), this, SLOT(onAlertPhoneError(int, QString)), Qt::UniqueConnection);

    httpalertphone->setUrl(QUrl("https://gbcstaging.zing.vn/monitorservice/api/reqalert/?"));
    httpalertphone->addParameter("cm", "alert", true);
    httpalertphone->addParameter("dt", CommonFunction::formatAlertPhone(listphone, content));
    httpalertphone->process();
}

void MainController::alertEmail(const QString &list_email, const QString& branch, const QString& host, int port) {
    httpalertemail = new HttpBase(QString(""),this);
    QObject::connect(httpalertemail, SIGNAL(done(QVariant)), this, SLOT(onAlertEmailDone(QVariant)), Qt::UniqueConnection);
    QObject::connect(httpalertemail, SIGNAL(error(int,QString)), this, SLOT(onAlertEmailError(int, QString)), Qt::UniqueConnection);

    httpalertemail->setUrl(QUrl("https://gbcstaging.zing.vn/monitorservice/api/reqalert/?"));
    httpalertemail->addParameter("cm", "alert", true);
    httpalertemail->addParameter("dt", CommonFunction::formatAlertEmail(list_email, branch, host, port));
    httpalertemail->process();
}

void MainController::onAlertEmailDone(const QVariant &data) {
    qDebug() << "alert email success, dt: " << data ;
}

void MainController::onAlertEmailError(const int &error, const QString &message) {
    qDebug() << "alert email faile, err: " << QString::number(error) << ", msg: " << message;
}

void MainController::onAlertPhoneDone(const QVariant &data) {
    qDebug() << "alert phone success, dt: " << data ;
}

void MainController::onAlertPhoneError(const int &error, const QString &message) {
    qDebug() << "alert phone faile, err: " << QString::number(error) << ", msg: " << message;
}

void MainController::onNotify(const QString &message)
{
    qDebug() << "onNotify:" << message;
    QString invceCode, zptransid, invceDate, barcode, discount, amount, payment;
    QJsonArray items;
    QJsonObject bill_note;
    int notify_type;
    BillInfo bi;
    if(CommonFunction::parseNotifyInfo(message, &notify_type, &invceCode, &zptransid, &invceDate, &barcode, &discount, &amount, &payment, &items, &bill_note)) {
        if(notify_type == 1) {
            // tạo nội dung xuất ra máy in
            QString printdata = bi.toPrinter(barcode,
                                             invceCode,
                                             zptransid,
                                             invceDate,
                                             discount,
                                             payment,
                                             items,
                                             bill_note);
            // print data
            printBill(invceCode, printdata);
        }
    }
}

void MainController::onCenterServiceFound(const QString &ip, const int &port) {
    qDebug() << "ip: " << ip << ", port:" + QString::number(port);
}

QString MainController::getAppName()
{
    return merchantCode;
}

void MainController::setAppName(const QString &appName, bool initSocket)
{
    if (appName.isEmpty() || (merchantCode.compare(appName) == 0)) {
        // Merchant ID is empty or the same current
        return;
    }

    merchantCode = appName;
    setting->setAppName(appName);

    if (initSocket) {
        // re-initial websocket for new session
        initialWebSocket(initSocket);
    }
}

QString MainController::getAppTitle() {
     return setting->appTitle;
}

void MainController::setAppTitle(const QString &appTitle) {
    setting->setAppTitle(appTitle);
}

QString MainController::getTitleEng()
{
    return CommonFunction::ViettoLatin(appTitle);
}

QString MainController::getAppMachine()
{
    return machineName;
}

int MainController::getConfigBillItemFontsize()
{
    return setting->billItemFontsize;
}

void MainController::setConfigBillItemFontsize(int fntsize)
{
    if (fntsize > 1) {
        setting->setBillItemFontsize(fntsize);
    }
}

int MainController::getConfigSobanin()
{
    return setting->sobanin;
}

void MainController::setConfigSobanin(int num)
{
    if (num > 0 && num <= 5) {
        setting->setSobanin(num);
    }
}

QString MainController::getConfigTenbanin()
{
    QStringList txts = setting->tenbanin.split(";");

    QString name = "";
    for (int i=0; i<qMax(txts.size(), setting->sobanin); i++)
    {
        if ( i < txts.size() )
        {
            name = name + (i>0? ";":"") + txts[i];
        }
        else
        {
            name = name + (i>0? ";":"");
        }
    }

    return name;
}

void MainController::setConfigTenbanin(const QString &name)
{
    setting->setTenbanin(name);
}

QString MainController::getConfigBillPreinf()
{
    return setting->billPreinf;
}

void MainController::setConfigBillPreinf(const QString &info)
{
    setting->setBillPreinf(info);
}

QString MainController::getConfigBillPostinf()
{
    return setting->billPostinf;
}

void MainController::setConfigBillPostinf(const QString &info)
{
    setting->setBillPostinf(info);
}

QString MainController::getConfigDockversion()
{
    return setting->dockVersion;
}

void MainController::setConfigDockversion(const QString &version)
{
    setting->setDockVersion(version);
}

QString MainController::getConfigPrintersize()
{
    return setting->printerSize;
}

void MainController::setConfigPrintersize(const QString &pagesize)
{
    setting->setPrintersize(pagesize);
}

bool MainController::getUserEnableConfig()
{
    return setting->userEnableConf;
}

void MainController::setUserEnableConfig(bool enableconf)
{
    setting->setUserenableConfig(enableconf);
}

int MainController::getConfigRebootDatePi()
{
    return setting->rebootDate;
}

void MainController::setConfigRebootDatePi(int dayofweek, bool on)
{
    if( on ) {
        setting->rebootDate |= (1 << dayofweek);
    }
    else {
        setting->rebootDate &= ~(1 << dayofweek);
    }

    if( setting->rebootDate && !m_rebootTimer.isActive() ) {
        m_rebootTimer.start(REBOOT_INTERVAL * 60000);
    }
    else if( !setting->rebootDate && m_rebootTimer.isActive() ) {
        m_rebootTimer.stop();
    }

    setting->saveRebootDatetime(1);
}

// type=0:all go&phut, type=1:gio, type=2:phut
int MainController::getConfigRebootTimePi(int type)
{
    if( type == 2 ) {
        return (setting->rebootTime % 60);
    }
    else if( type == 1 ) {
        return (setting->rebootTime / 60);
    }

    return setting->rebootTime;
}

void MainController::setConfigRebootTimePi(int value, int type)
{
    if( value < 0 ) {
        value = 0;
    }

    if( type == 2 ) {
        // minute
        if ( value > 59 ) {
            value = 59;
        }

        setting->rebootTime = (setting->rebootTime / 60)*60 + value;
    }
    else if( type == 1 ) {
        // hour
        if( value > 23 ) {
            value = 23;
        }
        setting->rebootTime = value*60 + (setting->rebootTime % 60);
    }
    else {
        // 23*60 + 59 = 1439
        if( value > 1439) {
            value = 1436;
        }
        setting->rebootTime = value;
    }

    // reboot time range: 00:03 - 23:56
    if( setting->rebootTime < 3 ) {
        setting->rebootTime = 3;
    }
    else if( setting->rebootTime > 1436 ) {
        setting->rebootTime = 1436;
    }

    setting->saveRebootDatetime(0);
}

QString MainController::getRestartTime()
{
    return m_startTime.toString(QString("yyyy/MM/dd - hh:mm:ss"));
}

QString MainController::getCurrentTime(bool on)
{
    QDateTime dt = QDateTime::currentDateTimeUtc().toTimeZone(QTimeZone("Asia/Ho_Chi_Minh"));

    if( on )
        return dt.toString(QString("yyyy/MM/dd - hh:mm:ss"));
    else
        return dt.toString(QString("yyyy/MM/dd - hh:mm ss"));
}

void MainController::saveConfig()
{
    setting->Save();
}

QString MainController::getLocalIp()
{
    QString ip;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
            if( ip.isEmpty() ) {
                ip = address.toString();
            }
            else {
                ip += "," + address.toString();
            }
        }
    }

    return ip;
}

void MainController::doScanDock()
{
    QStringList listServerIp;
    QList<QHostAddress> listServer;
    DeviceClient::discoverDeviceServerBroadcast(listServer);

    foreach (const QHostAddress& address, listServer) {
        qDebug() << "Found: " << address.toString();
        listServerIp << address.toString();
    }

    emit scanDockDone(listServerIp);
}

void MainController::doScanDockAutosetting()
{
    if (!isConnected())
    {
        QList<QHostAddress> listServer;
        DeviceClient::discoverDeviceServerBroadcast(listServer);

        foreach (const QHostAddress& address, listServer)
        {
            QString srvIp = address.toString();
            connectToDock(srvIp);

            break;
        }
    }
}

void MainController::doPing(const QString& host)
{
#ifndef Q_OS_IOS
    QProcess ps;
    QByteArray ba;
    ps.start("ping -c 4 " + host);
    if (ps.waitForStarted(-1)) {
        while(ps.waitForReadyRead(-1)) {
            ba += ps.readAllStandardOutput();
        }
    }

    emit pingDone(QString(ba));
#endif
}

void MainController::doWifiStatus(const QString &interface)
{
#ifndef Q_OS_IOS
    QProcess ps;
    QByteArray ba;
    QString programs = QString("%1 %2").arg("./vposwifi.sh status").arg(interface);
    ps.start(programs);
    if (ps.waitForStarted(-1)) {
        while(ps.waitForReadyRead(-1)) {
            ba += ps.readAllStandardOutput();
        }
    }
    qDebug() << "Call: " << programs;
    emit wifiStatusDone(QString(ba));
#endif
}

void MainController::updateWSServerIp()
{
    HttpBase httpIpServer;
    httpIpServer.setUrl(QUrl(httpTranspro + "://" + getPayment() + "/api/common?cm=getip"));
    httpIpServer.process(GET);
}

void MainController::initialWebSocket(bool forceStop)
{
    qDebug() << "initialWebSocket ... forcestop = " << forceStop;

    if( forceStop && wsClient )
    {
        wsClient->stop();
        wsClient->wait(10000);

        delete wsClient;
        wsClient = 0;
    }

    if (wsClient == 0)
    {
        //QUrl wsUrl = QUrl(wsTranspro + "192.168.102.201:8686/vpos" + "/ntf/");
        QUrl wsUrl = QUrl(wsTranspro + getPayment() + "/ntf/");
        qDebug() << "wsUrl: " << wsUrl;
        QUrl httpUrl = QUrl(httpTranspro + "://" + getPayment() + "/api/common/");
        qDebug() << "httpUrl: " << httpUrl;
        wsClient = new WSClient(wsUrl, httpUrl, merchantCode, deviceId, true, 0);

        QObject::connect(wsClient, SIGNAL(textMessageReceived(QString)), this, SLOT(onNotify(const QString&)));
        QObject::connect(wsClient, &WSClient::connected, this, [=](){emit cloudConnectionChange(true);});
        QObject::connect(wsClient, &WSClient::closed, this, [=](){emit cloudConnectionChange(false);});
        wsClient->start();
    }
}

void MainController::initialWsCssClient()
{
    if( wscssClient ) {
        delete wscssClient;
        wscssClient = NULL;
    }

    wscssClient = new WsCssClient( APPID::VPOS, APPID::PRINTER );
    QObject::connect(wscssClient, SIGNAL(textMessageReceived(QString)), this, SLOT(onNotify(QString)));
    QObject::connect(wscssClient, SIGNAL(foundServer(QString,int)), this, SLOT(onCenterServiceFound(QString,int)));
}

QString MainController::formatMoney(long long moneyValue)
{
    long long absVal = abs(moneyValue);
    QString money = QString::number(absVal);
    int loop = money.length() / 3;
    if (loop > 0)
    {
        if (money.length() % 3 == 0)
        {
            loop = loop - 1;
        }

        int index = money.length();
        for (int i = 0; i < loop ; i++)
        {
            index = index - 3;
            money.insert(index,  QString(","));
        }
    }

    if (moneyValue < 0)
        money.insert(0,  QString("-"));

    return money;
}

long long MainController::getMoneyValue(const  QString &moneyString)
{
    QString money = moneyString;
    money = money.replace(QString(","),QString::null);
    if (money.isEmpty())
    {
        return 0;
    }
    else
    {
        return money.toLongLong();
    }
}

QString MainController::moneyMoney(QString money)
{
    // convert money string "12345" >> "12,345"
    return formatMoney(getMoneyValue(money));
}

// print bill detail to printer
void MainController::printBill(const QString& ivcode, const QString &printData)
{
    qDebug() << "==============START PRINT BILL==============";
    qDebug() << "printData: " + printData;

    // call printing function to sending bill-Detail to printer
    // ...
#if 0
#ifdef Q_OS_ANDROID
    QString newData = CommonFunction::ViettoLatin(printData);
    QAndroidJniObject billText = QAndroidJniObject::fromString(newData);
    QtAndroid::androidActivity().callMethod<void>("printBill", "(Ljava/lang/String;)V",  billText.object<jstring>());
#endif
#endif

    if (deviceService)
    {
        QString fooddata = CommonFunction::ViettoLatin(printData);
        qDebug() << "fooddata: " + fooddata;

        if (setting->dockVersion.compare("1.0") == 0) {
            // original print server service
            qDebug() << "print in dock version 1.0";
            deviceService->print(QString(""), ivcode, fooddata, DeviceClient::VPOS_Payment);
        }
        else
        {
            // format print data for Dock Print Server 2.0
            if (setting->sobanin < 2)
            {
                qDebug() << "print in dock verson 2.0, sobanin < 2";
                QByteArray prntcode = createPrintFoodcourt(fooddata, setting->billPreinf, setting->billPostinf);
                QString prntdata = Prntdataformat::makePrintDataFromPrncode(prntcode);
                deviceService->print(QString(""), ivcode, prntdata, DeviceClient::VPOS_Payment);
            }
            else
            {
                qDebug() << "print in dock verson 2.0, sobanin >= 2";
                QByteArray prntcode;
                QStringList namelist = setting->tenbanin.split(";");

                for (int i=0; i<setting->sobanin; i++)
                {
                    QString namebanin;

                    if (i < namelist.size()) {
                        namebanin = QString("#%1 %2").arg(i+1).arg(namelist[i]);
                    } else {
                        namebanin = QString("#%1").arg(i+1);
                    }

                    prntcode = createPrintFoodcourt(fooddata, setting->billPreinf, setting->billPostinf, namebanin, (i+1)==setting->sobanin);
                    QString prntdata = Prntdataformat::makePrintDataFromPrncode(prntcode);
                    deviceService->print(QString(""), ivcode, prntdata, DeviceClient::VPOS_Payment);
                }
            }
        }
    }

#ifdef Q_OS_WIN32
    // xprinter58 is printer name

    qDebug() << "Printer name:" + getPrinter();

    ReceiptPrinter printer(getPrinter(), printData);
    printer.print();
#endif
}

void MainController::stopDevice()
{
    //qDebug() << "MainController::stopDevice";
#if 0
#ifdef Q_OS_ANDROID
    QByteArray dataArray = CommonFunction::parseCmdStopToReaderDevice();
    QAndroidJniObject jstrqrcode = QAndroidJniObject::fromString(QString(dataArray.toHex()));
    QtAndroid::androidActivity().callMethod<void>("stopDevice", "(Ljava/lang/String;)V",  jstrqrcode.object<jstring>());
#endif
#endif

    if (deviceService && deviceService->isConnected()) {
        deviceService->stopReaderDevice();
    }
}

QString MainController::getPrinter()
{
    return setting->printerName;
}

void MainController::setPrinter(QString prnName)
{
    setting->setPrinter(prnName);
}

QString MainController::getPayment()
{
    return setting->paymentName;
}

QString MainController::getListEmail() {
    return setting->listemail;
}

QString MainController::getListPhone() {
    return setting->listphone;
}

QString MainController::getUrlService()
{
    QStringList urls = setting->paymentName.split(".");
    if (urls.size() > 0) {
        return urls.at(0);
    }

    return setting->paymentName;
}

QString MainController::getTransferProtocol()
{
    return httpTranspro;
}

void MainController::setListEmail(QString listemail) {
    setting->setListEmail(listemail);
}

void MainController::setListPhone(QString listphone) {
    setting->setListPhone(listphone);
}

void MainController::setTransferProtocol(const QString& transpro, bool initSocket)
{
    if (transpro.isEmpty() || (httpTranspro.compare(transpro) == 0)) {
        return;
    }

    setting->setTransProtocol(transpro);

    if (transpro.compare("http") == 0) {
        httpTranspro = "http";
        wsTranspro = "ws://";
    } else {
        httpTranspro = "https";
        wsTranspro = "wss://";
    }

    if( initSocket ) {
        initialWebSocket(initSocket);
    }
}

void MainController::setPayment(QString paymentName, bool initSocket)
{
    if ( setting->setPaymentName(paymentName) &&
         initSocket )
    {
        // re-initial websocket for new session
        initialWebSocket(initSocket);
    }
}

QString MainController::getDockServer()
{
    return setting->dockServer;
}

void MainController::setDockServer(QString dockServer)
{
    setting->setDocServer(dockServer);
}

void MainController::scanDock(bool doAuto)
{
    if ( doAuto ) {
        doScanDockAutosetting();
    }
    else {
        // Start the computation.
        QFuture<void> future = QtConcurrent::run(this, &MainController::doScanDock);
    }
}

bool MainController::isConnected()
{
    if (deviceService && deviceService->isConnected()) {
        return true;
    }

    return false;
}

bool MainController::connectToDock(const QString &serverIp)
{
    if (Q_NULLPTR == deviceService) {
        deviceService = new DeviceClientService();
        connect(deviceService, &DeviceClientService::connectionChanged, [=](int iConnect) {
//            if (iConnect == DeviceClient::Connected) {
//                emit dockConnectionChange(true);
//            } else {
//                emit dockConnectionChange(false);
//            }
        });

        connect(deviceService, &DeviceClientService::printDone, [=](quint16 errcode, const QString& ivcode) {
//            if (!ivcode.isEmpty() && m_Bills.checkInvceCode(ivcode)) {
//                emit printDone(errcode);
//            }
//            else {
//                //qDebug() << "Not current invoice code " << ivcode;
//            }
        });

        connect(deviceService, &DeviceClientService::printerReadyChanged, [=](bool ready) {
//            emit printerReadyChanged(ready);
        });

        connect(deviceService, &DeviceClientService::dockStat, [=](const QString& stat) {
//            emit dockStatistics(stat);
        });

        connect(deviceService, &DeviceClientService::mifareFound, [=](const QString& mfdata) {
//            doPayCard(mfdata);
        });
    }

    deviceService->startService(serverIp);
    setting->setDocServer(serverIp);
    return true;
}

void MainController::disconnectFromDock()
{
    deviceService->disconnectFromServer();
}

void MainController::testReaderDevice(bool run)
{
    if (run) {
        qDebug() << "Start reader device";
        QByteArray data = CommonFunction::parseDataToRemoteReaderDevice(10000, 10, "dT-mf_jKeD9ZHlrmKJxooA");
        deviceService->startReaderDevice(data);
    } else {
        qDebug() << "Stop reader device";
        deviceService->stopReaderDevice();
    }
}

void MainController::updateWifi(const QString &ssid, const QString &key, const QString &encrypt)
{
    qDebug() << "updateWifi, ssid=" << ssid << ", key=" << key << ", encrypt=" << encrypt;

    if (key.isEmpty()) {
        deviceService->updateWifi(ssid, key, "none");
    } else {
        deviceService->updateWifi(ssid, key, encrypt);
    }
}

void MainController::updateWifiPi(const QString& interface, const QString &ssid, const QString &key, const QString &encrypt, bool scan_ssid)
{
#ifndef Q_OS_IOS

    // ./vposwifi.sh update interface ssid key psk2-mixed false
    // ./vposwifi.sh update wlan0 csmrouter gbc@vng2017 psk2-mixed false

    QString programs = QString("sudo ./vposwifi.sh update \"%1\" \"%2\" \"%3\"").arg(interface, ssid, key);
    QProcess::startDetached(programs);
#endif
}

void MainController::wifiStatus(const QString &interface)
{
    QFuture<void> future = QtConcurrent::run(this, &MainController::doWifiStatus, interface);
}

void MainController::testPing(const QString& host)
{
    QFuture<void> future = QtConcurrent::run(this, &MainController::doPing, host);
}

void MainController::restartDock()
{
    if (deviceService) {
        deviceService->restartService();
    }
}

void MainController::restartPi()
{
#ifndef Q_OS_IOS
    QString programs = QString("sudo reboot");
    qDebug() << "Call: " << programs;
    QProcess::startDetached(programs);
#endif
}

void MainController::haltPi()
{
#ifndef Q_OS_IOS
    QString programs = QString("sudo halt");
    qDebug() << "Call: " << programs;
    QProcess::startDetached(programs);
#endif
}

void MainController::checkPrinterStatus()
{
    if (deviceService && deviceService->isConnected()) {
        deviceService->checkPrinterStatus();
    }
}

void MainController::printTest(const QJsonArray &foods)
{
    QString dt = QString("\"dt\":{%1,%2,%3,%4,%5,%6,%7}")
            .arg("\"invoice_code\":\"0000000000000000\"")
            .arg("\"invoice_datetime\":\"201701100080808\"")
            .arg("\"barcode\":\"362589764568\"")
            .arg("\"amount\":780228")       //tong tien
            .arg("\"discount\":10")         //giam gia
            .arg("\"payment\":702205")      //thuc thu
            .arg(QString("\"appuser\":\"%1\"").arg(merchantCode));

    QString msg =
            QString("{%1,%2,%3}")
            .arg("\"type\":1")
            .arg("\"msg\":\"payment_success\"")
            .arg(dt);

    onNotify(msg);
}

bool MainController::checkToken(const QString& data, const QString& token, const QString key)
{
    QString tk = CommonFunction::HMacSha256HexStringEncode(data, key);
    return (tk.compare(token) == 0);
}

QString MainController::xorstr(const QString& s)
{
    QString res = "";

    for( int i=0; i<s.length(); i++ )
    {
        res += (s[i].toLatin1() ^ 128);
    }

    return res;
}

void MainController::sortPairList(QList<QPair<QString, QString> > &pl)
{
    QList<QPair<QString, QString> > source = pl;

    QList<QString> keys;
    for( int i=0; i<source.size(); i++ )
    {
        keys.append( source.at(i).first);
    }
    qSort(keys);

    pl.clear();
    for( int i=0; i<keys.size(); i++ )
    {
        const QString key = keys.at(i);
        int idx = -1;

        for( int j=0; j<source.size(); j++ )
        {
            if( key == source.at(j).first )
            {
                pl.append( source.at(j) );
                idx = j;
                break;
            }
        }

        if( idx >= 0 ) {
            source.removeAt(idx);
        }
    }
}

// tạo bản in cho foodcourt
QByteArray MainController::createPrintFoodcourt(const QString& fooddata,
                                                const QString &billPreinf,
                                                const QString &billPostinf,
                                                const QString &banin, bool cutpageSeperate)
{
    int PAGESZ = 33;
    int TAB1, TAB2, TAB3, TAB4;

    if (setting->printerSize == "small") {
        PAGESZ = 33;
        TAB1 = 10;
        TAB2 = 12;
        TAB3 = 23;
        TAB4 = 33;
    }
    else {
        PAGESZ = 48;
        TAB1 = 12;
        TAB2 = 27;
        TAB3 = 38;
        TAB4 = 48;
    }

    QJsonDocument jsd = QJsonDocument::fromJson(fooddata.toUtf8());
    if (!jsd.isObject()) {
        return "";
    }

    QJsonObject jso = jsd.object();

    Prntdataformat pdf;

    pdf.codeFontType(pdf.font_A);
    pdf.codeFontBold(true);
    pdf.codeLine(setting->appTitle, pdf.Justify_center);
    pdf.codeFontBold(false);

    if ( !billPreinf.isEmpty() ) {
        QStringList infs = billPreinf.split(";");
        for (int i=0; i<infs.length(); i++) {
            pdf.codeLine(infs.at(i));
        }
        //pdf.codeLine("Tang 5-TTTM Flemington");
        //pdf.codeLine("184 Le Dai Hanh, P.15, Q.11");
    }

    pdf.codeFeedline();
    QString vposInvoice = jso["receiptNum"].toString();
    QString zptransid = jso["zptransid"].toString();
    QString localtion = jso["location"].toString();
    QString customer_name = jso["customer_name"].toString();
    QString notice = jso["bill_note"].toString();
    QString phone_no = jso["phone_no"].toString();
    pdf.codeLine(QString("Hoa don   :\t%1").arg(zptransid), pdf.Justify_left, TAB1);
    pdf.codeLine(QString("Ten KH    :\t%1").arg(customer_name), pdf.Justify_left, TAB1);
    pdf.codeLine(QString("Phone     :\t%1").arg(phone_no), pdf.Justify_left, TAB1);
    pdf.codeLine(QString("Vi tri    :\t%1").arg(localtion), pdf.Justify_left, TAB1);
    pdf.codeLine(QString("Ngay      :\t%1").arg(jso["datetime"].toString()), pdf.Justify_left, TAB1);

    pdf.codeChars('-', PAGESZ, pdf.Justify_center);
    pdf.codeText("TEN", pdf.Justify_left);
    pdf.codeText("\tSL", pdf.Justify_none, TAB2);
    pdf.codeText("\tD.GIA", pdf.Justify_right, TAB3);
    pdf.codeLine("\tT.TIEN", pdf.Justify_right, TAB4);
    pdf.codeChars('-', PAGESZ, pdf.Justify_center);

    // ...
    if (jso["item"].isArray())
    {
        QJsonArray receiptItem = jso["item"].toArray();
        for (int i = 0; i < receiptItem.size(); i++)
        {
            QJsonObject item = receiptItem[i].toObject();

            QString name;

            if(QString::compare(item["notetext"].toString().trimmed(), "", Qt::CaseInsensitive) == 0) {
                name = item["item_name"].toString();
            }
            else {
                name = item["item_name"].toString() + "("+ item["notetext"].toString() +")";
            }
            int isBold = QString::compare(name, "com trua", Qt::CaseInsensitive);
            if (isBold == 0) {
                pdf.emphasized_on();
                name = name.toUpper();
                pdf.prntUnderline(Prntdataformat::udl_1dot);
            }

            if (name.length() >= TAB2)
                pdf.codeLine(name, pdf.Justify_left);
            else
                pdf.codeText(name, pdf.Justify_left);

            if (isBold == 0) {
                pdf.prntUnderline(Prntdataformat::udl_none);
            }

            pdf.codeText("\t" + item["quantity"].toString(), pdf.Justify_left, TAB2);
            pdf.codeText("\t" + item["price"].toString(), pdf.Justify_right, TAB3);
            pdf.codeLine("\t" + item["amount"].toString(), pdf.Justify_right, TAB4);

            if (isBold == 0) {
                pdf.emphasized_off();
            }
        }
    }

    pdf.codeChars('-', PAGESZ, pdf.Justify_left);

    QString total = "\t" + jso["total"].toString();

    if (jso["ext"].isArray()) {
        pdf.codeLine(QString("TONG:%1").arg(total), pdf.Justify_left, TAB4-total.length());
    }
    else {
        pdf.emphasized_on();
        pdf.codeLine(QString("TONG:%1").arg(total), pdf.Justify_left, TAB4-total.length());
        pdf.emphasized_off();
    }

    // Extended field
    if (jso["ext"].isArray())
    {
        QJsonArray extItems = jso["ext"].toArray();
        for (int i = 0; i < extItems.size(); i++)
        {
            QJsonObject item = extItems[i].toObject();

            QString name = item["name"].toString();
            QString value = "\t" + item["value"].toString();

            if( (i+1) == extItems.size() ) {
                pdf.codeChars('-', PAGESZ, pdf.Justify_left);
            }

            if( (i+1) < extItems.size() )
            {
                pdf.codeLine(QString("%1%2").arg(name).arg(value), pdf.Justify_left, TAB4-value.length());
            }
            else
            {
                pdf.emphasized_on();
                pdf.codeLine(QString("%1%2").arg(name).arg(value), pdf.Justify_left, TAB4-value.length());
                pdf.emphasized_off();
            }
        }
    }
    // Extended field

    pdf.codeChars('-', PAGESZ, pdf.Justify_left);
    pdf.codeFeedline(1);

    pdf.codeLine(QString("%1%2").arg("(*)Ghi chu: ").arg(notice), pdf.Justify_left, 80);

    pdf.codeBarcode(jso["barcode"].toString(), 2, 80, pdf.Justify_center);
    pdf.codeFeedline(1);

    if ( !billPostinf.isEmpty() ) {
        QStringList infs = billPostinf.split(";");
        for (int i=0; i<infs.length(); i++) {
            pdf.codeLine(infs.at(i));
        }
        //pdf.codeLine("Cam on quy khach");
        //pdf.codeLine("Hen gap lai");
    }

    pdf.codeFeedline(PAGESZ < 40 ? 2 : 1);

    if (!cutpageSeperate) {
        pdf.codeChars('-', PAGESZ, pdf.Justify_left);
        pdf.codeFeedline(2);
    }
    else {
        pdf.codeFeedline(0);
    }

    pdf.codeCutpage(cutpageSeperate);

    return pdf.getPrintDeviceCode();
}

QByteArray MainController::createPrintBaocao(const QString& baocao, int bcType, bool bDetail)
{
    int PAGESZ = 33;
    int TAB3, TAB4;

    if (setting->printerSize == "small") {
        PAGESZ = 33;
        TAB3 = 23;
        TAB4 = 33;
    }
    else {
        PAGESZ = 48;
        TAB3 = 38;
        TAB4 = 48;
    }

    Prntdataformat pdf;

    pdf.codeFontType(pdf.font_A);
    pdf.codeFontBold(true);
    pdf.codeLine(getTitleEng(), pdf.Justify_center);
    pdf.codeFontBold(false);

    if ( !setting->billPreinf.isEmpty() ) {
        QStringList infs = setting->billPreinf.split(";");
        for (int i=0; i<infs.length(); i++) {
            pdf.codeLine(infs.at(i));
        }
    }

    pdf.codeFeedline();
    pdf.codeLine(bcType == 0 ? "BAO CAO  X" : "BAO CAO Z", pdf.Justify_center);

    // bao cao data
    QJsonDocument jsd = QJsonDocument::fromJson(baocao.toUtf8());
    if (jsd.isObject())
    {
        QJsonObject jso = jsd.object();

        QString slMonan;
        QString sDoanhthu, sGiamgia, sThucthu;
        int iDoanhthu=0, iGiamgia=0, iThucthu=0;

        if (jso.contains("dt"))
        {
            QJsonObject jdt = jso["dt"].toObject();

            QString beginTime, endTime;

            if (jdt.contains("begin_datetime")) {
                beginTime = jdt["begin_datetime"].toString();
            }

            if (jdt.contains("end_datetime")) {
                endTime = jdt["end_datetime"].toString();
            }

            pdf.codeLine(QString("tu : %1").arg(beginTime));
            pdf.codeLine(QString("den: %1").arg(endTime));

            // lấy giờ server hoặc ngày nhập trùng ngày server
            if (!m_bcDate.isEmpty() && endTime.left(10) != m_bcDate)
            {
                pdf.codeFeedline();
                pdf.codeLine(QString("(Ngay in: %1)").arg(endTime));
            }

            pdf.codeFeedline();

            if (jdt.contains("dataSummary"))
            {
                QJsonObject jsum = jdt["dataSummary"].toObject();

                if (jsum.contains("total_revenue_summary"))
                {
                    iDoanhthu = jsum["total_revenue_summary"].toInt();
                    sDoanhthu = "\t" + moneyMoney( QString::number( iDoanhthu ) );
                }

                if (jsum.contains("total_real_revenue_summary"))
                {
                    iThucthu = jsum["total_real_revenue_summary"].toInt();
                    iGiamgia = iDoanhthu - iThucthu;

                    sGiamgia = "\t" + moneyMoney( QString::number( iGiamgia ) );
                    sThucthu = "\t" + moneyMoney( QString::number( iThucthu ) );
                }

                if (bDetail == false )
                {
                    // bao cao rut gon

                    pdf.codeChars('-', PAGESZ, pdf.Justify_center);

                    pdf.codeText(QString("DOANH THU:"), pdf.Justify_left);
                    pdf.codeLine(sDoanhthu, pdf.Justify_left, TAB4-sDoanhthu.length());

                    pdf.codeText(QString("GIAM GIA:"), pdf.Justify_left);
                    pdf.codeLine(sGiamgia, pdf.Justify_left, TAB4-sGiamgia.length());

                    pdf.codeText(QString("THUC THU:"), pdf.Justify_left);
                    pdf.codeLine(sThucthu, pdf.Justify_left, TAB4-sThucthu.length());

                    pdf.codeChars('-', PAGESZ, pdf.Justify_center);

                    pdf.codeFeedline(PAGESZ < 40 ? 2 : 1);
                    pdf.codeCutpage();
                }
                else
                {
                    // bao cao chi tiet

                    if (jsum.contains("total_items_summary")) {
                        slMonan = "\t" + QString::number(jsum["total_items_summary"].toInt());
                    }

                    if (jdt.contains("listData"))
                    {
                        QJsonArray jlstdata = jdt["listData"].toArray();

                        if (jlstdata.size() > 0 )
                        {
                            pdf.codeChars('-', PAGESZ, pdf.Justify_center);
                            pdf.codeText("TEN MON AN", pdf.Justify_left);
                            pdf.codeText("\tSL", pdf.Justify_left, TAB3-3);
                            pdf.codeLine("\tT.TIEN", pdf.Justify_left, TAB4-7);
                            pdf.codeChars('-', PAGESZ, pdf.Justify_center);
                        }

                        for( int i=0; i<jlstdata.size(); i++)
                        {
                            QJsonObject item = jlstdata[i].toObject();

                            QString name = QString("%1 %2").arg(QString("%1").arg(i+1, 2, 10, QChar(' '))).arg(item["item_name"].toString());
                            if (name.length() < TAB3)
                                pdf.codeText(name, pdf.Justify_left);
                            else
                                pdf.codeLine(name, pdf.Justify_left);

                            name = "\t" + item["total_items"].toString();
                            pdf.codeText(name, pdf.Justify_left, TAB3-name.length());

                            name = "\t" + moneyMoney( item["total_revenue"].toString() );
                            pdf.codeLine(name, pdf.Justify_left, TAB4-name.length());
                        }
                    }

                    pdf.codeChars('-', PAGESZ, pdf.Justify_center);

                    pdf.codeText("TONG:", pdf.Justify_left, 0);
                    pdf.codeText(slMonan, pdf.Justify_left, TAB3-slMonan.length());
                    pdf.codeLine(sDoanhthu, pdf.Justify_left, TAB4-sDoanhthu.length());

                    pdf.codeText(QString("GIAM GIA:"), pdf.Justify_left);
                    pdf.codeLine(sGiamgia, pdf.Justify_left, TAB4-sGiamgia.length());

                    pdf.codeText(QString("THUC THU:"), pdf.Justify_left);
                    pdf.codeLine(sThucthu, pdf.Justify_left, TAB4-sThucthu.length());

                    pdf.codeChars('-', PAGESZ, pdf.Justify_center);

                    // In chi tiet hoa don
                    if (jdt.contains("listInvoice"))
                    {
                        QJsonArray jlstdata = jdt["listInvoice"].toArray();

                        if (jlstdata.size() > 0)
                        {
                            pdf.codeFeedline(1);
                            pdf.codeLine("THONG TIN CHI TIET", pdf.Justify_center);
                            pdf.codeFeedline(1);
                        }

                        for( int i=0; i<jlstdata.size(); i++)
                        {
                            QJsonObject jsoIvce = jlstdata[i].toObject();

                            pdf.codeLine(QString("Ngay: %1").arg(jsoIvce["payment_date_time"].toString()), pdf.Justify_left);
                            pdf.codeLine(QString("HD  : %1").arg(jsoIvce["invoice_code"].toString()), pdf.Justify_left);

                            if (jsoIvce["listInvoiceDetail"].isArray())
                            {
                                QJsonArray receiptItem = jsoIvce["listInvoiceDetail"].toArray();
                                for (int i = 0; i < receiptItem.size(); i++)
                                {
                                    QJsonObject item = receiptItem[i].toObject();

                                    QString name = QString("%1 %2").arg(QString("%1").arg(i+1, 2, 10, QChar(' '))).arg(item["item_name"].toString());
                                    if (name.length() >= TAB3)
                                        pdf.codeLine(name, pdf.Justify_left);
                                    else
                                        pdf.codeText(name, pdf.Justify_left);

                                    name = "\t" + QString::number( item["quantity"].toInt() );
                                    pdf.codeText(name, pdf.Justify_left, TAB3-name.length());

                                    name = "\t" + moneyMoney( QString::number( item["amount"].toInt() ));
                                    pdf.codeLine(name, pdf.Justify_left, TAB4-name.length());
                                }
                            }

                            int iThanhtien = jsoIvce["amount"].toInt();
                            QString sThanhtien = "\t" + moneyMoney( QString::number( iThanhtien ) );
                            pdf.codeText("TONG:", pdf.Justify_left, 0);
                            pdf.codeText(sThanhtien, pdf.Justify_left, TAB4-sThanhtien.length());

                            int iThucthu = jsoIvce["real_amount"].toInt();
                            if (iThanhtien > iThucthu)
                            {
                                int iGiamgia = iThanhtien - iThucthu;
                                QString sGiamgia = "\t" + moneyMoney( QString::number( iGiamgia ) );
                                pdf.codeText("GIAM GIA:", pdf.Justify_left, 0);
                                pdf.codeText(sGiamgia, pdf.Justify_left, TAB4-sGiamgia.length());

                                QString sThucthu = "\t" + moneyMoney( QString::number( iThucthu ) );
                                pdf.codeText("THUC THU:", pdf.Justify_left, 0);
                                pdf.codeText(sThucthu, pdf.Justify_left, TAB4-sThucthu.length());
                            }
                            pdf.codeChars('-', PAGESZ, pdf.Justify_center);
                        }
                    }

                    pdf.codeFeedline(1);
                    pdf.codeText("Thank You!", pdf.Justify_center);
                    pdf.codeFeedline(2);

                    pdf.codeFeedline(PAGESZ < 40 ? 2 : 1);
                    pdf.codeCutpage();
                }
            }

            // tra ket qua pdf ve
            return pdf.getPrintDeviceCode();
        }
        else {
            pdf.codeChars('-', PAGESZ, pdf.Justify_center);
            pdf.codeLine("KHONG CO DU LIEU HOP LE");
            pdf.codeChars('-', PAGESZ, pdf.Justify_center);
        }
    }
    else {
        pdf.codeChars('-', PAGESZ, pdf.Justify_center);
        pdf.codeLine("DU LIEU KHONG HOP LE");
        pdf.codeChars('-', PAGESZ, pdf.Justify_center);
    }
    // bao cao data

    pdf.codeFeedline(PAGESZ < 40 ? 2 : 1);
    pdf.codeCutpage();

    return pdf.getPrintDeviceCode();
}

void MainController::printBigData(const QByteArray &data)
{
    int buffsize = 2048;
    int pos = 0;

    while( pos < data.size() )
    {
        int prntsize;

        if ( (pos + buffsize) < data.size() ) {
            prntsize = buffsize;
        }
        else {
            prntsize = data.size() - pos;
        }

        QString prncode = Prntdataformat::makePrintDataFromPrncode(data.mid(pos, prntsize));
        deviceService->print(QString(""), "", prncode, DeviceClient::VPOS_Payment);

        pos += prntsize;
    }
}
