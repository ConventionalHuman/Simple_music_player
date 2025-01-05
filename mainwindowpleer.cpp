#include "mainwindowpleer.h"
#include "./ui_mainwindowpleer.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QPainter>

MainWindowPleer::MainWindowPleer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowPleer)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/Icon/logo3.png"));
    setWindowTitle("UtochkaKria");
    // Установить фиксированный размер окна
    setFixedSize(1100, 800);
    // Установить стандартное окно и отключить возможность изменения состояния
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    setStyleSheet("background: #0f1725;");

    QMenu *fileMenu = menuBar()->addMenu(tr("Файл")); // Локализуемый текст
    fileMenu->addAction(tr("Открыть"), this, SLOT(onOpen()));
    fileMenu->addAction(tr("Сохранить"), this, SLOT(onSave()));
    fileMenu->addAction(tr("Выход"), this, SLOT(onExit()));

    // Создаем "Вид" и добавляем действия
    QMenu *viewMenu = menuBar()->addMenu(tr("Вид"));
    //viewMenu->addAction(tr("Полный экран"), this, SLOT(onFullScreen()));
   // viewMenu->addAction(tr("Показать панель инструментов"), this, SLOT(onToggleToolbar()));

    // Создаем "Помощь" и добавляем действия
    QMenu *helpMenu = menuBar()->addMenu(tr("Помощь"));
    helpMenu->addAction(tr("О программе"), this, SLOT(onAbout()));

    //pushButtonSearch
    ui->pushButtonSearch->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"    // Прозрачный фон
        "    border: none;"               // Без рамки
        "    color: #484c55;"             // Цвет иконки в обычном состоянии
        "}"
        );
    //фиксация размера кнопки поиска
    ui->pushButtonSearch->setFixedSize(45,35);
    ui->pushButtonSearch->setIcon(QIcon(":/Icon/icon_search.png"));
    QPixmap pixmap(":/Icon/icon_search.png");
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), QColor("#484c55"));
    painter.end();
    ui->pushButtonSearch->setIcon(QIcon(pixmap));
    //QFramePleer
    // Создаём эффект прозрачности
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.2); // Устанавливаем уровень прозрачности (0.0 до 1.0)
    ui->framePleer->setGraphicsEffect(effect);// Применяем эффект к фрейму
    ui->framePleer->setStyleSheet(
        "QFrame {"
        "    background-image: url(:/Images/jinx.jpg);"  // Замените путь на правильный
        "    background-repeat: no-repeat;"                   // Без повторения
        "    background-position: center;"                    // Центрирование изображения
        "    background-color: transparent;"                  // Прозрачный фон (если нужно)
        "}"
        );
    //фиксация размера framePleer
    ui->framePleer->setFixedSize(550,726);

    // LineEditSearch
    ui->lineEditSearch->setStyleSheet(
        "QLineEdit {"
        "    background: transparent;"
        "    border: none;"
        "    border-bottom: 1px solid #484c55;"
        "    color: #484c55;"
        "    padding: 2px;"
        "}"
        "QLineEdit:focus {"
        "    border-bottom: 2px solid #484c55;"
        "}"
        );

    // Установка текста-подсказки
    ui->lineEditSearch->setPlaceholderText("Поиск");

    //QTableWidgetSongs
    // Установка колонок и стилей
    table_labels << "" << "Название" << "Исполнитель" << "";
    ui->tableWidgetSongs->setColumnCount(4);
    ui->tableWidgetSongs->setHorizontalHeaderLabels(table_labels);
    ui->tableWidgetSongs->verticalHeader()->hide();

    // Установка растяжения колонок
    ui->tableWidgetSongs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Удаление вертикальных линий
    ui->tableWidgetSongs->setShowGrid(false);

    // Стиль таблицы
    ui->tableWidgetSongs->setStyleSheet(
        "QTableWidget {"
        "    background: transparent;"
        "    border: none;"
        "    color: #484c55;"
        "    gridline-color: transparent;"   // Убираем линии сетки
        "}"
        "QTableWidget::item {"
        "    border-bottom: 1px solid #484c55;" // Добавляем только нижнюю линию
        "}"
        "QTableWidget::item:hover {"
        "    background-color: #12cea4;"  // Цвет строки при наведении
        "}"
        );

    // Добавление строк с кнопкой Play/Pause
    for (int i = 0; i < 10; ++i) {  // Пример на 10 строк
        ui->tableWidgetSongs->insertRow(i);

        // Создание кнопки и установка иконки
        QPushButton *playButton = new QPushButton;
        playButton->setIcon(QIcon(":/Icon/play.png")); // Изначальная иконка
        playButton->setStyleSheet(
            "QPushButton {"
            "    background: transparent;"
            "    border: none;"
            "} "
            "QPushButton:hover {"
            "    color: #12cea4;"  // Изменение цвета кнопки при наведении
            "} "
            );

        // Функция для изменения цвета иконки
        auto updateIconColor = [](const QString &iconPath, QPushButton *button) {
            QPixmap pixmap(iconPath);
            QPainter painter(&pixmap);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(pixmap.rect(), QColor("#484c55")); // Изменение цвета
            painter.end();
            button->setIcon(QIcon(pixmap));
        };

        // Применяем начальный цвет для иконки play
        updateIconColor(":/Icon/play.png", playButton);

        // Логика изменения иконки Play/Pause
        QObject::connect(playButton, &QPushButton::clicked, [playButton, updateIconColor]() {
            if (playButton->icon().name() == ":/Icon/play.png") {
                // Меняем иконку на паузу и обновляем цвет
                playButton->setIcon(QIcon(":/Icon/pause.png"));
                updateIconColor(":/Icon/pause.png", playButton);
            } else {
                // Меняем иконку на воспроизведение и обновляем цвет
                playButton->setIcon(QIcon(":/Icon/play.png"));
                updateIconColor(":/Icon/play.png", playButton);
            }
        });

        // Добавляем кнопку в ячейку первой колонки
        ui->tableWidgetSongs->setCellWidget(i, 0, playButton);

        // Добавляем содержимое в остальные колонки
        ui->tableWidgetSongs->setItem(i, 1, new QTableWidgetItem("Название трека " + QString::number(i + 1)));
        ui->tableWidgetSongs->setItem(i, 2, new QTableWidgetItem("Исполнитель " + QString::number(i + 1)));
        ui->tableWidgetSongs->setItem(i, 3, new QTableWidgetItem(""));
    }


    // Реакция на изменение текста (опционально)
   /* connect(ui->lineEditSearch, &QLineEdit::textChanged, this, [this]() {
        if (ui->lineEditSearch->text().isEmpty()) {
            ui->lineEditSearch->setPlaceholderText("Поиск");
        }
    });*/
}

MainWindowPleer::~MainWindowPleer()
{
    delete ui;
}

void MainWindowPleer::onOpen() {
    QMessageBox::information(this, tr("Открыть"), tr("Gojo Satoru прибыл..."));
}

void MainWindowPleer::onSave() {
    QMessageBox::information(this, tr("Сохранить"), tr("Gojo Satoru запечатан..."));
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
    QMessageBox::about(this, tr("О программе"), tr("Просто :) плеер на Qt."));
}
