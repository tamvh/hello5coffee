#ifndef UTILITY_H
#define UTILITY_H
#include <QObject>
#include "http/httpbase.h"
#include "http/httpbase2.h"

#define SL_SERVERURL    "https://gbcstaging.zing.vn"
#define SL_LOG          "/logging/?"

class Utility : QObject
{
    Q_OBJECT
public:
    explicit Utility(QObject *parent = 0);
    ~Utility();
public:
    static void writeLog(const QString msg);
    static void ping(const QString content);
public slots:
    void onGetWriteLogDone(const QVariant &data);
signals:

private:
    HttpBase* httpPing;
    HttpBase* httpLog;
};

#endif // UTILITY_H
