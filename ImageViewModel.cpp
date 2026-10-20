#include "ImageViewModel.h"

ImageViewModel::ImageViewModel(QObject *parent) : QObject(parent) {
}

ImageViewModel::ImageState ImageViewModel::imageState() const {
    return m_imageState;
}

QUrl ImageViewModel::imageUrl() const {
    return m_imageUrl;
}

QString ImageViewModel::errorText() const {
    return m_errorText;
}

QString ImageViewModel::imageName() const {
    return QString::fromStdString(m_imageInfo.name);
}

int ImageViewModel::imageWidth() const {
    return m_imageInfo.width;
}

int ImageViewModel::imageHeight() const {
    return m_imageInfo.height;
}

void ImageViewModel::resetImageData() {
    m_errorText = "";
    m_imageInfo = ImageInfo();
    m_imageState = ImageState::NotLoaded;
    m_imageUrl = QUrl();
}

void ImageViewModel::setLoadingState() {
    resetImageData();
    m_imageState = ImageState::Loading;
    emit imageChanged();
}

void ImageViewModel::setSuccessState() {
    m_imageState = ImageState::Success;
    emit imageChanged();
}

void ImageViewModel::setErrorState(const QString &additionalErrorMessage) {
    resetImageData();
    m_imageState = ImageState::Error;
    m_errorText = "Error: " + additionalErrorMessage;
    emit imageChanged();
}

void ImageViewModel::loadImage(const QUrl &imageUrl) {

    setLoadingState();

    QString localPath = imageUrl.toLocalFile();
    if (localPath.isEmpty()) {
        setErrorState("not a local file");
        return;
    }

    auto result = m_imageLoader.load(localPath.toStdString());

    if (auto* info = std::get_if<ImageInfo>(&result)) {
        m_imageInfo = *info;

        // QML needs the url first, otherwise it can never call reportImageLoaded
        m_imageUrl = imageUrl;
        emit imageChanged();
        return;
    }
    else if (auto* errorMessage = std::get_if<std::string>(&result)) {
        setErrorState(QString::fromStdString(*errorMessage));
        return;
    }
    else {
        setErrorState("unknown error");
        return;
    }
}

void ImageViewModel::reportImageLoaded() {
    setSuccessState();
}

void ImageViewModel::reportImageLoadError() {
    setErrorState("cannot load image file");
}