#include "cameracontroller.h"

cameracontroller::cameracontroller(Qt3DCore::QNode *parent):
    Qt3DCore::QEntity (parent)
{
    m_leftButtonPressed = false;
    m_dx = 0;
    m_dy = 0;
    m_lookSpeed = 180.0;
    m_linearSpeed = 25.0;
    m_camera = 0;

    m_mouseDevice = new Qt3DInput::QMouseDevice(this);
    m_logicalDevice = new Qt3DInput::QLogicalDevice(this);

    m_leftButtonAction = new Qt3DInput::QAction(this);
    m_leftButtonInput = new  Qt3DInput::QActionInput(this);
    m_xAxis = new  Qt3DInput::QAxis(this);
    m_yAxis = new  Qt3DInput::QAxis(this);
    m_mouseXInput = new Qt3DInput::QAnalogAxisInput(this);
    m_mouseYInput = new Qt3DInput::QAnalogAxisInput(this);

    m_frameAction = new Qt3DLogic::QFrameAction(this);

    m_leftButtonInput->setButtons(QVector<int>() << Qt::LeftButton);
    m_leftButtonInput->setSourceDevice(m_mouseDevice);
    m_leftButtonAction->addInput(m_leftButtonInput);
    m_leftButtonAction->setObjectName("leftButton");

    m_mouseXInput->setAxis(Qt3DInput::QMouseDevice::X);
    m_mouseXInput->setSourceDevice(m_mouseDevice);
    m_xAxis->addInput(m_mouseXInput);
    m_xAxis->setObjectName("xAxis");
    m_mouseYInput->setAxis(Qt3DInput::QMouseDevice::Y);
    m_mouseYInput->setSourceDevice(m_mouseDevice);
    m_yAxis->addInput(m_mouseYInput);
    m_yAxis->setObjectName("yAxis");

    m_logicalDevice->addAction(m_leftButtonAction);
    m_logicalDevice->addAxis(m_xAxis);
    m_logicalDevice->addAxis(m_yAxis);

    connect(m_leftButtonAction,SIGNAL(activeChanged(bool)),this,SLOT(activeChanged(bool)));
    connect(m_xAxis,SIGNAL(valueChanged(float)),this,SLOT(valueChanged(float)));
    connect(m_yAxis,SIGNAL(valueChanged(float)),this,SLOT(valueChanged(float)));
    connect(m_frameAction,SIGNAL(triggered(float)),this,SLOT(frameActionTriggered(float)));
}

void cameracontroller::setCamera(Qt3DRender::QCamera *camera)
{
    m_camera = camera;
}

float cameracontroller::lookSpeed() const
{
    return m_lookSpeed;
}

void cameracontroller::setLookSpeed(float lookSpeed)
{
    m_lookSpeed = lookSpeed;
}

float cameracontroller::linearSpeed() const
{
    return m_linearSpeed;
}

void cameracontroller::setLinearSpeed(float linearSpeed)
{
    m_linearSpeed = linearSpeed;
}

void cameracontroller::activeChanged(bool isActive)
{
    if(sender()->objectName() == "leftButton")
        m_leftButtonPressed = isActive;
}

void cameracontroller::valueChanged(float value)
{
    if(sender()->objectName() == "xAxis")
        m_dx = value;
    else if(sender()->objectName() == "yAxis")
        m_dy = value;
}

void cameracontroller::frameActionTriggered(float dt)
{
    if(m_camera == 0)
        return;

    if(m_leftButtonPressed == true)
    {
        m_camera->panAboutViewCenter(-m_dx * m_lookSpeed * dt);
        m_camera->tiltAboutViewCenter(-m_dy * m_lookSpeed * dt);
    }
}


