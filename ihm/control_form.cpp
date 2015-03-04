#include "control_form.hpp"
#include "ui_control_form.h"

ControlForm::ControlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlForm)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButtonZoomIn, SIGNAL(clicked()), parent , SLOT(onZoomIn()));
    QObject::connect(ui->pushButtonZoomOut, SIGNAL(clicked()), parent , SLOT(onZoomOut()));
    QObject::connect(ui->pushButtonCenter, SIGNAL(clicked()), parent , SLOT(onCenter()));
}


ControlForm::~ControlForm()
{
    delete ui;
}
