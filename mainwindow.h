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


private slots:
    void close();
    void persoanlCal();
    void othDirectCal();
    void inDirectCal();
    void SubcontractingCal();
    void totalFundCal();
    void clearAllFields();


};

#endif // MAINWINDOW_H
