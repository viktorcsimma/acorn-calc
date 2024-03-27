#ifndef HISTORYITEMWIDGET_H
#define HISTORYITEMWIDGET_H

#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui {
class HistoryItemWidget;
}
QT_END_NAMESPACE

// A widget which contains a command issued in the past
// and its result.
class HistoryItemWidget: public QFrame {
    Q_OBJECT

public:
    // Sets the two labels with the parameters given.
    HistoryItemWidget(const QString& command, const QString& result, QWidget* parent = nullptr);

private:
    Ui::HistoryItemWidget *ui;
};

#endif // HISTORYITEMWIDGET_H
