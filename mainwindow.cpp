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

    connect(ui->clearAllBtn,SIGNAL(clicked()),this,SLOT(clearAllFields()));

    connect(ui->rtd_pm,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));
    connect(ui->dem_pm,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));
    connect(ui->mgt_pm,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));
    connect(ui->pm_cost,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));

    connect(ui->travel_cost,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));
    connect(ui->equip_cost,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));

    connect(ui->persoanl_oth,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));

    connect(ui->sub_con_rtd,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));
    connect(ui->sub_con_dem,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));
    connect(ui->sub_con_mgt,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));
    connect(ui->sub_con_oth,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));

    connect(ui->oth_direct_dem,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));
    connect(ui->oth_direct_oth,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));

    connect(ui->indirect_perc,SIGNAL(textEdited(QString)),this,SLOT(indirectCal()));
    connect(ui->oth_direct_rtd,SIGNAL(textChanged(QString)),this,SLOT(indirectCal()));
    connect(ui->oth_direct_dem,SIGNAL(textEdited(QString)),this,SLOT(indirectCal()));
    connect(ui->oth_direct_mgt,SIGNAL(textChanged(QString)),this,SLOT(indirectCal()));
    connect(ui->indirect_oth,SIGNAL(textEdited(QString)),this,SLOT(indirectCal()));

    connect(ui->tot_persoanl,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
    connect(ui->tot_sub_con,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
    connect(ui->tot_oth_direct,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
    connect(ui->tot_indirect,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
}

void MainWindow::persoanlCal(){

    int rtd_pm = ui->rtd_pm->text().toInt();
    int dem_pm = ui->dem_pm->text().toInt();
    int mgt_pm = ui->mgt_pm->text().toInt();
    int tot_pm = rtd_pm + dem_pm + mgt_pm;

    double pm_cost = ui->pm_cost->text().toDouble();

    double personal_rtd = pm_cost*rtd_pm;
    double personal_dem = pm_cost*dem_pm;
    double personal_mgt = pm_cost*mgt_pm;
    double personal_oth = ui->persoanl_oth->text().toDouble();

    double tot_persoanl = personal_rtd + personal_dem + personal_mgt + personal_oth;

    ui->persoanl_rtd->setText(formatNumber(personal_rtd));
    ui->persoanl_dem->setText(formatNumber(personal_dem));
    ui->personal_mgt->setText(formatNumber(personal_mgt));

    ui->tot_persoanl->setText(formatNumber(tot_persoanl));

    ui->tot_pm->setText(QString::number(tot_pm));
    totalCategory();
}

void MainWindow::SubcontractingCal(){

    double sub_con_rtd = ui->sub_con_rtd->text().toDouble();
    double sub_con_dem = ui->sub_con_dem->text().toDouble();
    double sub_con_mgt = ui->sub_con_mgt->text().toDouble();
    double sub_con_oth = ui->sub_con_oth->text().toDouble();

    double tot_sub_con = sub_con_dem + sub_con_rtd + sub_con_mgt + sub_con_oth;

    ui->tot_sub_con->setText(formatNumber(tot_sub_con));
    totalCategory();
}

void MainWindow::othDirectCal(){
    double travel_cost = ui->travel_cost->text().toDouble();
    double equip_cost = ui->equip_cost->text().toDouble();

    double oth_direct_rtd = travel_cost + equip_cost;
    double oth_direct_dem = ui->oth_direct_dem->text().toDouble();
    double oth_direct_mgt = travel_cost;
    double oth_direct_oth = ui->oth_direct_oth->text().toDouble();

    ui->oth_direct_rtd->setText(formatNumber(oth_direct_rtd));
    ui->oth_direct_mgt->setText(formatNumber(oth_direct_mgt));

    double tot_oth_direct = oth_direct_rtd + oth_direct_dem + oth_direct_mgt + oth_direct_oth;

    ui->tot_oth_direct->setText(formatNumber(tot_oth_direct));
    totalCategory();
}


void MainWindow::set_indirect_perc(){
    indirect_perc = ui->indirect_perc->text().toDouble();
}

void MainWindow::indirectCal(){

    set_indirect_perc();

    double pm_cost = ui->pm_cost->text().toDouble();

    int rtd_pm = ui->rtd_pm->text().toInt();
    double personal_rtd = pm_cost*rtd_pm;
    double oth_direct_rtd = ui->oth_direct_rtd->text().toDouble();
    double indirect_rtd = (oth_direct_rtd + personal_rtd) * indirect_perc;
    ui->indirect_rtd->setText(formatNumber(indirect_rtd));

    int dem_pm = ui->dem_pm->text().toInt();
    double personal_dem = pm_cost*dem_pm;
    double oth_direct_dem = ui->oth_direct_dem->text().toDouble();
    double indirect_dem = (oth_direct_dem + personal_dem) * indirect_perc;
    ui->indirect_dem->setText(formatNumber(indirect_dem));

    int mgt_pm = ui->mgt_pm->text().toInt();
    double personal_mgt = pm_cost*mgt_pm;
    double oth_direct_mgt = ui->oth_direct_mgt->text().toDouble();
    double indirect_mgt = (oth_direct_mgt + personal_mgt) * indirect_perc;
    ui->indirect_mgt->setText(formatNumber(indirect_mgt));

    double indirect_oth = ui->indirect_oth->text().toDouble();

    double tot_indirect = indirect_dem + indirect_rtd + indirect_mgt + indirect_oth;

    ui->tot_indirect->setText(formatNumber(tot_indirect));

    totalCategory();
}

void MainWindow::totalCategory(){

    double personal_rtd = ui->persoanl_rtd->text().toDouble();
    double sub_con_rtd = ui->sub_con_rtd->text().toDouble();
    double oth_direct_rtd = ui->oth_direct_rtd->text().toDouble();
    double indirect_rtd = ui->indirect_rtd->text().toDouble();
    double tot_rtd = personal_rtd + sub_con_rtd + oth_direct_rtd + indirect_rtd;
    ui->tot_rtd->setText(formatNumber(tot_rtd));

    double personal_dem = ui->persoanl_dem->text().toDouble();
    double sub_con_dem = ui->sub_con_dem->text().toDouble();
    double oth_direct_dem = ui->oth_direct_dem->text().toDouble();
    double indirect_dem= ui->indirect_dem->text().toDouble();
    double tot_dem = personal_dem + sub_con_dem + oth_direct_dem + indirect_dem;
    ui->tot_dem->setText(formatNumber(tot_dem));

    double personal_mgt = ui->personal_mgt->text().toDouble();
    double sub_con_mgt = ui->sub_con_mgt->text().toDouble();
    double oth_direct_mgt = ui->oth_direct_mgt->text().toDouble();
    double indirect_mgt = ui->indirect_mgt->text().toDouble();
    double tot_mgt = personal_mgt + sub_con_mgt + oth_direct_mgt + indirect_mgt;
    ui->tot_mgt->setText(formatNumber(tot_mgt));

    double personal_oth = ui->persoanl_oth->text().toDouble();
    double sub_con_oth = ui->sub_con_oth->text().toDouble();
    double oth_direct_oth = ui->oth_direct_oth->text().toDouble();
    double indirect_oth = ui->indirect_oth->text().toDouble();
    double tot_oth = personal_oth + sub_con_oth + oth_direct_oth + indirect_oth;
    ui->tot_oth->setText(formatNumber(tot_oth));

}

void MainWindow::totalFundCal(){
    double tot_personal = ui->tot_persoanl->text().toDouble();
    double tot_sub_con = ui->tot_sub_con->text().toDouble();
    double tot_oth_direct = ui->tot_oth_direct->text().toDouble();
    double tot_indirect = ui->tot_indirect->text().toDouble();

    double tot_fund = tot_personal + tot_sub_con + tot_oth_direct + tot_indirect;

    ui->fund_lcd->display(tot_fund);
}

void MainWindow::clearAllFields(){
    ui->rtd_pm->clear();
    ui->dem_pm->clear();
    ui->mgt_pm->clear();
    ui->tot_pm->clear();
    ui->pm_cost->clear();

    ui->travel_cost->clear();
    ui->equip_cost->clear();
    ui->indirect_perc->clear();

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

void MainWindow::setToolTip(){
    ui->rtdLbl_2->setToolTip(tr("Research and technological development"));
    ui->demLbl_2->setToolTip(tr("Demonstration"));
    ui->mgtLbl_2->setToolTip(tr("Management of the consortium"));
    ui->othLbl->setToolTip(tr("Other specific activities"));
}

void MainWindow::set_validators(){

    QIntValidator *int_no = new QIntValidator(0,100,this);
    QDoubleValidator *double_no = new QDoubleValidator(0,10000000000,3,this);

    ui->rtd_pm->setValidator(int_no);
    ui->dem_pm->setValidator(int_no);
    ui->mgt_pm->setValidator(int_no);
    ui->tot_pm->setValidator(int_no);

    ui->travel_cost->setValidator(double_no);
    ui->travel_cost->setValidator(double_no);

    ui->indirect_perc->setValidator(new QDoubleValidator(0,0,2,this));

    ui->persoanl_rtd->setValidator(double_no);
    ui->persoanl_dem->setValidator(double_no);
    ui->personal_mgt->setValidator(double_no);
    ui->persoanl_oth->setValidator(double_no);
    ui->tot_persoanl->setValidator(double_no);

    ui->sub_con_rtd->setValidator(double_no);
    ui->sub_con_dem->setValidator(double_no);
    ui->sub_con_mgt->setValidator(double_no);
    ui->sub_con_oth->setValidator(double_no);
    ui->tot_sub_con->setValidator(double_no);

    ui->oth_direct_rtd->setValidator(double_no);
    ui->oth_direct_dem->setValidator(double_no);
    ui->oth_direct_mgt->setValidator(double_no);
    ui->oth_direct_oth->setValidator(double_no);
    ui->tot_oth_direct->setValidator(double_no);

    ui->indirect_rtd->setValidator(double_no);
    ui->indirect_dem->setValidator(double_no);
    ui->indirect_mgt->setValidator(double_no);
    ui->indirect_oth->setValidator(double_no);
    ui->tot_indirect->setValidator(double_no);

    ui->tot_rtd->setValidator(double_no);
    ui->tot_dem->setValidator(double_no);
    ui->tot_mgt->setValidator(double_no);
    ui->tot_oth->setValidator(double_no);
}

QString MainWindow::formatNumber(double number){
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    QLocale aEnglish;
    return aEnglish.toString(number);
}

void MainWindow::setGuiStyle(){
    this->setStyleSheet("background-color :white");
    //ui->basicsLyt->setStyleSheet("background-color :black ; color : white");
    //ui->resultLyt->setStyleSheet("background-color :black ; color : white");
}

MainWindow::~MainWindow()
{
    delete ui;
}


