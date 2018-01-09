#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QJsonArray>
#include <QEvent>
#include <QProcess>
#include <QSet>
#include "http/httpbase.h"
#include "http/httpbase2.h"
#include "../common/wscssclient.h"
#include "../common/deviceclientservice.h"
#include "wsclient.h"
#include "billdetail.h"

#define PAY_ZALO 1
#define PAY_CARD 2
#define PAY_CASH 4

#define LOGIN_NONE          0
#define LOGIN_WAITLOGIN     1
#define LOGIN_READY         2
#define BAOCAO_WAITING      3
#define BAOCAO_READY        4
#define FUPDATE_NONE        0
#define FUPDATE_PROG1       1
#define FUPDATE_PROG2       2
#define FUPDATE_BUSY        (FUPDATE_NONE + FUPDATE_PROG1 + FUPDATE_PROG2)
#define FOOD_SEARCHING      4

class ConfigSetting;
class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = 0);
    ~MainController();

    Q_INVOKABLE bool    isDebugmode();
    Q_INVOKABLE bool    isRaspberry();
    Q_INVOKABLE void    appQuit();

    Q_INVOKABLE QString viet2latin(const QString &name);

    Q_INVOKABLE QString formatMoney(long long moneyValue);
    Q_INVOKABLE long long getMoneyValue(const QString &moneyString);
    // format string tiền, thêm dấu ','
    Q_INVOKABLE QString moneyMoney(QString money);

    Q_INVOKABLE void printBill(const QString& ivcode, const QString &printData);
    Q_INVOKABLE void stopDevice();

    Q_INVOKABLE QString getPrinter();
    Q_INVOKABLE void setPrinter(QString prnName);
    Q_INVOKABLE QString getPayment();
    Q_INVOKABLE QString getListEmail();
    Q_INVOKABLE void setListEmail(QString listemail);
    Q_INVOKABLE QString getListPhone();
    Q_INVOKABLE void setListPhone(QString listphone);
    Q_INVOKABLE QString getUrlService();
    Q_INVOKABLE QString getTransferProtocol();
    Q_INVOKABLE void setTransferProtocol(const QString& transpro, bool initSocket=true);
    Q_INVOKABLE void setPayment(QString paymentName, bool initSocket=true);

    Q_INVOKABLE QString getDockServer();
    Q_INVOKABLE void setDockServer(QString dockServer);

    Q_INVOKABLE void scanDock(bool doAuto=false);
    Q_INVOKABLE bool isConnected();
    Q_INVOKABLE bool connectToDock(const QString& serverIp);
    Q_INVOKABLE void disconnectFromDock();
    Q_INVOKABLE void testReaderDevice(bool run);
    Q_INVOKABLE void updateWifi(const QString &ssid, const QString &key, const QString &encrypt = QString("psk2-mixed"));
    Q_INVOKABLE void updateWifiPi(const QString& interface, const QString &ssid, const QString &key, const QString &encrypt = QString("psk2-mixed"), bool scan_ssid = false);
    Q_INVOKABLE void wifiStatus(const QString& interface = QString("wlan0"));
    Q_INVOKABLE void testPing(const QString& host);
    Q_INVOKABLE void restartDock();
    Q_INVOKABLE void restartPi();
    Q_INVOKABLE void haltPi();
    Q_INVOKABLE void checkPrinterStatus();

    Q_INVOKABLE void printTest(const QJsonArray &foods);

    Q_INVOKABLE QString getLocalIp();

    Q_INVOKABLE QString getAppName();
    Q_INVOKABLE void    setAppName(const QString &appName, bool initSocket=true);
    Q_INVOKABLE QString getAppTitle();
    Q_INVOKABLE void    setAppTitle(const QString &appTitle);
    Q_INVOKABLE QString getTitleEng();
    Q_INVOKABLE QString getAppMachine();

    Q_INVOKABLE int     getConfigBillItemFontsize();
    Q_INVOKABLE void    setConfigBillItemFontsize(int fntsize);
    Q_INVOKABLE int     getConfigSobanin();
    Q_INVOKABLE void    setConfigSobanin(int num);
    Q_INVOKABLE QString getConfigTenbanin();
    Q_INVOKABLE void    setConfigTenbanin(const QString &name);
    Q_INVOKABLE QString getConfigBillPreinf();
    Q_INVOKABLE void    setConfigBillPreinf(const QString &info);
    Q_INVOKABLE QString getConfigBillPostinf();
    Q_INVOKABLE void    setConfigBillPostinf(const QString &info);
    Q_INVOKABLE QString getConfigDockversion();
    Q_INVOKABLE void    setConfigDockversion(const QString &version);
    Q_INVOKABLE QString getConfigPrintersize();
    Q_INVOKABLE void    setConfigPrintersize(const QString &pagesize);
    Q_INVOKABLE bool    getUserEnableConfig();
    Q_INVOKABLE void    setUserEnableConfig(bool enableconf);
    Q_INVOKABLE int     getConfigRebootDatePi();
    Q_INVOKABLE void    setConfigRebootDatePi(int dayofweek, bool on);
    Q_INVOKABLE int     getConfigRebootTimePi(int type=0);
    Q_INVOKABLE void    setConfigRebootTimePi(int value, int type=0);
    Q_INVOKABLE QString getRestartTime();
    Q_INVOKABLE QString getCurrentTime(bool on);

    Q_INVOKABLE void saveConfig();

    Q_INVOKABLE QString getAccount();
