#include "functionutils.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

FunctionUtils::FunctionUtils(QObject *parent) : QObject(parent)
{

}

QJsonObject FunctionUtils::convertXmlToJson(const QString &xmlText, const QString &fromNode)
{
    QDomDocument doc;
    doc.setContent(xmlText);
    QDomNodeList nodeList = doc.elementsByTagName(fromNode);
    if (nodeList.size() > 0) {
        return convertXmlToJson(nodeList.at(0));
    }
    return QJsonObject();
}

QJsonObject FunctionUtils::convertXmlToJson(const QDomNode &xmlNode)
{
    QJsonObject resultJson;
    QJsonObject jsonInfo;
    convertNode(xmlNode, jsonInfo);
    resultJson[xmlNode.nodeName()] = jsonInfo;
    return resultJson;
}

bool FunctionUtils::checkChildTextNodeXml(const QDomNode &xmlNode)
{
    if (xmlNode.childNodes().size() == 1) {
        return xmlNode.childNodes().at(0).nodeType() == QDomNode::NodeType::TextNode;
    }
    return false;
}

void FunctionUtils::analyticNodeList(const QDomNode &xmlNode, QHash<QString, int> &multiNodeHash, QHash<QString, int> &singleNodeHash)
{
    const QDomNodeList nodeList = xmlNode.childNodes();
    for (int i = 0; i < nodeList.size(); i++) {
        if (multiNodeHash.contains(nodeList.at(i).nodeName()) == false &&
                singleNodeHash.contains(nodeList.at(i).nodeName()) == false) {
            singleNodeHash[nodeList.at(i).nodeName()] = 1;
        } else if (singleNodeHash.contains(nodeList.at(i).nodeName()) == false){
            multiNodeHash[nodeList.at(i).nodeName()] += 1;
        } else {
            singleNodeHash.remove(nodeList.at(i).nodeName());
            multiNodeHash[nodeList.at(i).nodeName()] = 2;
        }
    }
}

bool FunctionUtils::convertNode(const QDomNode &xmlNode, QJsonObject &resultJson)
{
    bool hasAttr = convertAttributeXml(xmlNode, resultJson);
    if (checkChildTextNodeXml(xmlNode)) {
        if (hasAttr) {
            resultJson["#text"] = xmlNode.childNodes().at(0).nodeValue();
        } else {
            resultJson[xmlNode.nodeName()] = xmlNode.childNodes().at(0).nodeValue();
        }

        return true;
    }

    QHash<QString, int> multiNodeHash;
    QHash<QString, int> singleNodeHash;
    analyticNodeList(xmlNode, multiNodeHash, singleNodeHash);

    QDomNodeList childs = xmlNode.childNodes();
    for (int i = 0 ; i < childs.size(); i++) {
        if (multiNodeHash.contains(childs.at(i).nodeName()) == true) {
            QJsonArray jsonArr;
            if (!resultJson[childs.at(i).nodeName()].isNull()) {
                jsonArr = resultJson[childs.at(i).nodeName()].toArray();
            }

            if (checkChildTextNodeXml(childs.at(i))) {
                jsonArr.append(childs.at(i).childNodes().at(0).nodeValue());
            } else {
                QJsonObject jsonEle;
                convertNode(childs.at(i), jsonEle);
                jsonArr.append(jsonEle);
            }
            resultJson[childs.at(i).nodeName()] = jsonArr;
        } else {
            if (checkChildTextNodeXml(childs.at(i))) {
                convertNode(childs.at(i), resultJson);
            } else {
                QJsonObject jsonEle;
                convertNode(childs.at(i), jsonEle);
                if (!jsonEle.isEmpty()) {
                    resultJson[childs.at(i).nodeName()] = jsonEle;
                } else {
                    resultJson[childs.at(i).nodeName()] = "";
                }

            }
        }
    }

    return true;
}

bool FunctionUtils::convertAttributeXml(const QDomNode &xmlNode, QJsonObject &resultJson)
{
    const QDomNamedNodeMap attributes = xmlNode.attributes();
    bool hasAtt = false;
    for (int i = 0; i < attributes.size(); i++) {
        resultJson["@" + attributes.item(i).nodeName()] = attributes.item(i).nodeValue();
        hasAtt = true;
    }

    return hasAtt;
}

QDomDocument FunctionUtils::convertJsonToXml(const QJsonDocument &infoJson)
{
    QDomDocument doc;
    if (infoJson.isObject() && infoJson.object().size() == 1) {
        QDomElement ele = doc.createElement(infoJson.object().begin().key());
        convertQJson(infoJson.object().begin().value(), doc, ele);
        doc.appendChild(ele);
    }

    return doc;
}

bool FunctionUtils::convertQJson(const QJsonValue &infoJson, QDomDocument &doc, QDomNode &xmlNode)
{
    if (infoJson.isObject()) {
        const QJsonObject jsonObj = infoJson.toObject();
        for (QJsonObject::const_iterator it = jsonObj.begin(); it != jsonObj.end(); it++) {
            if (it.value().isObject()) {
                QDomElement childNode = doc.createElement(it.key());
                convertQJson(it.value(), doc, childNode);
                xmlNode.appendChild(childNode);
            } else if (it.value().isArray()) {
                const QJsonArray jsonArr = it.value().toArray();
                for (int i = 0; i < jsonArr.size(); i++) {
                    QDomElement childNode = doc.createElement(it.key());
                    convertQJson(jsonArr[i], doc, childNode);
                    xmlNode.appendChild(childNode);
                }
            } else if (it.value().isNull()) {
                xmlNode.appendChild(doc.createElement(it.key()));
            } else if (!it.value().isUndefined()) {
                if (checkIsAttribute(it.key())) {
                    xmlNode.toElement().setAttribute(it.key().mid(1),it.value().toString());
                } else if (checkIsTextNode(it.key())) {
                    xmlNode.appendChild(doc.createTextNode(getValue(it.value())));
                } else {
                    QDomElement childNode = doc.createElement(it.key());
                    childNode.appendChild(doc.createTextNode(getValue(it.value())));
                    xmlNode.appendChild(childNode);
                }
            }
        }

    } else if (infoJson.isArray()) {

    } else if (infoJson.isBool() || infoJson.isDouble() || infoJson.isString()){
        xmlNode.appendChild(doc.createTextNode(getValue(infoJson)));
    }
    return false;
}

bool FunctionUtils::checkIsAttribute(const QString &name)
{
    if (name.length() > 0) {
        return name.at(0) == '@';
    }
    return false;
}

bool FunctionUtils::checkIsTextNode(const QString &name)
{
    return name.compare("#text") == 0;
}

QString FunctionUtils::getValue(const QJsonValue &infoJson)
{
    QString data = "";
    switch (infoJson.type()) {
    case QJsonValue::Type::Bool:
        data = QString::number(infoJson.toBool());
        break;
    case QJsonValue::Type::Double:
        data = QString::number(infoJson.toDouble());
        break;
    case QJsonValue::Type::String:
        data = infoJson.toString();
        break;

    }
    return data;
}
