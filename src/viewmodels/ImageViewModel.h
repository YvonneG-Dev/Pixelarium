#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QUrl>
#include "../model/ImageInfo.h"
#include "../core/ImageLoader.h"

class ImageViewModel : public QObject {
    // Qt Meta-Object System configuration
    Q_OBJECT // Enables Qt's meta-object features (signals, slots, properties)
    QML_ELEMENT // Registers this C++ class directly as a native QML type via CMake

    // readable for QML
    Q_PROPERTY(ImageState imageState READ imageState NOTIFY imageChanged)
    Q_PROPERTY(QUrl imageUrl READ imageUrl NOTIFY imageChanged)
    Q_PROPERTY(QString errorText READ errorText NOTIFY imageChanged)
    Q_PROPERTY(QString imageName READ imageName NOTIFY imageChanged)
    Q_PROPERTY(int imageWidth READ imageWidth NOTIFY imageChanged)
    Q_PROPERTY(int imageHeight READ imageHeight NOTIFY imageChanged)

public:
    // Reactive properties exposed to the QML view layer
    explicit ImageViewModel(QObject *parent = nullptr);

    // Image state machine to update view
    enum class ImageState {
        NotLoaded,
        Loading,
        Success,
        Error
    };

    // Read-only getter functions (guaranteed not to modify the object state)
    ImageState imageState() const;
    QUrl imageUrl() const;
    QString errorText() const;
    QString imageName() const;
    int imageWidth() const;
    int imageHeight() const;

    // Register Enum to QT
    Q_ENUM(ImageState)

    // Invokable method acting as a bridge to receive commands from QML
    Q_INVOKABLE void loadImage(const QUrl &imageUrl);
    Q_INVOKABLE void reportImageLoaded();
    Q_INVOKABLE void reportImageLoadError();

signals:
    // Notifies QML that properties have updated and the UI needs redrawing
    void imageChanged();

private:
    QUrl m_imageUrl;
    ImageInfo m_imageInfo; // Encapsulated data model holding the raw information
    ImageState m_imageState = ImageState::NotLoaded;
    QString m_errorText;
    ImageLoader m_imageLoader;

    void resetImageData();
    void setLoadingState();
    void setSuccessState();
    void setErrorState(const QString &additionalErrorMessage);
};
