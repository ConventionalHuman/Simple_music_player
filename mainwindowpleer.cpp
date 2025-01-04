#include "mainwindowpleer.h"
#include "./ui_mainwindowpleer.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

MainWindowPleer::MainWindowPleer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowPleer)
{
    ui->setupUi(this);

    setWindowIcon(QIcon("://Icon/Logo1.png"));
    setWindowTitle("UtochkaKria");

    QMenu *fileMenu = menuBar()->addMenu(tr("Файл")); // Локализуемый текст
    fileMenu->addAction(tr("Открыть"), this, SLOT(onOpen()));
    fileMenu->addAction(tr("Сохранить"), this, SLOT(onSave()));
    fileMenu->addAction(tr("Выход"), this, SLOT(onExit()));

    // Создаем "Вид" и добавляем действия
    QMenu *viewMenu = menuBar()->addMenu(tr("Вид"));
    viewMenu->addAction(tr("Полный экран"), this, SLOT(onFullScreen()));
   // viewMenu->addAction(tr("Показать панель инструментов"), this, SLOT(onToggleToolbar()));

    // Создаем "Помощь" и добавляем действия
    QMenu *helpMenu = menuBar()->addMenu(tr("Помощь"));
    helpMenu->addAction(tr("О программе"), this, SLOT(onAbout()));

    // Опционально: реализуйте слоты (onOpen, onSave, и т.д.) для обработки действий
}

MainWindowPleer::~MainWindowPleer()
{
    delete ui;
}

void MainWindowPleer::onOpen() {
    QMessageBox::information(this, tr("Открыть"), tr("Открыть файл..."));
}

void MainWindowPleer::onSave() {
    QMessageBox::information(this, tr("Сохранить"), tr("Сохранение выполнено."));
}

void MainWindowPleer::onExit() {
    close(); // Закрыть приложение
}

void MainWindowPleer::onFullScreen() {
    if (isFullScreen()) {
        showNormal(); // Выйти из полного экрана
    } else {
        showFullScreen(); // Войти в полноэкранный режим
    }
}

void MainWindowPleer::onToggleToolbar() {
    // Предположим, у вас есть toolbar с именем "toolBar"
    //ui->toolBar->setVisible(!ui->toolBar->isVisible());
}

void MainWindowPleer::onAbout() {
    QMessageBox::about(this, tr("О программе"), tr("Пример приложения на Qt."));
}
