#ifndef HIGHLIGHTDELEGATE_H
#define HIGHLIGHTDELEGATE_H

#include <QStyledItemDelegate>
#include <QTableWidget>
#include <QPainter>

class HighlightDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit HighlightDelegate(QTableWidget *table, QObject *parent = nullptr)
        : QStyledItemDelegate(parent), m_table(table) {
        m_hoveredRow = -1;// Инициализация строки подсветки (изначально нет подсветки)
    }
    // Устанавливает номер строки, на которую наведена мышь
    void setHoveredRow(int row) {
        m_hoveredRow = row;// Обновляем номер строки
        m_table->viewport()->update(); // Обновляем отображение таблицы
    }

protected:
    // Метод для пользовательской отрисовки ячейки
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QStyleOptionViewItem opt = option;// Копируем текущие опции отображения

        // Проверяем, является ли строка текущей наведённой строкой
        if (index.row() == m_hoveredRow) {
            opt.backgroundBrush = QBrush(QColor("#12cea4")); // Подсветка строки
            painter->fillRect(opt.rect, opt.backgroundBrush); // Фон строки
            opt.palette.setColor(QPalette::Text, Qt::white);  // Цвет текста
        }

        // Вызываем базовый метод для стандартной отрисовки ячейки
        QStyledItemDelegate::paint(painter, opt, index);
    }

private:
    QTableWidget *m_table;// Указатель на таблицу, с которой работает делегат
    int m_hoveredRow;// Номер строки, на которую наведена мышь
};

#endif // HIGHLIGHTDELEGATE_H
