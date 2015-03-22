#ifndef NEW_SIMULATION_DIALOG_HPP
#define NEW_SIMULATION_DIALOG_HPP

#include <QDialog>

namespace Ui {
class NewSimulationDialog;
}

class NewSimulationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewSimulationDialog(QWidget *parent = 0);
    ~NewSimulationDialog();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::NewSimulationDialog *ui;
};

#endif // NEW_SIMULATION_DIALOG_HPP
