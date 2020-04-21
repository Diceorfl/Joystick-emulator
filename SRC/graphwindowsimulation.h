#ifndef GRAPHWINDOWSIMULATION_H
#define GRAPHWINDOWSIMULATION_H

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <QMouseEvent>
#include <QKeyEvent>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DRender/QAttribute>
#include "cameracontroller.h"

class graphwindowsimulation: public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT
public:
    graphwindowsimulation();
    void loading(const QString);
    void setmpoint(QVector3D);
    void clear();

signals:
    void start(float);
    void sendvalue(float,float,float);

private:
    Qt3DCore::QEntity *rootEntity;
    cameracontroller *cameraController;
    bool flag = false;
    bool anglestatus = false;
    bool speedstatus = false;
    bool accelerationstatus = false;
    float time = 0.0;
    float anglevalue = 0.0;
    float speedvalue = 0;
    float accelerationvalue = 0;
    float coefforangle = 0.0f;
    float coefforspeed = 0.0f;
    float coefforacceleration = 0.0f;
    QVector3D Axis = QVector3D(0,0,0);
    QTimer *timer;
    QTimer *valuetimer;

private slots:
    void move();
    void getangleactive(bool);
    void getspeedactive(bool);
    void getaccelerationactive(bool);
    void gettime(float);
    void getcoef(float,int);
    void getAxis(QVector3D);
    void sendvalue();

protected:
    void wheelEvent ( QWheelEvent * ev ) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void keyPressEvent(QKeyEvent *ev) override;
    void keyReleaseEvent(QKeyEvent *ev) override;

};

#endif // GRAPHWINDOWSIMULATION_H
