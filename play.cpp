#include "play.h"
#include <QImage>
#include <QEventLoop>
#include <QPixmap>
#include "mainwindowpleer.h"  // Добавляем, чтобы использовать методы MainWindowPleer

Play::Play(MainWindowPleer *mainWindow, Ui::MainWindowPleer *ui, QObject *parent)
    : QObject(parent), mainWindow_(mainWindow), ui_(ui) {

    player_.setAudioOutput(&audio_output_);
    // Установим максимальную громкость.
    audio_output_.setVolume(100);

    connect(updateTimer_, &QTimer::timeout, this, &Play::updateTrackProgress);
    // Обновляем слайдер каждую секунду
    connect(updateTimer_, &QTimer::timeout, this, &Play::updateSlider);
}

void Play::stopCurTrack()
{
    player_.pause();
    updateTimer_->stop(); // Останавливаем таймер
}

void Play::updateTrackProgress()
{
    qint64 currentPosition = player_.position(); // Получаем текущую позицию трека
    QString currentTime = QTime(0, 0).addMSecs(currentPosition).toString("mm:ss");

    // Обновляем лейбл текущего времени
    ui_->LabelBegin->setText(currentTime);
    updateRemainingTime();
}

void Play::updateRemainingTime()
{
    qint64 currentPosition = player_.position();
    qint64 totalDuration = player_.duration(); // Общая длительность трека

    if (totalDuration > 0) {
        qint64 remainingTime = totalDuration - currentPosition;
        QString remainingTimeStr = QTime(0, 0).addMSecs(remainingTime).toString("mm:ss");

        // Обновляем лейбл оставшегося времени
        ui_->labelEnd->setText(remainingTimeStr);
    }
}

void Play::sliderMoved(int position)
{
    qint64 totalDuration = player_.duration();
    if (totalDuration > 0) {
        qint64 newPosition = (totalDuration * position) / 100; // Пересчет в миллисекунды
        player_.setPosition(newPosition); // Устанавливаем новую позицию трека
    }
}

void Play::updateSlider()
{
    qint64 currentPosition = player_.position(); // Получаем текущую позицию трека
    qint64 totalDuration = player_.duration();

    if (totalDuration > 0) {
        int sliderValue = static_cast<int>((currentPosition * 100) / totalDuration);
        ui_->horizontalSlider->setValue(sliderValue); // Обновляем значение слайдера
    }
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
    QString title = metadata.stringValue(QMediaMetaData::Title);
    QString artist = metadata.stringValue(QMediaMetaData::ContributingArtist);
    QString duration = QTime(0, 0).addMSecs(mediaPlayer.duration()).toString("mm:ss");
    ui_->labelTitle->setText(title);
    ui_->labelArtist->setText(artist);

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
    // Проверка, является ли текущий трек тем же самым
    if (player_.source().toString() == QUrl::fromLocalFile(filePath).toString()) {
        // Если трек на паузе, продолжаем воспроизведение
        if (player_.playbackState() == QMediaPlayer::PausedState) {
            player_.play();  // Продолжаем с текущей позиции
            return;
        }
    } else {
        // Новый трек, загружаем его
        player_.setSource(QUrl::fromLocalFile(filePath));
        player_.play();
    }

    // Запуск таймера для обновления информации о треке каждые 500 мс
    updateTimer_->start(100);
}
