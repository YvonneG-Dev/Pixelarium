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

    Colors {
        id: colors
        isDark: !window.lightMode
    }
    property bool lightMode: Application.styleHints.colorScheme === Qt.Light

    background: Rectangle {
        color: colors.windowBackground
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        // App Toolbar
        RowLayout {
            spacing: 15

            // Title
            Text {
                text: "Pixelarium"
                font.family: "Avenir Next"
                font.pointSize: 24
                font.bold: true
                color: colors.primaryText

                Layout.alignment: Qt.AlignTop | Qt.AlignLeading
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: window.lightMode ? qsTr("Dark Mode") : qsTr("Light Mode")
                palette.buttonText: colors.primaryText
                onClicked: window.lightMode = !window.lightMode
            }

            Button {
                id: openImageButton
                text: qsTr("Open Image")
                onClicked: {
                    imageDialog.open()
                }

                palette.buttonText: colors.primaryText
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 1
            color: colors.separator
        }

        RowLayout {
            spacing:15


            // Image Placeholder
            Rectangle {
                id: imagePlaceholder
                color: colors.itemBackground
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 3 // 3/4 of the window

                Image {
                    id: loadedImage
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: imageViewModel.imageUrl
                    onStatusChanged: {
                        if (status === Image.Ready) {
                            imageViewModel.reportImageLoaded()
                        } else if (status === Image.Error) {
                            imageViewModel.reportImageLoadError()
                        }
                    }
                    visible: imageViewModel.imageState === ImageViewModel.ImageState.Success
                }

                Text {
                    id: noImageHint
                    color: colors.primaryText
                    text: {
                        switch (imageViewModel.imageState) {
                        case ImageViewModel.ImageState.NotLoaded:
                            return qsTr("No image loaded.")
                        case ImageViewModel.ImageState.Loading:
                            return qsTr("Loading...")
                        case ImageViewModel.ImageState.Success:
                            return ""
                        case ImageViewModel.ImageState.Error:
                            return imageViewModel.errorText
                        default:
                            return ""
                        }
                    }
                    anchors.centerIn: parent
                    visible: imageViewModel.imageState !== ImageViewModel.ImageState.Success
                }
            }

            // Image Data
            Rectangle {
                id: imageDataPlaceholder
                color: colors.itemBackground
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
                        color: colors.primaryText
                        text: qsTr("Image name:")
                    }

                    Text {
                        id: imageName
                        color: colors.primaryText
                        text: imageViewModel.imageName || "-"
                    }

                    Text {
                        id: imageSizeTitle
                        font.bold: true
                        color: colors.primaryText
                        text: qsTr("Image size:")
                    }

                    Text {
                        id: imageSize
                        color: colors.primaryText
                        text: imageViewModel.imageWidth > 0 ?
                              imageViewModel.imageWidth + " x " +
                              imageViewModel.imageHeight + " px" :
                              "-"
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
            imageViewModel.loadImage(imageDialog.selectedFile)
        }
    }
}
