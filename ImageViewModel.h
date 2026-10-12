#pragma once

#include <QObject>
#include <QQmlEngine>
#include "ImageInfo.h"

class ImageViewModel : public QObject {
    // Qt Meta-Object System configuration
    Q_OBJECT // Enables Qt's meta-object features (signals, slots, properties)
    QML_ELEMENT // Registers this C++ class directly as a native QML type via CMake

    // QML can read this properties: imageName, imageWidth, imageHeight
    Q_PROPERTY(QString imageName READ imageName NOTIFY imageChanged)
    Q_PROPERTY(int imageWidth READ imageWidth NOTIFY imageChanged)
    Q_PROPERTY(int imageHeight READ imageHeight NOTIFY imageChanged)

public:
    // Reactive properties exposed to the QML view layer
    explicit ImageViewModel(QObject *parent = nullptr);

    // Read-only getter functions (guaranteed not to modify the object state)
    QString imageName() const;
    int imageWidth() const;
    int imageHeight() const;

    // Invokable method acting as a bridge to receive commands from QML
    Q_INVOKABLE void loadImage(const QString &filePath);

signals:
    // Notifies QML that properties have updated and the UI needs redrawing
    void imageChanged();

private:
    ImageInfo imageInfo; // Encapsulated data model holding the raw information
};
