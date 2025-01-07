#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QPushButton>

class HoverButton : public QPushButton {
    Q_OBJECT

public:
    explicit HoverButton(int row, QWidget *parent = nullptr)
        : QPushButton(parent), m_row(row) {}

signals:
    void hovered(int row);

protected:
    void enterEvent(QEnterEvent *event) override {
        emit hovered(m_row); // Передаем строку при наведении
        QPushButton::enterEvent(event); // Обрабатываем базовый функционал
    }

private:
    int m_row; // Номер строки, к которой привязана кнопка
};

#endif // HOVERBUTTON_H
