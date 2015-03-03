#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QSettings>
#include "living.hpp"
#include "options_form.hpp"
#include "infos_form.hpp"
#include "ui_options_form.h"
#include "ui_infos_form.h"
#include "foosh.hpp"
#include "food.hpp"

namespace Ui {
    class MainWindow;
}

class View;
class Scene;
class b2World;
class b2Body;
class Food;
class Living;
class Simulation;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void clickAt(int x, int y, Living::Type type);
    void loadSettings();
    void saveSettings();

    void startSimulation();
    void stopSimulation();

    void setSpinboxes();
public slots:
    //  Public slots.
    void onAdvance();
    void onUpdate();
    void onTimer1Seconde();
    void onTimer10Secondes();
    void onTimer10Minutes();
    void onTimerAutosave();

    void onUpdateCPSMax(int i);
    void onUpdateFPSMax(int i);

    void onUpdateWorldWidth(int i);
    void onUpdateWorldHeight(int i);

    void onUpdateFooshesMin(int i);
    void onUpdateFooshMaxSpeed(double d);
    void onUpdateFooshAgingSpeed(double d);
    void onUpdateFooshMaxAngularSpeed(double d){Foosh::setAngularSpeedMax(d);}
    void onUpdateFooshMaxDigestion(double d){Foosh::setDigestionMax(d);}

    void onUpdateFoodGrowingSpeed(double d){Food::setGrowingSpeed(d);}
    void onUpdateFoodGap(int i);

    void onUpdateFireGap(int i);

    void center();

private slots:
    void on_actionFull_Screen_toggled(bool arg1);

    void on_actionSave_triggered();

    void on_actionNew_simulation_triggered();

    void on_actionOpen_simulation_triggered();

    void on_pushButtonPlay_clicked();

    void on_pushButtonPause_clicked();

private:
    Ui::MainWindow * ui;

    OptionsForm * optionsForm;
    InfosForm * infosForm;

    View * view;

    QTimer * timerAdvance;
    QTimer * timerUpdate;
    QTimer * timer1Seconde;
    QTimer * timer10Secondes;
    QTimer * timer10Minutes;
    QTimer * timerAutosave;

    Simulation * simulation;


    QSettings settings;


    bool go;
    int CPS;
    int FPS;

};
