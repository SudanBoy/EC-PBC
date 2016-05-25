#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QWhatsThis>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("European Commission - Fund Calculator");

    setGuiStyle();
    setToolTip();
    set_validators();

    set_indirect_perc();
    get_indirect_perc();

    connect(ui->clearAllBtn,SIGNAL(clicked()),this,SLOT(clearAllFields()));

    connect(ui->rtd_pm,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));
    connect(ui->dem_pm,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));
    connect(ui->mgt_pm,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));
    connect(ui->pm_cost,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));

    connect(ui->persoanl_oth,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));

    connect(ui->sub_con_dem,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));
    connect(ui->sub_con_rtd,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));
    connect(ui->sub_con_mgt,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));
    connect(ui->sub_con_oth,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));

    connect(ui->tot_travel_cost,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));
    connect(ui->tot_equip_cost,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));

    connect(ui->oth_direct_dem,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));
    connect(ui->oth_direct_oth,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));

    connect(ui->oth_direct_rtd,SIGNAL(textChanged(QString)),this,SLOT(inDirectCal()));
    connect(ui->oth_direct_dem,SIGNAL(textEdited(QString)),this,SLOT(inDirectCal()));
    connect(ui->oth_direct_mgt,SIGNAL(textChanged(QString)),this,SLOT(inDirectCal()));
    connect(ui->indirect_oth,SIGNAL(textEdited(QString)),this,SLOT(inDirectCal()));

    connect(ui->tot_persoanl,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
    connect(ui->tot_sub_con,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
    connect(ui->tot_oth_direct,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
    connect(ui->tot_indirect,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
}

void MainWindow::persoanlCal(){
    int pm_cost = ui->pm_cost->text().toInt();

    int dem_pm = ui->dem_pm->text().toInt();
    int personal_dem = pm_cost*dem_pm;

    int rtd_pm = ui->rtd_pm->text().toInt();
    int personal_rtd = pm_cost*rtd_pm;

    int mgt_pm = ui->mgt_pm->text().toInt();
    int personal_mgt = pm_cost*mgt_pm;

    int personal_oth = ui->persoanl_oth->text().toInt();

    int tot_pm = rtd_pm + dem_pm + mgt_pm;
    int tot_persoanl = personal_rtd + personal_dem + personal_mgt + personal_oth;

    ui->persoanl_rtd->setText(QString::number(personal_rtd));
    ui->persoanl_dem->setText(QString::number(personal_dem));
    ui->personal_mgt->setText(QString::number(personal_mgt));
    ui->tot_persoanl->setText(QString::number(tot_persoanl));

    ui->tot_pm->setText(QString::number(tot_pm));
}

void MainWindow::SubcontractingCal(){

    int sub_con_dem = ui->sub_con_dem->text().toInt();
    int sub_con_rtd = ui->sub_con_rtd->text().toInt();
    int sub_con_mgt = ui->sub_con_mgt->text().toInt();
    int sub_con_oth = ui->sub_con_oth->text().toInt();

    int tot_sub_con = sub_con_dem + sub_con_rtd + sub_con_mgt + sub_con_oth;

    ui->tot_sub_con->setText(QString::number(tot_sub_con));
}

void MainWindow::othDirectCal(){
    int tot_travel_cost = ui->tot_travel_cost->text().toInt();
    int tot_equip_cost = ui->tot_equip_cost->text().toInt();

    int oth_direct_dem = ui->oth_direct_dem->text().toInt();
    int oth_direct_mgt = tot_travel_cost;
    int oth_direct_oth = ui->oth_direct_oth->text().toInt();
    int oth_direct_rtd = ui->oth_direct_rtd->text().toInt();

    oth_direct_rtd = tot_travel_cost + tot_equip_cost;

    ui->oth_direct_rtd->setText(QString::number(oth_direct_rtd));
    ui->oth_direct_mgt->setText(QString::number(oth_direct_mgt));

    int tot_oth_direct = oth_direct_rtd + oth_direct_dem + oth_direct_mgt + oth_direct_oth;

    ui->tot_oth_direct->setText(QString::number(tot_oth_direct));
}

void MainWindow::inDirectCal(){

    int pm_cost = ui->pm_cost->text().toInt();

    int dem_pm = ui->dem_pm->text().toInt();
    int personal_dem = pm_cost*dem_pm;
    int oth_direct_dem = ui->oth_direct_dem->text().toInt();
    int indirect_dem = (oth_direct_dem + personal_dem) * 0.25;
    ui->indirect_dem->setText(QString::number(indirect_dem));

    int rtd_pm = ui->rtd_pm->text().toInt();
    int personal_rtd = pm_cost*rtd_pm;
    int oth_direct_rtd = ui->oth_direct_rtd->text().toInt();
    int indirect_rtd = (oth_direct_rtd + personal_rtd) * 0.25;
    ui->indirect_rtd->setText(QString::number(indirect_rtd));

    int mgt_pm = ui->mgt_pm->text().toInt();
    int personal_mgt = pm_cost*mgt_pm;
    int oth_direct_mgt = ui->oth_direct_mgt->text().toInt();
    int indirect_mgt = (oth_direct_mgt + personal_mgt) * 0.25;
    ui->indirect_mgt->setText(QString::number(indirect_mgt));

    int indirect_oth = ui->indirect_oth->text().toInt();

    int tot_indirect = indirect_dem + indirect_rtd + indirect_mgt + indirect_oth;

    ui->tot_indirect->setText(QString::number(tot_indirect));
}

void MainWindow::totalFundCal(){
    int tot_personal = ui->tot_persoanl->text().toInt();
    int tot_sub_con = ui->tot_sub_con->text().toInt();
    int tot_oth_direct = ui->tot_oth_direct->text().toInt();
    int tot_indirect = ui->tot_indirect->text().toInt();

    int tot_fund = tot_personal + tot_sub_con + tot_oth_direct + tot_indirect;

    ui->fund_lcd->display(tot_fund);
}

void MainWindow::clearAllFields(){
    ui->rtd_pm->clear();
    ui->dem_pm->clear();
    ui->mgt_pm->clear();
    ui->tot_pm->clear();
    ui->pm_cost->clear();

    ui->persoanl_rtd->clear();
    ui->persoanl_dem->clear();
    ui->personal_mgt->clear();
    ui->persoanl_oth->clear();
    ui->tot_persoanl->clear();

    ui->sub_con_rtd->clear();
    ui->sub_con_dem->clear();
    ui->sub_con_mgt->clear();
    ui->sub_con_oth->clear();
    ui->tot_sub_con->clear();

    ui->tot_travel_cost->clear();
    ui->tot_equip_cost->clear();

    ui->oth_direct_rtd->clear();
    ui->oth_direct_dem->clear();
    ui->oth_direct_mgt->clear();
    ui->oth_direct_oth->clear();
    ui->tot_oth_direct->clear();

    ui->indirect_rtd->clear();
    ui->indirect_dem->clear();
    ui->indirect_mgt->clear();
    ui->indirect_oth->clear();
    ui->tot_indirect->clear();

    ui->tot_rtd->clear();
    ui->tot_dem->clear();
    ui->tot_mgt->clear();
    ui->tot_oth->clear();
}

void MainWindow::set_indirect_perc(){
    ui->indirect_perc->setText("0.25");
    indirect_per = ui->indirect_perc->text().toFloat();
}

int MainWindow::get_indirect_perc(){
    return indirect_per;
}

void MainWindow::setToolTip(){
    ui->rtdLbl_2->setToolTip(tr("Research and technological development"));
    ui->demLbl_2->setToolTip(tr("Demonstration"));
    ui->mgtLbl_2->setToolTip(tr("Management of the consortium"));
    ui->othLbl->setToolTip(tr("Other specific activities"));
}

void MainWindow::set_validators(){
    ui->rtd_pm->setValidator(new QIntValidator(0,100,this));
    ui->dem_pm->setValidator(new QIntValidator(0,100,this));
    ui->mgt_pm->setValidator(new QIntValidator(0,100,this));
    ui->tot_pm->setValidator(new QIntValidator(0,100,this));
}

void MainWindow::setGuiStyle(){
    this->setStyleSheet("background-color :white");
    ui->basicsLyt->setStyleSheet("background-color :black ; color : white");
    ui->resultLyt->setStyleSheet("background-color :black ; color : white");
}

MainWindow::~MainWindow()
{
    delete ui;
}


