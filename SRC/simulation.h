#ifndef SIMULATION_H
#define SIMULATION_H

#include <QMainWindow>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QMessageBox>
#include <QVector3D>
#include "graphwindowsimulation.h"
#include "settime.h"
#include <QProgressBar>

namespace Ui {
class simulation;
}

class simulation : public QMainWindow
{
    Q_OBJECT

public:
    explicit simulation(QWidget *parent = nullptr);
    ~simulation();

signals:
    void senderror(QString);
    void sendpath(const QString);
    void sendfinishload();

private slots:
    void on_actionAdd_file_triggered();

    void geterror(QString);

    void getpath(const QString);

    void getfinishload();

    void on_actionClear_all_triggered();

    void getvalue(float,float,float);

    void on_actionTime_Coef_triggered();

private:
    Ui::simulation *ui;
    QFuture<void> future;
    QVector3D minpoints = QVector3D(0.0,0.0,0.0);
    QVector3D maxpoints = QVector3D(0.0,0.0,0.0);
    QWidget *container;
    graphwindowsimulation *window;

    void loading(const QStringList);
    bool solidcheck(QString &); // Проверяет наличие слова solid и пробела после него
    bool getPoint(QString &, QString &, QVector3D &); // Проверяет синтаксис в файле, если все корректно, то возрвращает координаты вершины или нормали
    bool getmPoint(QTextStream &,const QString &);
};

#endif // SIMULATION_H
