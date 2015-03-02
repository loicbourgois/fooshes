#ifndef OPTIONS_FORM_HPP
#define OPTIONS_FORM_HPP

#include <QWidget>

namespace Ui {
class OptionsForm;
}

class OptionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsForm(QWidget *parent = 0);
    ~OptionsForm();
    Ui::OptionsForm * ui;

};

#endif // OPTIONS_FORM_HPP
