#include "qmldefine.h"

QmlDefine::QmlDefine(QObject *parent) : QObject(parent)
{

}

QString QmlDefine::appVersion()
{
#ifdef APP_FULL
    return QString(APP_VER) + "-full";
#else
    return APP_VER;
#endif
}

bool QmlDefine::appFull()
{
#ifdef APP_FULL
    return true;
#else
    return false;
#endif
}

QString QmlDefine::buildDate()
{
    return QString::fromUtf8("%1 - %2").arg(__DATE__).arg(__TIME__);
}
