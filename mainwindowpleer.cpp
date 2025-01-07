#include "mainwindowpleer.h"
#include "./ui_mainwindowpleer.h"
#include "HighlightDelegate.h"
#include "HoverButton.h"
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
#include <QTime>
#include <QDebug>

MainWindowPleer::MainWindowPleer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowPleer)
{
    ui->setupUi(this);
    //mainWindow
    setWindowIcon(QIcon(":/Icon/Logo4.png"));
    setWindowTitle("UtochkaKria");
    // Установить фиксированный размер окна
    setFixedSize(1100, 550);
    // Установить стандартное окно и отключить возможность изменения состояния
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    setStyleSheet("background: #0f1725;");

    QMenu *fileMenu = menuBar()->addMenu(tr("Файл")); // Локализуемый текст
    fileMenu->addAction(tr("Открыть"), this, SLOT(onOpen()));
    fileMenu->addAction(tr("Выход"), this, SLOT(onExit()));
    QMenu *helpMenu = menuBar()->addMenu(tr("Помощь"));
    helpMenu->addAction(tr("О программе"), this, SLOT(onAbout()));

    //labelTitle
    ui->labelTitle->setStyleSheet(
        "QLabel {"                             // Исправлено название класса
        "    background: transparent;"         // Прозрачный фон
        "    font-size: 24px;"
        "    border: none;"
        "    color: #12cea4;"
        "    font-weight: bold;"
        "}"
        );

    //labelArtist
    ui->labelArtist->setStyleSheet(
        "QLabel {"                             // Исправлено название класса
        "    background: transparent;"         // Прозрачный фон
        "    font-size: 16px;"
        "    border: none;"
        "    color: #ffffff;"
        "    font-weight: bold;"
        "}"
        );

    //labelBegin
    ui->LabelBegin->setStyleSheet(
        "QLabel {"                             // Исправлено название класса
        "    background: transparent;"         // Прозрачный фон
        "    color: #8a9197;"
        "}"
        );

    //labelEnd
    ui->labelEnd->setStyleSheet(
        "QLabel {"                             // Исправлено название класса
        "    background: transparent;"         // Прозрачный фон
        "    color: #8a9197;"
        "}"
        );

    //pushButtonPlay
    ui->pushButtonPlay->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"    // Прозрачный фон
        "    border: none;"               // Без рамки
        "}");
    ui->pushButtonPlay->setFixedSize(34,34);
    ui->pushButtonPlay->setIconSize(QSize(34,34));
    updateIconColor(":/Icon/play.png",ui->pushButtonPlay, "#12cea4");

    //pushButtonNext
    ui->pushButtonNext->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"    // Прозрачный фон
        "    border: none;"               // Без рамки
        "}");
    ui->pushButtonNext->setFixedSize(34,34);
    ui->pushButtonNext->setIconSize(QSize(34,34));
    updateIconColor(":/Icon/next.png",ui->pushButtonNext, "#8a9197");

    //pushButtonPrev
    ui->pushButtonPrev->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"    // Прозрачный фон
        "    border: none;"               // Без рамки
        "}");
    ui->pushButtonPrev->setFixedSize(34,34);
    ui->pushButtonPrev->setIconSize(QSize(34,34));
    updateIconColor(":/Icon/previous.png",ui->pushButtonPrev, "#8a9197");

    //pushButtonCircle
    ui->pushButtonCircle->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"    // Прозрачный фон
        "    border: none;"               // Без рамки
        "}");
    ui->pushButtonCircle->setFixedSize(34,34);
    ui->pushButtonCircle->setIconSize(QSize(34,34));
    updateIconColor(":/Icon/return.png",ui->pushButtonCircle, "#8a9197");

    //pushButtonRandom
    ui->pushButtonRandom->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"    // Прозрачный фон
        "    border: none;"               // Без рамки
        "}");
    ui->pushButtonRandom->setFixedSize(34,34);
    ui->pushButtonRandom->setIconSize(QSize(34,34));
    updateIconColor(":/Icon/random.png",ui->pushButtonRandom, "#8a9197");

    //horizontalSlider
    ui->horizontalSlider->setStyleSheet(
        "QSlider {"
        "    background: #8a9197;"  // Цвет остальной части полосы (не заполненной)
        "    border: none;"
        "    height: 6px;"  // Размер полосы
        "    border-radius: 2px;"  // Скругление краев полосы
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: #12cea4;"  // Заполненная часть слайдера
        "    border: none;"
        "    height: 6px;"  // Размер заполненной части
        "    border-radius: 2px;"  // Скругление для заполненной области
        "}"
        "QSlider::handle:horizontal {"
        "    background: #12cea4;"
        " height: 6px;"  // Высота бегунка
        "    border-radius: 2px;"
        "}"
        );

    // Создаем QLabel для фона
    QLabel *backgroundLabel = new QLabel(ui->framePleer); // Для фона
    QPixmap pixmap(":/Images/jinx.jpg");
    backgroundLabel->setPixmap(pixmap);
    backgroundLabel->setAlignment(Qt::AlignCenter);
    // Устанавливаем QLabel как фоновый элемент, растягиваем по всему фрейму
    backgroundLabel->setGeometry(0, 0, ui->framePleer->width(), ui->framePleer->height());
    // Применяем полупрозрачность через QGraphicsOpacityEffect только к изображению
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.1);  // Задаем уровень прозрачности
    backgroundLabel->setGraphicsEffect(effect);
    // Устанавливаем атрибут для игнорирования кликов
    backgroundLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    // Поднимаем QLabel на задний план, чтобы фон был "позади"
    backgroundLabel->raise();

    // Фиксация размера framePleer
    ui->framePleer->setFixedSize(550, 476);
    // Устанавливаем стиль фрейма для остальных элементов
    ui->framePleer->setStyleSheet(
        "QFrame {"
        "    border: none;" // Убираем рамки фрейма
        "}"
        );
    // Включаем возможность работы с другими виджетами
    ui->framePleer->setAutoFillBackground(true);

    //pushButtonSearch
    ui->pushButtonSearch->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"    // Прозрачный фон
        "    border: none;"               // Без рамки
        "}"
        );
    //фиксация размера кнопки поиска
    ui->pushButtonSearch->setFixedSize(34,34);
    ui->pushButtonSearch->setIconSize(QSize(34,34));
    updateIconColor(":/Icon/icon_search.png",ui->pushButtonSearch, "#8a9197");

    // LineEditSearch
    ui->lineEditSearch->setStyleSheet(
        "QLineEdit {"
        "    background: transparent;"
        "    border: none;"
        "    border-bottom: 1px solid #484c55;"
        "    color: #484c55;"
        "    font-size: 16px;"  // Задайте нужный размер шрифта
        "    padding: 2px;"
        "}"
        "QLineEdit:focus {"
        "    border-bottom: 2px solid #8a9197;"
        "    color: #8a9197;"
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
    ui->tableWidgetSongs->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Отключение заголовков таблицы
    ui->tableWidgetSongs->horizontalHeader()->setSectionsClickable(false);
    // Установка ширины колонок
    ui->tableWidgetSongs->setColumnWidth(0,50);
    ui->tableWidgetSongs->setColumnWidth(1,190);
    ui->tableWidgetSongs->setColumnWidth(2,190);
    ui->tableWidgetSongs->setColumnWidth(3,50);
    ui->tableWidgetSongs->setFocusPolicy(Qt::NoFocus);
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
        "QHeaderView::section {"
        "    background: transparent;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    color: #12cea4;"
        "    border: none;" // Убираем вертикальные линии заголовков
        "} "

        /* Стиль для вертикального скроллбара */
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: #f1f1f1;"
        "    width: 12px;"
        "    margin: 0px 3px 0 3px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #12cea4;"  // Цвет ползунка
        "    min-height: 20px;"
        "    border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: #16d8b1;"  // Цвет ползунка при наведении
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    background: none;"
        "    border: none;"
        "    height: 0px;"
        "    width: 0px;"
        "}"
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
        "    background: none;"
        "    border: none;"
        "    height: 0px;"
        "    width: 0px;"
        "}"
        );
    addTrackInTable();
    disableColomTable();
}

