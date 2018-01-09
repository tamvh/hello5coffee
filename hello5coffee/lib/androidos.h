#ifndef ANDROIDOS_H
#define ANDROIDOS_H

#include <QObject>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QtAndroidExtras/QtAndroidExtras>
#include <QAndroidJniObject>
#include "jni.h"
#endif


class AndroidOs
{
public:
    AndroidOs();

    void    dim();

    void    wakeup();
    void    keepscreen(bool on);

    void    mobiledata(bool enable);

    //bool    isWifiEnable();
    //void    turnWifi(bool on);
    //bool    is3GEnable();
    //void    turn3G(bool on);
};

#endif // ANDROIDOS_H
