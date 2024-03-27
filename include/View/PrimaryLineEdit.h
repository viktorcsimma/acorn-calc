#ifndef PRIMARYLINEEDIT_H
#define PRIMARYLINEEDIT_H

#include <QLineEdit>

class PrimaryLineEdit : public QLineEdit
{
private:
    // Indicates whether the content of the line edit
    // is a result of a computation
    // or something the user has entered.
    bool containsResult;

public:
    PrimaryLineEdit(QWidget*& parent);

    // This changes the content, if there was a result in it, to "Ans".
    virtual void mousePressEvent(QMouseEvent* e) override;

public slots:
    // Concatenates a given text to the existing text.
    void addToText(const QString&);
    // Sets the line edit to the given test
    // but also sets the "containsResult" flag.
    void setResult(const QString&);
};

#endif // PRIMARYLINEEDIT_H
