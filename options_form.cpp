#include "options_form.hpp"
#include "ui_options_form.h"

#include "constants.h"

OptionsForm::OptionsForm(QWidget * parent) :
    QWidget(parent),
    ui(new Ui::OptionsForm)
{
    ui->setupUi(this);
    QObject::connect(ui->spinBoxCPS, SIGNAL(valueChanged(int)), parent, SLOT(onUpdateCPSMax(int)));
    QObject::connect(ui->spinBoxFPS, SIGNAL(valueChanged(int)), parent, SLOT(onUpdateFPSMax(int)));
    QObject::connect(ui->spinBoxFooshesMinimum, SIGNAL(valueChanged(int)), parent, SLOT(onUpdateFooshesMin(int)));
    QObject::connect(ui->spinBoxWorldWidth, SIGNAL(valueChanged(int)), parent, SLOT(onUpdateWorldWidth(int)));
    QObject::connect(ui->spinBoxWorldHeight, SIGNAL(valueChanged(int)), parent, SLOT(onUpdateWorldHeight(int)));
    QObject::connect(ui->spinBoxFoodGap, SIGNAL(valueChanged(int)), parent, SLOT(onUpdateFoodGap(int)));
    QObject::connect(ui->spinBoxFireGap, SIGNAL(valueChanged(int)), parent, SLOT(onUpdateFireGap(int)));
    QObject::connect(ui->doubleSpinBoxFooshMaxSpeed, SIGNAL(valueChanged(double)), parent, SLOT(onUpdateFooshMaxSpeed(double)));

    QObject::connect(ui->doubleSpinBoxFooshAgingSpeed, SIGNAL(valueChanged(double)), parent, SLOT(onUpdateFooshAgingSpeed(double)));
    QObject::connect(ui->doubleSpinBoxFooshMaxAngularSpeed, SIGNAL(valueChanged(double)), parent, SLOT(onUpdateFooshMaxAngularSpeed(double)));
    QObject::connect(ui->doubleSpinBoxFoodGrowingSpeed, SIGNAL(valueChanged(double)), parent, SLOT(onUpdateFoodGrowingSpeed(double)));
    QObject::connect(ui->doubleSpinBoxFooshMaxDigestion, SIGNAL(valueChanged(double)), parent, SLOT(onUpdateFooshMaxDigestion(double)));
}

OptionsForm::~OptionsForm()
{
    delete ui;
}
