#pragma once

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
