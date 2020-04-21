#include "settime.h"
#include "ui_settime.h"

SetTime::SetTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTime)
{
    ui->setupUi(this);
}

SetTime::~SetTime()
{
    delete ui;
}

void SetTime::on_pushButton_clicked()
{
    if(ui->lineEdit->text() != "")
    {
        time = ui->lineEdit->text().toFloat();
        emit sendtime(time);
    }
    if(ui->lineEdit_2->text() != "")
        emit sendcoef(ui->lineEdit_2->text().toFloat(),1);
    if(ui->lineEdit_3->text() != "")
        emit sendcoef(ui->lineEdit_3->text().toFloat()*(time/1000),2);
    if(ui->lineEdit_4->text() != "")
        emit sendcoef(ui->lineEdit_4->text().toFloat()*(time/1000)*(time/1000),3);
}

void SetTime::on_checkBox_4_stateChanged()
{
    if(ui->checkBox_4->isChecked())
        emit sendangleactive(true);
    else
        emit sendangleactive(false);
}

void SetTime::on_checkBox_5_stateChanged()
{
    if(ui->checkBox_5->isChecked())
        emit sendspeedactive(true);
    else
        emit sendspeedactive(false);
}

void SetTime::on_checkBox_6_stateChanged()
{
    if(ui->checkBox_6->isChecked())
        emit sendaccelerationactive(true);
    else
        emit sendaccelerationactive(false);
}

void SetTime::on_radioButton_clicked()
{
    if(ui->radioButton->isChecked())
    {
        ui->radioButton_2->setChecked(false);
        ui->radioButton_3->setChecked(false);
    }
    emit sendAxis(QVector3D(1,0,0));
}

void SetTime::on_radioButton_2_clicked()
{
    if(ui->radioButton_2->isChecked())
    {
        ui->radioButton->setChecked(false);
        ui->radioButton_3->setChecked(false);
    }
    emit sendAxis(QVector3D(0,1,0));
}

void SetTime::on_radioButton_3_clicked()
{
    if(ui->radioButton_3->isChecked())
    {
        ui->radioButton_2->setChecked(false);
        ui->radioButton->setChecked(false);
    }
    emit sendAxis(QVector3D(0,0,1));
}
