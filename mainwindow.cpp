#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->exitBtn,SIGNAL(clicked()),this,SLOT(close()));
}


void MainWindow::close(){
    QCoreApplication::quit();
}

MainWindow::~MainWindow()
{
    delete ui;
}
