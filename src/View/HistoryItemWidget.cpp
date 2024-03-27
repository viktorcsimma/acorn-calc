#include "View/HistoryItemWidget.h"
#include "View/ui_HistoryItemWidget.h"

HistoryItemWidget::HistoryItemWidget(const QString& command, const QString& result, QWidget* parent)
    : QFrame(parent)
    , ui(new Ui::HistoryItemWidget)
{
    ui->setupUi(this);

    ui->commandLabel->setText(command);
    ui->resultLabel->setText(result);
}
