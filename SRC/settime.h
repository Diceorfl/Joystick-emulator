#ifndef SETTIME_H
#define SETTIME_H

#include <QDialog>
#include <QVector3D>

namespace Ui {
class SetTime;
}

class SetTime : public QDialog
{
    Q_OBJECT

public:
    explicit SetTime(QWidget *parent = nullptr);
    ~SetTime();

signals:
    void sendtime(float);
    void sendcoef(float,int);
    void sendAxis(QVector3D);
    void sendangleactive(bool);
    void sendspeedactive(bool);
    void sendaccelerationactive(bool);

private slots:
    void on_pushButton_clicked();

    void on_checkBox_4_stateChanged();

    void on_checkBox_5_stateChanged();

    void on_checkBox_6_stateChanged();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

private:
    Ui::SetTime *ui;
    float time = 1.0f;
};

#endif // SETTIME_H
