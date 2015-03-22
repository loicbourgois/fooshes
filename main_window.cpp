#include "main_window.hpp"
#include "ui_main_window.h"

#include <QColor>
#include <QThread>
#include "food.hpp"
#include "fire.hpp"
#include "foosh.hpp"
#include <QDebug>
#include <QBitArray>
#include <QGraphicsItem>
#include <QFileDialog>
#include <Box2D/Box2D.h>
#include "my_query_callback.hpp"
#include "scene.hpp"
#include "view.hpp"
#include "constants.hpp"
#include "simulation.hpp"
#include "ui_options_form.h"
#include "ui_infos_form.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    optionsForm(new OptionsForm(this)),
    infosForm(new InfosForm(this)),
    controlForm(new ControlForm(this)),
    view(new View(this)),
    timerAdvance(new QTimer(this)),
    timerUpdate(new QTimer(this)),
    timer1Seconde(new QTimer(this)),
    timer10Secondes(new QTimer(this)),
    timer10Minutes(new QTimer(this)),
    timerAutosave(new QTimer(this)),
    simulation(),
    settings("Loïc Bourgois", "Fooshes"),
    go(true),
    CPS(0),
    FPS(0)

{
    //  Inits.
    ui->setupUi(this);
    view->scale(0.25,0.25);
    ui->widgetView->layout()->addWidget(view);
    ui->scrollAreaInfos->setWidget(infosForm);
    ui->scrollAreaInfos->setMinimumWidth(infosForm->sizeHint().width());
    ui->scrollAreaOptions->setWidget(optionsForm);
    ui->scrollAreaOptions->setMinimumWidth(optionsForm->sizeHint().width());
    ui->scrollAreaControls->setWidget(controlForm);
    //
    QObject::connect(timerAdvance, SIGNAL(timeout()), this, SLOT(onAdvance()));
    QObject::connect(timerUpdate, SIGNAL(timeout()), this, SLOT(onUpdate()));
    QObject::connect(timer1Seconde, SIGNAL(timeout()), this, SLOT(onTimer1Seconde()));
    QObject::connect(timer10Secondes, SIGNAL(timeout()), this, SLOT(onTimer10Secondes()));
    QObject::connect(timer10Minutes, SIGNAL(timeout()), this, SLOT(onTimer10Minutes()));
    QObject::connect(timerAutosave, SIGNAL(timeout()), this, SLOT(onTimerAutosave()));
    //
    loadSettings();
    //
    on_actionNew_simulation_triggered();
    timer1Seconde->start(1000);
    timer10Secondes->start(1000*10);
    timer10Minutes->start(1000*60*10);
    timerAutosave->start(1000*60*10);
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::clickAt(int x, int y, Living::Type type)
{
    simulation->addLiving(x, y, 0, type);
}

void MainWindow::saveSettings()
{
    settings.setValue("main_window/fullScreen", isFullScreen());
    settings.setValue("main_window/maximized", isMaximized());
    if(!isMaximized() && !isFullScreen())
        settings.setValue("main_window/geometry", saveGeometry());
}

void MainWindow::loadSettings()
{
    restoreGeometry(settings.value("main_window/geometry").toByteArray());
    if(settings.value("main_window/fullScreen").value<bool>())
        this->showFullScreen();
    if(settings.value("main_window/maximized").value<bool>())
        showMaximized();
}



void MainWindow::startSimulation()
{
    timerAdvance->start(1000/simulation->getCpsmax());
    timerUpdate->start(1000/simulation->getFpsmax());
}

void MainWindow::pauseSimulation()
{
    timerAdvance->stop();
}

void MainWindow::stopSimulation()
{
    timerAdvance->stop();
    timerUpdate->stop();
}

void MainWindow::onAdvance()
{
    simulation->advance();
    CPS++;
}

void MainWindow::onUpdate()
{
    simulation->update();
    infosForm->ui->labelFoodCount->setText("Foods : " +QString::number(Food::getCount()));
    infosForm->ui->labelFoodsEaten->setText("Eaten : " +QString::number(Food::getEatenCount()));
    infosForm->ui->labelFooshesCount->setText("Fooshes : " +QString::number(Foosh::getCount()));
    infosForm->ui->labelFooshesDeaths->setText("Dead : " +QString::number(Foosh::getDeaths()));
    infosForm->ui->labelSteps->setText("Steps : " + QString::number(simulation->getSteps()));
    infosForm->ui->labelTimeElapsed->setText("Time : " + QString::number(simulation->getTimeElapsed()));
    //view->centerOn(0,0);
    FPS++;
}

void MainWindow::onTimer1Seconde()
{
    infosForm->ui->labelCps->setText("CPS : " + QString::number(CPS));
    infosForm->ui->labelFps->setText("FPS : " + QString::number(FPS));
    CPS = 0;
    FPS = 0;
}

void MainWindow::onTimer10Secondes()
{
    //simulation->deleteOutsiders();
    //saveSettings();
}

void MainWindow::onTimer10Minutes()
{
}

void MainWindow::onTimerAutosave()
{
    //
    int i = 0;
    QDir dir("./simulations/autosaves/");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Time);
    QFileInfoList list = dir.entryInfoList();
    if(list.size())
    {
        QString str = list[0].fileName();
        QRegExp rx("(\\d+)");
        std::vector<int> result;
        int pos = 0;
        while ((pos = rx.indexIn(str, pos)) != -1)
        {
            QString theNumber = rx.cap(1);
            result.push_back(theNumber.toInt());
            pos += rx.matchedLength();
        }
        if(result.size() != 1)
        {
            qDebug() << "void MainWindow::onTimerAutosave() : problem";
        }
        else
        {
            i = result[0]+1;
        }
    }
    //
    QString path = "./simulations/autosaves/simulation_" + QString::number(i) + ".foosh";
    simulation->save(path);
}

