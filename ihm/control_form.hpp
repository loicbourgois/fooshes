#ifndef CONTROL_FORM_HPP
#define CONTROL_FORM_HPP

#include <QWidget>

class MainWindow;

namespace Ui {
class ControlForm;
}

class ControlForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlForm(QWidget *parent);
    ~ControlForm();

private:
    Ui::ControlForm *ui;
};

#endif // CONTROL_FORM_HPP