signals:
    void scanDockDone(const QStringList& listDock);
    void dockConnectionChange(bool connected);
    void pingDone(const QString& data);
    void loadingDone();
    void wifiStatusDone(const QString& data);
    void showMessage(const QString& msg);
    void cloudConnectionChange(bool connected);
    void dockStatistics(const QString& stat);
    void printerReadyChanged(bool ready);
    void idleTimeout();
public slots:
    void onNotify(const QString &message);
    void onCenterServiceFound(const QString &ip, const int &port);
    void onAlertEmailDone(const QVariant &data);
    void onAlertEmailError(const int &error, const QString &message);
    void onAlertPhoneDone(const QVariant &data);
    void onAlertPhoneError(const int &error, const QString &message);

    void timerReboot();
    void timerSystemIdle();
private:
    void alertPhone(const QString & listphone, const QString & content);
    void alertEmail(const QString & listemail, const QString & branch, const QString & host, int port);
    void doScanDock();
    void doScanDockAutosetting();
    void doPing(const QString& host);
    void doWifiStatus(const QString& interface);
    void updateWSServerIp();
    void initialWebSocket(bool forceStop=false);
    void initialWsCssClient();
    bool checkToken(const QString& data, const QString& token, const QString key);

    QString xorstr(const QString& s);

    void sortPairList(QList<QPair<QString, QString> > &pl);

    // tạo bản in cho foodcourt
    QByteArray createPrintFoodcourt(const QString& fooddata,
                                    const QString &billPreinf="",
                                    const QString &billPostinf="",
                                    const QString &banin="",
                                    bool cutpageSeperate=true);
    QByteArray createPrintBaocao(const QString& baocao, int bcType, bool bDetail);
    void printBigData(const QByteArray& data);

private:
    HttpBase*           payZalo;
    HttpBase*           httppayCash;
    HttpBase*           httpcancel;
    HttpBase*           httpreject;
    HttpBase*           httpfood;
    HttpBase*           httpalertemail;
    HttpBase*           httpalertemaildominoserr;
    HttpBase*           httpalertphone;
    HttpBase*           httppmsid;
    HttpBase2*          http2;
    HttpBase2*          httpBaocao;

    WSClient            *wsClient;
    WsCssClient         *wscssClient;

    QString             m_cardID;

    DeviceClientService *deviceService;
    ConfigSetting       *setting;
    QString             deviceId;

    qulonglong          m_qullLUT;
    QTimer              m_tmCheckUpdateFood;
    QTimer              m_rebootTimer;

    HttpBase*           m_httpCheckUpdate;
    int                 m_fupdatestatus;

    QDateTime           m_startTime;

    qint64              m_lastTimeActivity;
    QTimer              m_idleTimer;

    CBillDetail m_Bills;    // ds hoa don cho thanh toan

    QString sid_amount;
    QString sid_cardid;
    int sid_paymod;
    int     m_progstatus;   // login & baocao processing status
    QString m_bcDate;       // date bao cao "" or "2017-03-24"
    int     m_bcType;       // baocaoX=0, baocaoZ=1, baocaoDetail=2
    QString m_usrPwd;       // user's login password
    bool    m_login4Baocao;
    QProcess* ps_telnet_domino;
public:
    QString httpTranspro;   // http / https
    QString wsTranspro;     // ws / wss
    QString appTitle;       // "Canteen VNG"
    QString merchantCode;   // "vpos"
    QString machineName;    // "May-1"
    bool    cardWaitingPay; // đang chờ thanh toán ...

private:
    QString cmd_apiitem;
    QString cmd_appinvce;
    QString cmd_getlastupdate;
    QString cmd_getlist;
    QString cmd_getsession;
    QString cmd_paymentsuccess;
    QString cmd_token;

    QString gVPOS1();
};

#endif // MAINCONTROLLER_H
