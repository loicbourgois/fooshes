#include "new_simulation_dialog.hpp"
#include "ui_new_simulation_dialog.h"

#include "main_window.hpp"

NewSimulationDialog::NewSimulationDialog(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::NewSimulationDialog)
{
    ui->setupUi(this);
}

NewSimulationDialog::~NewSimulationDialog()
{
    delete ui;
}

void NewSimulationDialog::on_pushButtonOK_clicked()
{
    static_cast<MainWindow*>(this->parent())->
}