MainWindowPleer::~MainWindowPleer()
{
    delete ui;
}

void MainWindowPleer::disableColomTable()
{
    int rowCount = ui->tableWidgetSongs->rowCount();
    int columnCount = ui->tableWidgetSongs->columnCount();

    // Отключение взаимодействия для всех ячеек, кроме первой колонки
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 1; col < columnCount; ++col) {
            QTableWidgetItem* item = ui->tableWidgetSongs->item(row, col);
            if (!item) {
                item = new QTableWidgetItem();
                ui->tableWidgetSongs->setItem(row, col, item);
            }
            item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsEnabled);
            item->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void MainWindowPleer::addTrackInTable()
{
    HighlightDelegate *highlightDelegate = new HighlightDelegate(ui->tableWidgetSongs, this);
    ui->tableWidgetSongs->setItemDelegate(highlightDelegate);
    for (int i = 0; i < 40; ++i) {
        ui->tableWidgetSongs->insertRow(i);

        HoverButton *playButton = new HoverButton(i, this); // Привязываем строку
        playButton->setIcon(QIcon(":/Icon/play.png"));
        playButton->setFocusPolicy(Qt::NoFocus);

        playButton->setStyleSheet(
            "QPushButton {"
            "    background: transparent;"
            "    border: none;"
            "} "
            );
        // Применяем начальный цвет для иконки play
        updateIconColor(":/Icon/play.png", playButton,"#8a9197");

        connect(playButton, &HoverButton::hovered, this, [=](int row) {
            highlightDelegate->setHoveredRow(row); // Передаем строку в делегат
        });

        bool isPlayState = true;

        connect(playButton, &QPushButton::clicked, [this, playButton, &isPlayState]() {
            QString iconPath = isPlayState ? ":/Icon/pause.png" : ":/Icon/play.png";
            updateIconColor(iconPath, playButton, "#8a9197"); // Функция будет доступна
            isPlayState = !isPlayState;  // Переключаем состояние
        });

        ui->tableWidgetSongs->setCellWidget(i, 0, playButton);
        ui->tableWidgetSongs->setItem(i, 1, new QTableWidgetItem("Название трека " + QString::number(i + 1)));
        ui->tableWidgetSongs->setItem(i, 2, new QTableWidgetItem("Исполнитель " + QString::number(i + 1)));
        QTime time(0, 0);
        time = time.addSecs(i * 200);
        ui->tableWidgetSongs->setItem(i, 3, new QTableWidgetItem(time.toString("mm:ss")));
    }
    ui->tableWidgetSongs->setMouseTracking(true); // Обязательно для получения событий cellEntered
    // Подключение события наведения мыши
    connect(ui->tableWidgetSongs, &QTableWidget::cellEntered, this, [=](int row, int column) {
        Q_UNUSED(column); // Обрабатываем только строку
        highlightDelegate->setHoveredRow(row);
    });

}

void MainWindowPleer::updateIconColor(const QString &iconPath, QPushButton *button, const QString &iconColor)
{
    QPixmap pixmap(iconPath);
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), QColor(iconColor)); // Изменение цвета
    painter.end();
    button->setIcon(QIcon(pixmap));
}

void MainWindowPleer::onOpen() {
    QMessageBox::information(this, tr("Открыть"), tr("Gojo Satoru прибыл..."));
}

void MainWindowPleer::onExit() {
    close(); // Закрыть приложение
}

void MainWindowPleer::onAbout() {
    QMessageBox::about(this, tr("О программе"), tr("Просто :) плеер на Qt."));
}
