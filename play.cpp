#include "play.h"
#include <QImage>
#include <QEventLoop>
#include <QPixmap>
#include "mainwindowpleer.h"  // Добавляем, чтобы использовать методы MainWindowPleer

void Play::stopCurTrack()
{
    player_.stop();
}

void Play::loadCoverArt(const QString &filePath)
{
    if (!mainWindow_) return;  // Проверяем, что указатель не null

    QMediaPlayer mediaPlayer;
    mediaPlayer.setSource(QUrl::fromLocalFile(filePath));

    // Ожидание загрузки метаданных
    QEventLoop loop;
    connect(&mediaPlayer, &QMediaPlayer::metaDataChanged, &loop, &QEventLoop::quit);
    mediaPlayer.play();
    loop.exec();
    mediaPlayer.stop();

    // Извлекаем метаданные
    QMediaMetaData metadata = mediaPlayer.metaData();

    // Проверка наличия миниатюры (обложки)
    QVariant thumbnailVariant = metadata.value(QMediaMetaData::ThumbnailImage);
    if (thumbnailVariant.isValid()) {
        QImage coverImage = thumbnailVariant.value<QImage>();
        if (!coverImage.isNull()) {
            qDebug() << "Cover art loaded successfully.";
            QPixmap coverPixmap = QPixmap::fromImage(coverImage);
            mainWindow_->backgroundLabel_->setPixmap(coverPixmap);
            mainWindow_->backgroundLabel_->setAlignment(Qt::AlignCenter);
            mainWindow_->backgroundLabel_->setScaledContents(true);
            mainWindow_->backgroundLabel_->setGeometry(0, 0, mainWindow_->getFrameWidth(), mainWindow_->getFrameHeight());
        } else {
            qDebug() << "Cover art is null.";
        }
    } else {
        qDebug() << "No cover art found.";
        mainWindow_->backgroundLabel_->setPixmap(QPixmap(":/Images/jinx.jpg"));
        mainWindow_->backgroundLabel_->setAlignment(Qt::AlignCenter);
        mainWindow_->backgroundLabel_->setScaledContents(true);
    }
}


void Play::playCurTrack(const QString &filePath)
{
    player_.setAudioOutput(&audio_output_);
    // Установим максимальную громкость.
    audio_output_.setVolume(100);
    player_.setSource(QUrl::fromLocalFile(filePath));
    player_.play();
}
