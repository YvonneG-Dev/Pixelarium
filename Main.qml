import QtQuick
import QtCore
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import appPixelarium

ApplicationWindow {
    id: window
    width: 640
    height: 480
    minimumWidth: 200
    minimumHeight: 250
    visible: true
    title: qsTr("Pixelarium")

    ImageViewModel {
        id: imageViewModel
    }

    // Colors
    property bool lightMode: Application.styleHints.colorScheme === Qt.Light
    property color reallyDark: "#1f1f1f"
    property color dark: "#262626"
    property color reallyLight: "#e7e7e7"
    property color light: "#e0e0e0"

    background: Rectangle {
        color: window.lightMode ? window.reallyLight : window.reallyDark
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        // Title
        Text {
            text: "Pixelarium"
            font.family: "Avenir Next"
            font.pointSize: 24
            font.bold: true
            color: window.lightMode ? window.reallyDark : window.reallyLight

            Layout.alignment: Qt.AlignTop | Qt.AlignLeading
        }

        RowLayout {
            spacing: 15
            Button {
                id: openImageButton
                text: "Open Image"
                palette.buttonText: window.lightMode ? window.dark : window.light
                onClicked: {
                    imageDialog.open()
                }
            }

            Button {
                text: window.lightMode ? "Dark Mode" : "Light Mode"
                palette.buttonText: window.lightMode ? window.dark : window.light
                onClicked: window.lightMode = !window.lightMode
            }
        }

        RowLayout {
            spacing:15


            // Image Placeholder
            Rectangle {
                id: imagePlaceholder
                color: window.lightMode ? "#f4f4f4" : "#303030"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 3 // 3/4 of the window

                Image {
                    id: loadedImage
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    visible: status === Image.Ready
                }

                Text {
                    id: noImageHint
                    color: window.lightMode ? window.dark : window.light
                    text: qsTr("No image loaded.")
                    anchors.centerIn: parent
                    visible: loadedImage.status !== Image.Ready
                }
            }

            // Image Data
            Rectangle {
                id: imageDataPlaceholder
                color: window.lightMode ? window.reallyLight : window.reallyDark
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 1 // 1/4 of the window

                ColumnLayout {
                    spacing: 15
                    anchors.fill: parent
                    anchors.margins: 15

                    Text {
                        id: imageNameTitle
                        font.bold: true
                        color: window.lightMode ? window.dark : window.light
                        text: qsTr("Image name:")
                    }

                    Text {
                        id: imageName
                        color: window.lightMode ? window.dark : window.light
                        text: qsTr(imageViewModel.imageName ? imageViewModel.imageName : "-")
                    }

                    Text {
                        id: imageSizeTitle
                        font.bold: true
                        color: window.lightMode ? window.dark : window.light
                        text: qsTr("Image size:")
                    }

                    Text {
                        id: imageSize
                        color: window.lightMode ? window.dark : window.light
                        text: qsTr(imageViewModel.imageWidth > 0 ? (imageViewModel.imageWidth + " x " + imageViewModel.imageHeight + " px") : "-")
                    }

                    // Spacer
                    Item {
                        Layout.fillHeight: true
                    }
                }
            }
        }
    }

    FileDialog {
        id: imageDialog
        title: "Choose an image"
        nameFilters: ["Bilddateien (*.png *.jpg *.jpeg *.bmp)"]
        onAccepted: {
            loadedImage.source = imageDialog.selectedFile
            imageViewModel.loadImage(imageDialog.selectedFile.toString())
        }
    }
}
