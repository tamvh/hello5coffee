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
import Material 0.2
import Material.ListItems 0.1 as ListItem

Page {
    id: page
    title: "Domino"

    Row {
        anchors.fill: parent

        ItemGridView {
            id: itemGrid
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width*2/5
            height: parent.height
        }

        Column {
            anchors.top: parent.top
            anchors.left: itemGrid.right
            anchors.right: parent.right
            height: parent.height

            ChoosenItemListView {
                id: choosenItemListView
                anchors.top: parent.top
                anchors.left: parent.left
                width: parent.width
                height: parent.height/2
            }

            PaymentView {
                id: paymentView
                anchors.top: choosenItemListView.bottom
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: parent.width
            }
        }
    }
}
