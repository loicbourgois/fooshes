#pragma once

#include <QWidget>

namespace Ui {
class InfosForm;
}

class InfosForm : public QWidget
{
    Q_OBJECT

public:
    explicit InfosForm(QWidget *parent = 0);
    ~InfosForm();
    Ui::InfosForm * ui;
};
