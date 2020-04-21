#include "graphwindowsimulation.h"
#include <QtMath>
#include <QTimer>
#include <QMessageBox>
#include <QExtrudedTextMesh>

graphwindowsimulation::graphwindowsimulation()
{
    this->defaultFrameGraph()->setClearColor((QColor(QRgb(0xCAEBF9))));
    Qt3DRender::QCamera *camera = this->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.01f, 30000.0f);
    camera->setPosition(QVector3D(500.0f, 500.0f, 500.0f));
    camera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));

     rootEntity = new Qt3DCore::QEntity();

     cameraController = new cameracontroller(rootEntity);
     cameraController->setCamera(camera);
     cameraController->setLookSpeed(180.0f);
     cameraController->setLinearSpeed(50.0f);

     Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(camera);
     Qt3DRender::QPointLight *pointLight = new Qt3DRender::QPointLight(lightEntity);
     pointLight->setColor("white");
     pointLight->setIntensity(1);
     Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
     lightTransform->setTranslation(camera->position());
     lightEntity->addComponent(pointLight);
     lightEntity->addComponent(lightTransform);

     this->setRootEntity(rootEntity);
     timer = new QTimer(this);
     valuetimer = new QTimer(this);
     connect(valuetimer,SIGNAL(timeout()), this, SLOT(sendvalue()));
     valuetimer->start(500);
}

void graphwindowsimulation::sendvalue()
{
    if(time != 0.0f)
        emit sendvalue(anglevalue,speedvalue,accelerationvalue/(time/1000));
    else
       emit sendvalue(0,0,0);
}

void graphwindowsimulation::getAxis(QVector3D Axisvalue)
{
    Axis = Axisvalue;
}

void graphwindowsimulation::move()
{
    this->camera()->panAboutViewCenter(speedvalue * (time/1000),Axis);
    speedvalue+= accelerationvalue;
}

void graphwindowsimulation::gettime(float Time)
{
    time = Time;
    timer->stop();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(move()));
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    if(speedstatus || accelerationstatus)
    {
        anglevalue = speedvalue = accelerationvalue = 0;
        timer->start(time);
    }
}

void graphwindowsimulation::getcoef(float value, int number)
{
    if(number == 1)
        coefforangle = value;
    if(number == 2)
        coefforspeed = value;
    if(number == 3)
        coefforacceleration = value;
}
void graphwindowsimulation::getangleactive(bool status)
{
    anglevalue = speedvalue = accelerationvalue = 0;
    if(status && !speedstatus && !accelerationstatus)
        timer->stop();
    anglestatus = status;
}

void graphwindowsimulation::getspeedactive(bool status)
{
    timer->start(time);
    anglevalue = speedvalue = accelerationvalue = 0;
    if(!status && !accelerationstatus)
        timer->stop();
    speedstatus = status;
}

void graphwindowsimulation::getaccelerationactive(bool status)
{
    timer->start(time);
    anglevalue = speedvalue = accelerationvalue = 0;
    if(!status && !speedstatus)
        timer->stop();
    accelerationstatus = status;
}

