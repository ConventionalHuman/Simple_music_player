#ifndef PLAY_H
#define PLAY_H

#include <QObject>
#include <QString>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaMetaData>
#include <QtMultimedia/QAudioOutput>

class MainWindowPleer;  // Предварительное объявление

class Play: public QObject
{
    Q_OBJECT
public:
    explicit Play(MainWindowPleer *mainWindow, QObject *parent = nullptr)
        : QObject(parent), mainWindow_(mainWindow) {}
    Play() = delete;
   /* Play(MainWindowPleer *mainWindow, const QString& filePath)
        : mainWindow_(mainWindow) {
        loadCoverArt(filePath);
        playCurTrack(filePath);
    };*/
    void stopCurTrack();
    void loadCoverArt(const QString &filePath);
    void playCurTrack(const QString &filePath);

private:

    QMediaPlayer player_;
    QAudioOutput audio_output_{this};
    MainWindowPleer *mainWindow_; // Указатель на главное окно
};

#endif // PLAY_H
