#include "ImageViewModel.h"
#include <QImageReader>
#include <QUrl>
#include <QFileInfo>

ImageViewModel::ImageViewModel(QObject *parent) : QObject(parent) {
}


QString ImageViewModel::imageName() const {
    return imageInfo.name;
}

int ImageViewModel::imageWidth() const {
    return imageInfo.width;
}

int ImageViewModel::imageHeight() const {
    return imageInfo.height;
}

void ImageViewModel::loadImage(const QString &filePath) {

    if (filePath.isEmpty()) {
        return;
    }

    // clean image path
    QString localPath = QUrl(filePath).toLocalFile();
    if (localPath.isEmpty()) {
        localPath = filePath;
    }
    QImageReader reader(localPath);
    if (!reader.canRead()) {
        return;
    }

    imageInfo.name = QFileInfo(localPath).fileName();
    imageInfo.width = reader.size().width();
    imageInfo.height = reader.size().height();

    emit imageChanged();
}