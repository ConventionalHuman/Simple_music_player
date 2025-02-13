#ifndef MAINWINDOWPLAYER_H
#define MAINWINDOWPLAYER_H

#include <QMainWindow>
#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include "HoverLabel.h"
#include "play.h"
#include <deque>

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
    Play *play_stop = new Play(this,ui);
    QString path_cur_track_;
    std::deque <HoverLabel*> dq_lb;
protected slots:
    void onOpen();
    void onExit();
    void onAbout();
    void buttonPlayClicked();
    void sliderMoved(int position);

};
#endif // MAINWINDOWPLAYER_H
