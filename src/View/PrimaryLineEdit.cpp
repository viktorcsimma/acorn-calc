#include "View/PrimaryLineEdit.h"

PrimaryLineEdit::PrimaryLineEdit(QWidget*& parent):
    QLineEdit(parent), containsResult(false) {}

void PrimaryLineEdit::mousePressEvent(QMouseEvent* e) {
    if (containsResult) {
        // then we change the text to Ans
        // so that the user can calculate with the real result
        // instead of the approximation
        this->setText("Ans ");
        containsResult = false;
    }

    QLineEdit::mousePressEvent(e);
}

void PrimaryLineEdit::addToText(const QString& str) {
    this->setFocus();

    if (0 < str.length()) {
        // a space will not toggle the flag
        if (containsResult && str != " ") {
            containsResult = false;
            if (str.endsWith('(')) {
                this->setText(str + "Ans");
            } else if (str.at(0).isLetterOrNumber()) {
                this->setText(str);
            } else {
                this->setText("Ans" + str);
            }
        } else {
            this->setText(this->text() + str);
        }
    }
}

void PrimaryLineEdit::setResult(const QString& str) {
    this->setText(str);
    containsResult = true;
}
