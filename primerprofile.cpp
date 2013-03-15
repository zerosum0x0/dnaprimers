#include "primerprofile.h"
#include "ui_primerprofile.h"

PrimerProfile::PrimerProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrimerProfile)
{
    ui->setupUi(this);
}

PrimerProfile::~PrimerProfile()
{
    delete ui;
}

void PrimerProfile::on_pushButton_clicked()
{
    emit this->findProfile(this->ui->spinBoxLengthMin->value(), this->ui->spinBoxLengthMax->value(),
                           this->ui->doubleSpinBoxTempMin->value(), this->ui->doubleSpinBoxTempMax->value(),
                           this->ui->doubleSpinBoxContentMin->value(), this->ui->doubleSpinBoxContentMax->value(),
                           this->ui->checkBoxStartSequence->isChecked(), this);
}
