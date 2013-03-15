#include "primerfound.h"
#include "ui_primerfound.h"

primerfound::primerfound(std::string p1, uint n1, std::string p2, uint n2, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::primerfound)
{
    ui->setupUi(this);

    this->ui->lineEditPrimer1->setText(QString::fromStdString(p1));
    this->ui->lineEditPrimer2->setText(QString::fromStdString(p2));
    this->ui->lineEditProduct1->setText(QString::number(n1));
    this->ui->lineEditProduct2->setText(QString::number(n2));
}

primerfound::~primerfound()
{
    delete ui;
}
