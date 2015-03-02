#include "infos_form.hpp"
#include "ui_infos_form.h"

InfosForm::InfosForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfosForm)
{
    ui->setupUi(this);
}

InfosForm::~InfosForm()
{
    delete ui;
}

