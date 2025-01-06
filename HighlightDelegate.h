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
        m_hoveredRow = -1;
    }

    void setHoveredRow(int row) {
        m_hoveredRow = row;
        m_table->viewport()->update(); // Обновляем отображение таблицы
    }

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QStyleOptionViewItem opt = option;

        if (index.row() == m_hoveredRow) {
            opt.backgroundBrush = QBrush(QColor("#12cea4")); // Подсветка строки
            painter->fillRect(opt.rect, opt.backgroundBrush); // Фон строки
            opt.palette.setColor(QPalette::Text, Qt::white);  // Цвет текста
        }

        QStyledItemDelegate::paint(painter, opt, index);
    }

private:
    QTableWidget *m_table;
    int m_hoveredRow;
};

#endif // HIGHLIGHTDELEGATE_H
