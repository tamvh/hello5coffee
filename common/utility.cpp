#include "utility.h"

Utility::Utility(QObject *parent)
    : QObject(parent)
{
    httpLog = NULL;
    httpPing = NULL;

}

Utility::~Utility() {

}

void Utility::writeLog(const QString msg) {
    httpLog = new HttpBase(QString(""), this);
    QObject::connect(httpLog, SIGNAL(done(QVariant)), this, SLOT(onGetWriteLogDone(QVariant)), Qt::UniqueConnection);
    QObject::connect(httpLog, SIGNAL(done(QVariant)), httpLog, SLOT(deleteLater()));
    QObject::connect(httpLog, SIGNAL(error(int,QString)), httpLog, SLOT(deleteLater()));
    httpLog->setUrl(QUrl(QString("%1%2").arg(SL_SERVERURL).arg(SL_LOG)));
    httpLog->addParameter("cm", "getlist_mobile", true);
    httpLog->process();
}

void Utility::onGetWriteLogDone(const QVariant &data) {

}

void Utility::ping(const QString content) {

}
