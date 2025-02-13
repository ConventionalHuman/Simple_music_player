#ifndef PLAY_H
#define PLAY_H

#include <QObject>
#include <QString>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaMetaData>
#include <QtMultimedia/QAudioOutput>
#include "./ui_mainwindowpleer.h"
#include <QTime>
#include <QTimer>

class MainWindowPleer;  // Предварительное объявление

class Play: public QObject
{
    Q_OBJECT
public:
    explicit Play(MainWindowPleer *mainWindow, Ui::MainWindowPleer *ui, QObject *parent = nullptr);
    Play() = delete;
    void stopCurTrack();
    void loadCoverArt(const QString &filePath);
    void playCurTrack(const QString &filePath);
    void updateRemainingTime();
    void sliderMoved(int position);
protected slots:
    void updateTrackProgress();
    void updateSlider();
private:
    QTimer *updateTimer_ = new QTimer(this);
    QMediaPlayer player_;
    QAudioOutput audio_output_{this};
    MainWindowPleer *mainWindow_; // Указатель на главное окно
    Ui::MainWindowPleer *ui_;
};

#endif // PLAY_H
