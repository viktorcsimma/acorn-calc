#include "View/PreciseOutputWindow.h"
#include "View/ui_PreciseOutputWindow.h"
#include "PreciseOutputWindow.moc"

PreciseOutputWindow::PreciseOutputWindow(PreciseOutputViewModel& viewModel, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::PreciseOutputWindow)  // don't forget! this caused me a lot of segfaults and headaches
    , viewModel(viewModel)
{
    ui->setupUi(this);

    // it gets the initial result automatically when the main view model spawns it
    ui->textEdit->setText(QString::fromStdString(viewModel.getResult()));

    ui->spinBox->setValue(viewModel.getPrecision());

    connect(ui->evaluateButton, &QPushButton::clicked, this, &PreciseOutputWindow::evaluateButtonClicked);
    // we do this in order to ensure that onEvaluationFinished runs in the main thread
    connect(this, &PreciseOutputWindow::evaluationFinished, this, &PreciseOutputWindow::onEvaluationFinished);
}

PreciseOutputWindow::~PreciseOutputWindow() {
    viewModel.interruptEvaluation();
}

void PreciseOutputWindow::evaluateButtonClicked()
{
    if ("Evaluate" == ui->evaluateButton->text()) startEvaluation();
    else interruptEvaluation();
}

void PreciseOutputWindow::enterKeyPressed()
{
    if ("Evaluate" == ui->evaluateButton->text()) startEvaluation();
    // else do nothing
}

void PreciseOutputWindow::onEvaluationFinished()
{
    // TODO: set the progress circle
    ui->textEdit->setText(QString::fromStdString(viewModel.getResult()));
    ui->evaluateButton->setText("Evaluate");
    ui->evaluateButton->setEnabled(true);
}

void PreciseOutputWindow::startEvaluation()
{
    viewModel.setPrecisionAsync(ui->spinBox->value(), [this]() {emit evaluationFinished();});
    ui->evaluateButton->setText("Cancel");
    // TODO: set the progress circle
}

void PreciseOutputWindow::interruptEvaluation()
{
    ui->evaluateButton->setEnabled(false);
    viewModel.interruptEvaluation();
}

