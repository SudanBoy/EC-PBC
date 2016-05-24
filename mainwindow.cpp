#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("European Commission Project Budget Calculator");

    connect(ui->exitBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->clearAll,SIGNAL(clicked()),this,SLOT(clearAllFields()));

    connect(ui->costPm_value,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));
    connect(ui->rtd_value,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));
    connect(ui->dem_value,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));
    connect(ui->mgt_value,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));

    connect(ui->persoanl_oth,SIGNAL(textEdited(QString)),this,SLOT(persoanlCal()));

    connect(ui->subCon_dem,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));
    connect(ui->subCon_rtd,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));
    connect(ui->subCon_mgt,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));
    connect(ui->subCon_oth,SIGNAL(textEdited(QString)),this,SLOT(SubcontractingCal()));

    connect(ui->travel,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));
    connect(ui->equip,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));

    connect(ui->othDirectCost_dem,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));
    connect(ui->othDirectCost_oth,SIGNAL(textEdited(QString)),this,SLOT(othDirectCal()));

    connect(ui->othDirectCost_rtd,SIGNAL(textChanged(QString)),this,SLOT(inDirectCal()));
    connect(ui->othDirectCost_dem,SIGNAL(textEdited(QString)),this,SLOT(inDirectCal()));
    connect(ui->othDirectCost_mgt,SIGNAL(textChanged(QString)),this,SLOT(inDirectCal()));
    connect(ui->indirectCost_oth,SIGNAL(textEdited(QString)),this,SLOT(inDirectCal()));

    connect(ui->persoanl_total,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
    connect(ui->subCon_total,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
    connect(ui->othDirectCost_total,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
    connect(ui->indirectCost_total,SIGNAL(textChanged(QString)),this,SLOT(totalFundCal()));
}


void MainWindow::close(){
    QCoreApplication::quit();
}

void MainWindow::persoanlCal(){
    int costPm_value = ui->costPm_value->text().toInt();

    int dem_value = ui->dem_value->text().toInt();
    int personal_dem = costPm_value*dem_value;

    int rtd_value = ui->rtd_value->text().toInt();
    int personal_rtd = costPm_value*rtd_value;

    int mgt_value = ui->mgt_value->text().toInt();
    int personal_mgt = costPm_value*mgt_value;

    int personal_oth = ui->persoanl_oth->text().toInt();

    int totalMP = rtd_value + dem_value + mgt_value;
    int persoanl_total = personal_rtd + personal_dem + personal_mgt + personal_oth;

    ui->persoanl_rtd->setText(QString::number(personal_rtd));
    ui->persoanl_dem->setText(QString::number(personal_dem));
    ui->personal_mgt->setText(QString::number(personal_mgt));
    ui->persoanl_total->setText(QString::number(persoanl_total));

    ui->totalPm_value->setText(QString::number(totalMP));
}

void MainWindow::SubcontractingCal(){

    int subCon_dem = ui->subCon_dem->text().toInt();
    int subCon_rtd = ui->subCon_rtd->text().toInt();
    int subCon_mgt = ui->subCon_mgt->text().toInt();
    int subCon_oth = ui->subCon_oth->text().toInt();

    int total_subCon = subCon_dem + subCon_rtd + subCon_mgt + subCon_oth;

    ui->subCon_total->setText(QString::number(total_subCon));
}

void MainWindow::othDirectCal(){
    int travel = ui->travel->text().toInt();
    int equip = ui->equip->text().toInt();
    int othDirectCost_dem = ui->othDirectCost_dem->text().toInt();
    int othDirectCost_mgt = travel;
    int othDirectCost_oth = ui->othDirectCost_oth->text().toInt();
    int othDirectCost_rtd = ui->othDirectCost_rtd->text().toInt();

    othDirectCost_rtd = travel + equip;
    ui->othDirectCost_rtd->setText(QString::number(othDirectCost_rtd));
    ui->othDirectCost_mgt->setText(QString::number(othDirectCost_mgt));

    int othDirectCost_total = othDirectCost_rtd + othDirectCost_dem + othDirectCost_mgt + othDirectCost_oth;

    ui->othDirectCost_total->setText(QString::number(othDirectCost_total));
}

void MainWindow::inDirectCal(){

    int costPm_value = ui->costPm_value->text().toInt();

    int dem_value = ui->dem_value->text().toInt();
    int personal_dem = costPm_value*dem_value;
    int othDirectCost_dem = ui->othDirectCost_dem->text().toInt();
    int indirectCost_dem = (othDirectCost_dem + personal_dem) * 0.25;
    ui->indirectCost_dem->setText(QString::number(indirectCost_dem));

    int rtd_value = ui->rtd_value->text().toInt();
    int personal_rtd = costPm_value*rtd_value;
    int othDirectCost_rtd = ui->othDirectCost_rtd->text().toInt();
    int indirectCost_rtd = (othDirectCost_rtd + personal_rtd) * 0.25;
    ui->indirectCost_rtd->setText(QString::number(indirectCost_rtd));

    int mgt_value = ui->mgt_value->text().toInt();
    int personal_mgt = costPm_value*mgt_value;
    int othDirectCost_mgt = ui->othDirectCost_mgt->text().toInt();
    int indirectCost_mgt = (othDirectCost_mgt + personal_mgt) * 0.25;
    ui->indirectCost_mgt->setText(QString::number(indirectCost_mgt));

    int indirect_oth = ui->indirectCost_oth->text().toInt();

    int total_indirect = indirectCost_dem + indirectCost_rtd + indirectCost_mgt + indirect_oth;

    ui->indirectCost_total->setText(QString::number(total_indirect));
}

void MainWindow::totalFundCal(){
    int total_personal = ui->persoanl_total->text().toInt();
    int total_subContract = ui->subCon_total->text().toInt();
    int total_otherDirect = ui->othDirectCost_total->text().toInt();
    int total_indirect = ui->indirectCost_total->text().toInt();

    int Fund = total_personal + total_subContract + total_otherDirect + total_indirect;

    ui->fund_lcdn->display(Fund);
    ui->fund_value->setText(QString::number(Fund));
}

void MainWindow::clearAllFields(){
    ui->rtd_value->clear();
    ui->dem_value->clear();
    ui->mgt_value->clear();
    ui->totalPm_value->clear();
    ui->costPm_value->clear();

    ui->persoanl_rtd->clear();
    ui->persoanl_dem->clear();
    ui->personal_mgt->clear();
    ui->persoanl_oth->clear();
    ui->persoanl_total->clear();

    ui->subCon_rtd->clear();
    ui->subCon_dem->clear();
    ui->subCon_mgt->clear();
    ui->subCon_oth->clear();
    ui->subCon_total->clear();

    ui->travel->clear();
    ui->equip->clear();
    ui->othDirectCost_rtd->clear();
    ui->othDirectCost_dem->clear();
    ui->othDirectCost_mgt->clear();
    ui->othDirectCost_oth->clear();
    ui->othDirectCost_total->clear();

    ui->indirectCost_rtd->clear();
    ui->indirectCost_dem->clear();
    ui->indirectCost_mgt->clear();
    ui->indirectCost_oth->clear();
    ui->indirectCost_total->clear();

    ui->rtd_total->clear();
    ui->dem_total->clear();
    ui->mgt_total->clear();
    ui->oth_total->clear();

    ui->fund_value->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}
