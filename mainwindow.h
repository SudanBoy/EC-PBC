#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int indirect_per;
    void set_indirect_perc();
    int get_indirect_perc();
    void set_validators();
    void setGuiStyle();

private slots:
    void persoanlCal();
    void othDirectCal();
    void inDirectCal();
    void SubcontractingCal();
    void totalFundCal();
    void clearAllFields();
    void setToolTip();


};

#endif // MAINWINDOW_H
