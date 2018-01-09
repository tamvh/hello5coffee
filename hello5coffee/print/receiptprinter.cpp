#include "receiptprinter.h"
#include <QLocale>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ReceiptPrinter::ReceiptPrinter()
{

}

ReceiptPrinter::ReceiptPrinter(QString printerName, QString data)
{
    QJsonDocument jsonResponse = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    _printerName = printerName;
    _receiptNum = jsonObject["receiptNum"].toString();
    _dateTime = jsonObject["datetime"].toString();
    _total = jsonObject["total"].toString();
    QJsonArray jsonArray = jsonObject["item"].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        _itemDataList.append(ReceiptData(obj["name"].toString(), obj["price"].toString(),
                obj["quantity"].toString(), obj["amount"].toString()));
    }
}

ReceiptPrinter::ReceiptPrinter(QString printerName, QString receiptNum, QString dateTime, QList<ReceiptData> itemdata)
{
    _printerName = printerName;
    _receiptNum = receiptNum;
    _dateTime = dateTime;
    _itemDataList = itemdata;
}

bool ReceiptPrinter::print()
{
#if 0
    _printer.setPrinterName(_printerName);

    if(!_printer.isValid()){
        return false;
    }

    _printer.setFullPage(true);
    _printer.setPageSize(QPrinter::Custom);
    _printer.setPageSizeMM(QSizeF(52,120));
    _printer.setResolution(110);
    _printer.setPageMargins(0,0,5,4,QPrinter::Millimeter);
    _printer.setColorMode(QPrinter::ColorMode::GrayScale);

    _document.setHtml(generateContent());
    _document.setPageSize(QSizeF(_printer.pageRect().size()));
    _document.print(&_printer);
#endif
    return true;
}

QString ReceiptPrinter::generateContent()
{
    QString content = "";
    content = content + "<html>"
            + "<head>"
            + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">"
            + "<style>table { table-layout: fixed; }</style>"
            + "</head>"
            + "<body><div>"
            + "<table>"
            + "<tr><td colspan=\"2\" style='white-space: pre'>==============================================</td></tr>"
            + "<tr style='font-size: 8pt;'>"
            + "<tr><td colspan=\"2\" align='center'><h3>HÓA ĐƠN DỊCH VỤ</h3></td></tr>"
            + "<tr style='font-size: 8pt;'>"
            + "<tr><td width='35%' style='white-space: pre;'>Số hóa đơn: </td>"
            + "<td><font style='font-weight: bold;'>" + _receiptNum + "</font></td></tr>"
            + "<tr><td>Ngày: </td><td>" + _dateTime + "</td></tr>"
            + "<tr style='font-size: 8pt;'>"
            + "<tr><td colspan=\"2\">"
            + "<table cellpadding=\"3\" width='100%'>"
            + "<tr><td style='white-space: pre; font-style:italic;' width='30%' align='left'>Đơn giá</td>"
            + "<td style='white-space: pre; font-style:italic;' width='30%' align='right'>Số lượng</td>"
            + "<td style='white-space: pre; font-style:italic;' width='40%' align='right'>Số tiền</td></tr>";

    for(int i = 0; i < _itemDataList.size(); i++)
    {
        content = content
            + "<tr><td colspan='3'><font style='font-weight: bold;'>" + _itemDataList.at(i).name + "</font></td></tr>"
            + "<tr><td>" + _itemDataList.at(i).price + "</td><td align='right'>" + _itemDataList.at(i).quantity + "</td>"
            + "<td align='right'>" + _itemDataList.at(i).amount + "</td></tr>";
    }

    content = content
            + "<tr style='font-size: 8pt;'>"
            + "<tr><td colspan='2'><font style='font-size: 10pt;'>Thành tiền</font></td>"
            + "<td align='right'><font style='font-weight: bold;'>" + _total + "</font></td></tr>"
            + "</table>"
            + "</td></tr>"
            + "<tr style='font-size: 8pt;'>"
            + "<tr><td colspan=\"2\" style='white-space: pre'>..............................................</td></tr>"
            + "</table>"
            + "</div></body>"
            + "</html>";

    qDebug() << "Content: " << content;
    return content;
}


