#ifndef FUNCTIONUTILS_H
#define FUNCTIONUTILS_H

#include <QObject>
#include <QDomDocument>
#include <QDomElement>
#include <QJsonDocument>
#include <QJsonObject>

class FunctionUtils : public QObject
{
    Q_OBJECT
public:
    explicit FunctionUtils(QObject *parent = 0);
    static QJsonObject convertXmlToJson(const QString &xmlText, const QString &fromNode = "");
    static QJsonObject convertXmlToJson(const QDomNode &xmlNode);

    static QDomDocument convertJsonToXml(const QJsonDocument &infoJson);

signals:

public slots:

private:
    static bool checkChildTextNodeXml(const QDomNode &xmlNode);
    static void analyticNodeList(const QDomNode &xmlNode, QHash<QString, int> &xmlArrayNodeList, QHash<QString, int> &xmlObjectNodeList);

    static bool convertNode(const QDomNode &xmlNode, QJsonObject &resultJson);
    static bool convertAttributeXml(const QDomNode &xmlNode, QJsonObject &resultJson);

    static bool checkIsAttribute(const QString &name);
    static bool checkIsTextNode(const QString &name);
    static QString getValue(const QJsonValue &infoJson);

    static bool convertQJson(const QJsonValue &infoJson, QDomDocument &doc, QDomNode &xmlNode);
};

#endif // FUNCTIONUTILS_H