void graphwindowsimulation::wheelEvent(QWheelEvent *ev)
{
    if(!flag && speedstatus && !anglestatus && !accelerationstatus)
    {
        anglevalue+= coefforspeed*ev->delta()/120;
        speedvalue+= coefforspeed*ev->delta()/120/(time/1000);
        emit sendvalue(anglevalue,speedvalue,accelerationvalue/(time/1000));
    }
    if(!flag && anglestatus && !speedstatus && !accelerationstatus)
    {
        anglevalue+= coefforangle*ev->delta()/120;
        speedvalue+= coefforangle*ev->delta()/120/(time/1000);
        emit sendvalue(anglevalue,speedvalue,accelerationvalue/(time/1000));
        this->camera()->panAboutViewCenter(coefforangle*ev->delta()/120,Axis);
    }
    if(!flag && accelerationstatus && !anglestatus && !speedstatus)
    {
        anglevalue+= coefforacceleration*ev->delta()/120;
        accelerationvalue += coefforacceleration*ev->delta()/120/(time/1000);
        emit sendvalue(anglevalue,speedvalue,accelerationvalue/(time/1000));
    }
    if(!flag && anglestatus && speedstatus && !accelerationstatus)
    {
        anglevalue+= coefforangle*ev->delta()/120;
        speedvalue+= coefforspeed*ev->delta()/120/(time/1000);
        emit sendvalue(anglevalue,speedvalue,accelerationvalue/(time/1000));
        this->camera()->panAboutViewCenter(coefforangle*ev->delta()/120,Axis);
    }
    if(!flag && anglestatus && !speedstatus && accelerationstatus)
    {
        anglevalue+= coefforangle*ev->delta()/120;
        accelerationvalue += coefforacceleration*ev->delta()/120/(time/1000);
        emit sendvalue(anglevalue,speedvalue,accelerationvalue/(time/1000));
        this->camera()->panAboutViewCenter(coefforangle*ev->delta()/120,Axis);
    }
    if(!flag && !anglestatus && speedstatus && accelerationstatus)
    {
        speedvalue+= coefforspeed*ev->delta()/120/(time/1000);
        accelerationvalue += coefforacceleration*ev->delta()/120/(time/1000);
        emit sendvalue(anglevalue,speedvalue,accelerationvalue/(time/1000));
    }
    if(!flag && anglestatus && speedstatus && accelerationstatus)
    {
        anglevalue+= coefforangle*ev->delta()/120;
        speedvalue+= coefforspeed*ev->delta()/120/(time/1000);
        accelerationvalue += coefforacceleration*ev->delta()/120/(time/1000);
        emit sendvalue(anglevalue,speedvalue,accelerationvalue/(time/1000));
        this->camera()->panAboutViewCenter(coefforangle*ev->delta()/120,Axis);
    }
    if(!flag && !anglestatus && !speedstatus && !accelerationstatus)
    {
        anglevalue = speedvalue = accelerationvalue = 0;
    }
    if(flag)
    {
        QVector3D vec = this->camera()->position() - this->camera()->viewCenter();
        float cof;
        cof = vec.length()/500.0f;
        if(cof < 0.01f)
            cof = 0.01f;
        vec = vec.normalized();
        QPoint delta = ev->angleDelta();
        int zoom_distance = delta.y()*cof;
        vec = this->camera()->position() - zoom_distance*vec;
        this->camera()->setPosition(vec);
    }

}

void graphwindowsimulation::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::MiddleButton)
        anglevalue = speedvalue = accelerationvalue = 0;

}
void graphwindowsimulation::keyPressEvent(QKeyEvent *ev)
{
   if(ev->key()==Qt::Key_Control)
       flag = true;
}

void graphwindowsimulation::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_Control)
        flag = false;
}
void graphwindowsimulation::loading(const QString item)
{
    Qt3DRender::QMesh *object = new Qt3DRender::QMesh();
    object->setSource(QUrl::fromLocalFile(item));
    Qt3DExtras::QPhongMaterial *objectMaterial = new Qt3DExtras::QPhongMaterial();
    objectMaterial->setDiffuse(QColor(QRgb(0x458df9)));
    Qt3DCore::QEntity *objectEntity = new Qt3DCore::QEntity(rootEntity);
    objectEntity->setObjectName("obj");
    objectEntity->addComponent(object);
    objectEntity->addComponent(objectMaterial);
}

void graphwindowsimulation::setmpoint(QVector3D mpoint)
{
    timer->stop();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(move()));
    this->camera()->setViewCenter(mpoint);
}

void graphwindowsimulation::clear()
{
   for(int i = 0; i < rootEntity->children().length(); i++)
       if(rootEntity->children()[i]->objectName() == "obj")
           rootEntity->children()[i]->deleteLater();
   anglevalue = 0;
   speedvalue = 0;
   timer->stop();
   connect(timer, SIGNAL(timeout()), this, SLOT(move()));
   accelerationvalue = 0;
   time = 0;
}
