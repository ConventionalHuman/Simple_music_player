#ifndef HOVERLABEL_H
#define HOVERLABEL_H

#include <QLabel>

class HoverLabel : public QLabel {
    Q_OBJECT

public:
    explicit HoverLabel(int row, QWidget *parent = nullptr)
        : QLabel(parent), m_row(row) {}

signals:
    void hovered(int row); // Сигнал для обработки наведения

protected:
    void enterEvent(QEnterEvent *event) override {
        emit hovered(m_row); // Передаем номер строки
        QLabel::enterEvent(event); // Обрабатываем базовое поведение
    }

private:
    int m_row; // Номер строки, к которой привязан QLabel
};

#endif // HOVERLABEL_H
