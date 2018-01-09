/*import QtQuick 2.0
import Material 0.2

TabbedPage {
    Rectangle {
        anchors.fill: parent
        color: Palette.colors.purple["200"]
    }
}*/

/*
 * QML Material - An application framework implementing Material Design.
 * Copyright (C) 2015 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.4
import QtQuick.Controls 1.1
import Material 0.2
import Material.ListItems 0.1 as ListItem

Item {

    Rectangle {
        anchors.fill: parent
        border.color: "#BDBDBD"
        border.width: 1

        Grid {
            anchors.fill: parent
            columns: 2
            ItemViewDetail {
                name: "Mì xào bò"
                image: "qrc:/images/mibo.jpg"
                price: "30,000"
            }

            ItemViewDetail {
                name: "Cà phê đá"
                image: "qrc:/images/cafe_denda.jpg"
                price: "10,000"
            }

            ItemViewDetail {
                name: "Cơm chiên trứng"
                image: "qrc:/images/comchientrung.jpg"
                price: "30,000"
            }

            ItemViewDetail {
                name: "Cà phê sữa"
                image: "qrc:/images/cafemilk.jpg"
                price: "15,000"
            }

            ItemViewDetail {
                name: "Muc nuong"
                image: "qrc:/images/muc_nuong.jpg"
                price: "25,000"
            }

            ItemViewDetail {
                name: "Mi xao"
                image: "qrc:/images/mixaohsan.jpg"
                price: "30,000"
            }
        }
    }

}
