#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include "qmldefine.h"
#include "maincontroller.h"
#include "../common/configsetting.h"

#ifdef USE_SYSLOG
#include <syslog.h>
// Handler for Qt log messages that sends output to syslog as well as standard error.
void SyslogMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context)
    QByteArray localMsg = msg.toLocal8Bit();
      switch (type) {
      case QtDebugMsg:
          syslog(LOG_DEBUG, "D[%s]: %s", context.category, localMsg.constData());
          break;
      case QtInfoMsg:
          syslog(LOG_INFO, "I[%s]: %s", context.category, localMsg.constData());
          break;
      case QtWarningMsg:
          syslog(LOG_WARNING, "W[%s]: %s", context.category, localMsg.constData());
          break;
      case QtCriticalMsg:
          syslog(LOG_CRIT, "C[%s]: %s", context.category, localMsg.constData());
          break;
      case QtFatalMsg:
          syslog(LOG_ALERT, "F[%s]: %s", context.category, localMsg.constData());
          abort();
      }
}
#endif

int main(int argc, char *argv[])
{
#ifdef USE_SYSLOG
    openlog ("vpos", LOG_CONS | LOG_PID | LOG_NDELAY | LOG_PERROR, LOG_LOCAL1);
    // Install our message handler.
    qInstallMessageHandler(SyslogMessageHandler);
#endif

//#ifdef USE_VT_KB
//    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
//#endif
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qDebug() << "VPOS started!!!";

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<MainController>("MainController", 1, 0, "MainController");
    qmlRegisterType<QmlDefine>("QmlDefine", 1, 0, "QmlDefine");

    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;

    #ifdef USE_VT_KB
        engine.load(QUrl(QLatin1String("qrc:/pi-main.qml")));
    #else
        engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    #endif

#ifdef USE_SYSLOG
    int ret = app.exec();
    qDebug() << "VPOS stopped!!!";
    closelog();
    return ret;
#else
    return app.exec();
#endif

}
