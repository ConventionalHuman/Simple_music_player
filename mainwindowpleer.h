#ifndef MAINWINDOWPLAYER_H
#define MAINWINDOWPLAYER_H

#include <QMainWindow>
#include <QStringList>
#include <QPushButton>
#include <QLabel>

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
    void addTrackInTable(const QStringList &files);
    void updateIconColor(const QString &iconPath, QPushButton *button, const QString &iconColor);
    void initializeDatabase();
    void loadCoverArt(const QString &filePath);
private:
    Ui::MainWindowPleer *ui;
    QLabel *backgroundLabel_;
protected slots:
    void onOpen();
    void onExit();
    void onAbout();
};
#endif // MAINWINDOWPLAYER_H
