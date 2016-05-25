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
    double indirect_perc;
    void set_indirect_perc();
    void set_validators();
    void setGuiStyle();

private slots:
    void persoanlCal();
    void othDirectCal();
    void indirectCal();
    void SubcontractingCal();
    void totalFundCal();
    void clearAllFields();
    void setToolTip();
    void totalCategory();


};

#endif // MAINWINDOW_H
