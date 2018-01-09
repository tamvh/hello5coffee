import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Private 1.0
import QtQuick.Layouts 1.1

Rectangle {
    property int iconsize: 325
    property int fontsize: 18

    property int m_colCount: width < iconsize ? 1 : width / iconsize
    property int m_colSpace: width / 25
    property int m_cellw: width / m_colCount
    property int m_cellh: m_cellw+30

    color: "transparent"

    ListModel {
        id: foodsModel
    }

    function append(foodname, price, image, img_cache) {
        var priceString = mainController.moneyMoney(price)
        foodsModel.append({name: foodname, price: priceString, image: image, img_cache: img_cache})
    }

    Flickable {
        anchors.fill: parent

        GridView {
            id: gridItemView
            anchors.fill: parent
            cellWidth: m_cellw
            cellHeight: m_cellh
            focus: true
            model: foodsModel

            highlight: HalfRadiusRectangle {}
            highlightMoveDuration: 0


            // Image w: 310 x h:255
            // Radius w: 350 x h: 310
            delegate: Item {
                id: item
                width: m_cellw
                height: m_cellh-5

                /*Rectangle {
                    anchors.fill: parent
                    anchors.margins: 5
                    color: "transparent"
                }*/
                HalfRadiusRectangle {
                    anchors.fill: parent
                    anchors.margins: 3
                    bottomRadius: 10
                    radiusWidth: 2
                    rcColor: "#E2E6E7"
                }

                Image {
                    id: foodIcon
                    x: 0
                    y: 5
                    fillMode: Image.Stretch
                    width:item.width-10
                    height:259
                    asynchronous: true
                    cache: img_cache


                    anchors.horizontalCenter: parent.horizontalCenter
                    source: image
                }

                Text {
                    id: foodName2
                    anchors { top: foodIcon.bottom; horizontalCenter: parent.horizontalCenter }
                    //text: price
                    color: "#FF0000"
                    font.pixelSize: fontsize - 6
                }

                Text {
                    id:foodName
                    anchors { top: foodName2.bottom; horizontalCenter: parent.horizontalCenter }
                    text: name
                    font.pixelSize: 24
                }

                RowLayout {
                    //top: foodName.bottom
                    anchors.top: foodName.bottom
                    anchors.horizontalCenter: parent.horizontalCenter

                    //horizontalCenter: parent.horizontalCenter

                    Text {
                        //anchors { top: foodName.bottom; }
                        text: price
                        color: "#FF0000"
                        font.pixelSize: 30
                    }

                    Text {
                        //anchors { top: foodName.bottom; }
                        text: "VNĐ"
                        color: "#FF0000"
                        font.pixelSize: 20
                        anchors.bottom: parent.bottom
                        anchors.margins: 4
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        parent.GridView.view.currentIndex = index
                        mainController.insertItem(name, price)

                    }
                }
            }
        }
    }

    Connections {
        target: mainController
        onFoodUpdate: {

            // clear obsolute food data
            foodsModel.clear();

            menus = JSON.parse(menus);
            for(var item in menus.dt.items) {
                append(menus.dt.items[item].item_name,
                       menus.dt.items[item].price,
                       menus.dt.items[item].img_path,
                       menus.dt.items[item].img_cache)
            }
        }
    }
}
