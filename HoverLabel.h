#ifndef HOVERLABEL_H
#define HOVERLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>

class HoverLabel : public QLabel {
    Q_OBJECT

public:
    explicit HoverLabel(int row, QWidget *parent = nullptr)
        : QLabel(parent), m_row(row), currentIcon(":/Icon/play.png") {
        QPixmap play_icon(currentIcon);
        QPainter painter(&play_icon);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);// Устанавливаем режим наложения SourceIn
        painter.fillRect(play_icon.rect(), QColor("#8a9197")); // Заполняем весь pixmap цветом, указанным в iconColor
        painter.end();
        setPixmap(play_icon.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

signals:
    void hovered(int row);
    void clicked(int row);

protected:
    void enterEvent(QEnterEvent *event) override {
        emit hovered(m_row); // Передаем строку при наведении
        QLabel::enterEvent(event); // Обрабатываем базовый функционал
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            emit clicked(m_row); // Эмитируем сигнал клика
            toggleIcon(); // Меняем иконку при клике
        }
        QLabel::mousePressEvent(event); // Обрабатываем базовый функционал
    }

private:
    int m_row;                  // Номер строки, к которой привязан QLabel
    QString currentIcon;        // Текущая иконка

    void toggleIcon() {
        // Меняем иконку при клике
        if (currentIcon == ":/Icon/play.png") {
            currentIcon = ":/Icon/pause.png";
        } else {
            currentIcon = ":/Icon/play.png";
        }
        QPixmap play_icon(currentIcon);
        QPainter painter(&play_icon);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);// Устанавливаем режим наложения SourceIn
        painter.fillRect(play_icon.rect(), QColor("#8a9197")); // Заполняем весь pixmap цветом, указанным в iconColor
        painter.end();
        setPixmap(play_icon.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
};

#endif // HOVERLABEL_H
