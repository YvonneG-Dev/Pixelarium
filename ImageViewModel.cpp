#include "ImageViewModel.h"
#include <QImageReader>
#include <QFileInfo>

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
    return m_imageInfo.name;
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

void ImageViewModel::setErrorState(const QString &additionalErrorMessage) {
    m_imageState = ImageState::Error;
    m_errorText = "Error: " + additionalErrorMessage;
    emit imageChanged();
}

void ImageViewModel::loadImage(const QUrl &imageUrl) {

    resetImageData();

    QString localPath = imageUrl.toLocalFile();

    if (localPath.isEmpty()) {
        setErrorState("not a local file");
        return;
    }

    QImageReader reader(localPath);
    if (!reader.canRead()) {
        setErrorState("cannot read image file");
        return;
    }

    QSize imageSize = reader.size();
    m_imageInfo.name = QFileInfo(localPath).fileName();
    m_imageInfo.width = imageSize.isValid() ? imageSize.width() : 0;
    m_imageInfo.height = imageSize.isValid() ? imageSize.height() : 0;
    m_imageUrl = imageUrl;
    m_imageState = ImageState::Success;
    emit imageChanged();
}