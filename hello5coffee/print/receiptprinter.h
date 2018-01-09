#ifndef RECEIPTPRINTER_H
#define RECEIPTPRINTER_H

#include <QObject>
#include <QTextDocument>
//#include <QPrinter>
//#include <QPrinterInfo>

struct ReceiptData {
    ReceiptData(QString name, QString price, QString quantity, QString amount)
    {
        this->name = name;
        this->price = price;
        this->quantity = quantity;
        this->amount = amount;
    }

    QString    name;
    QString    price;
    QString    quantity;
    QString    amount;
};

class ReceiptPrinter : public QObject
{
public:
    ReceiptPrinter();
    ReceiptPrinter(QString printerName, QString data);
    ReceiptPrinter(QString printerName, QString receiptNum, QString dateTime, QList<ReceiptData> itemdata);

    bool print();
private:
    QString generateContent();
private:
    QString             _receiptNum;
    QString             _printerName;
    QString             _dateTime;
    QString             _total;
    QList<ReceiptData>  _itemDataList;
    QTextDocument       _document;
    //QPrinter            _printer;
};

#endif // PRINTDATA_H
