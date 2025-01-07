#ifndef MAINWINDOWPLEER_H
#define MAINWINDOWPLEER_H

#include <QMainWindow>
#include <QStringList>
#include <QPushButton>

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
    QStringList table_labels;
    void disableColomTable();
    void addTrackInTable();
    void updateIconColor(const QString &iconPath, QPushButton *button, const QString &iconColor);

private:
    Ui::MainWindowPleer *ui;
protected slots:
    void onOpen();
    void onExit();
    void onAbout();
};
#endif // MAINWINDOWPLEER_H