void MainWindow::onUpdateCPSMax(int i)
{
    simulation->setCpsmax(i);
    timerAdvance->setInterval(1000/simulation->getCpsmax());
}

void MainWindow::onUpdateFPSMax(int i)
{
    simulation->setFpsmax(i);
    timerUpdate->setInterval(1000/simulation->getFpsmax());
}

void MainWindow::onUpdateFooshesMin(int i)
{
    simulation->setFooshesMin(i);
}

void MainWindow::onUpdateWorldWidth(int i)
{
    simulation->setWidth(i);
    simulation->deleteOutsiders();
}

void MainWindow::onUpdateWorldHeight(int i)
{
    simulation->setHeight(i);
    simulation->deleteOutsiders();
}

void MainWindow::onUpdateFoodGap(int i)
{
    simulation->setFoodGap(i);
    simulation->deleteOutsiders();
}

void MainWindow::onUpdateFireGap(int i)
{
    simulation->setFireGap(i);
    simulation->deleteOutsiders();
}

void MainWindow::onUpdateFooshMaxSpeed(double d)
{
    Foosh::setSpeedMax(d);
}

void MainWindow::onUpdateFooshAgingSpeed(double d)
{
    Foosh::setAgingSpeed(d);
}


void MainWindow::onCenter()
{
    view->centerOn(0,0);
}

void MainWindow::onZoomIn()
{
    view->scale(2,2);
}

void MainWindow::onZoomOut()
{
    view->scale(0.5,0.5);
}

void MainWindow::on_actionFull_Screen_toggled(bool arg1)
{
    if(arg1)
        showFullScreen();
    else
        showMaximized();
}

void MainWindow::on_actionSave_triggered()
{
    stopSimulation();
    QDir dir("./simulations/");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QString path = QFileDialog::getSaveFileName(this, "Save Simulation", "./simulations/simulation", "Foosh (*.foosh)");
    if(path.size())
    {
        simulation->save(path);
    }
    startSimulation();
}

void MainWindow::on_actionNew_simulation_triggered()
{
    stopSimulation();
    if(simulation)
        delete simulation;
    simulation = new Simulation(this, view);
    setSpinboxes();
    startSimulation();
}

void MainWindow::on_actionOpen_simulation_triggered()
{
    stopSimulation();
    QDir dir("./simulations/");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QString path = QFileDialog::getOpenFileName(this, "Open Simulation", "./simulations", "Foosh (*.foosh)");
    if(path.size())
    {
        if(simulation)
            delete simulation;
        simulation = new Simulation(this, view, path);
        setSpinboxes();
    }
    startSimulation();
}

void MainWindow::setSpinboxes()
{
    optionsForm->ui->spinBoxWorldWidth->setValue(simulation->getWidth());
    optionsForm->ui->spinBoxWorldHeight->setValue(simulation->getHeight());
    optionsForm->ui->spinBoxFireGap->setValue(simulation->getFireGap());
    optionsForm->ui->spinBoxFoodGap->setValue(simulation->getFoodGap());
    optionsForm->ui->spinBoxCPS->setValue(simulation->getCpsmax());
    optionsForm->ui->spinBoxFPS->setValue(simulation->getFpsmax());
    optionsForm->ui->spinBoxFooshesMinimum->setValue(simulation->getFooshesmin());
    optionsForm->ui->doubleSpinBoxFooshMaxSpeed->setValue(Foosh::getSpeedMax());
    optionsForm->ui->doubleSpinBoxFooshMaxAngularSpeed->setValue(Foosh::getAngularSpeedMax());
    optionsForm->ui->doubleSpinBoxFooshAgingSpeed->setValue(Foosh::getAgingSpeed());
    optionsForm->ui->doubleSpinBoxFoodGrowingSpeed->setValue(Food::getGrowingSpeed());
    optionsForm->ui->doubleSpinBoxFooshMaxDigestion->setValue(Foosh::getDigestionMax());
}

void MainWindow::on_pushButtonPlay_clicked()
{
    startSimulation();
}

void MainWindow::on_pushButtonPause_clicked()
{
    pauseSimulation();
}
