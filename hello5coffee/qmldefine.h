#ifndef QMLDEFINE_H
#define QMLDEFINE_H

#include <QObject>

class QmlDefine : public QObject
{
    Q_OBJECT
public:
    explicit QmlDefine(QObject *parent = 0);

    Q_INVOKABLE QString appVersion();
    Q_INVOKABLE bool appFull();
    Q_INVOKABLE QString buildDate();
signals:

public slots:
};

#endif // QMLDEFINE_H
