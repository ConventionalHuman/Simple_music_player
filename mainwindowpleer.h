#ifndef MAINWINDOWPLAYER_H
#define MAINWINDOWPLAYER_H

#include <QMainWindow>
#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include "HoverLabel.h"
#include "play.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowPleer;
}
QT_END_NAMESPACE

class MainWindowPleer : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowPleer(QWidget *parent = nullptr);
    ~MainWindowPleer();
    void disableColomTable();
    void addTrackInTable(const QStringList &files);
    void updateIconColor(const QString &iconPath, QPushButton *button, const QString &iconColor);
    void initializeDatabase();//class DbMp
    //void loadCoverArt(const QString &filePath);//class Play
    QLabel *backgroundLabel_;
    int getFrameWidth(){
        return width_frame_;
    };
    int getFrameHeight(){
        return height_frame_;
    };
private:
    Ui::MainWindowPleer *ui;
    HoverLabel *playLabel_;
    int width_frame_;
    int height_frame_;
    bool is_play_ = false;
    Play *play_stop;
    QString first_tr_path;
protected slots:
    void onOpen();
    void onExit();
    void onAbout();
    void buttonPlayClicked();
};
#endif // MAINWINDOWPLAYER_H
