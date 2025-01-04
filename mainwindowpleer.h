#ifndef MAINWINDOWPLEER_H
#define MAINWINDOWPLEER_H

#include <QMainWindow>

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

private:
    Ui::MainWindowPleer *ui;
protected slots:
    void onOpen();
    void onSave();
    void onExit();
    void onFullScreen();
    void onToggleToolbar();
    void onAbout();
};
#endif // MAINWINDOWPLEER_H
