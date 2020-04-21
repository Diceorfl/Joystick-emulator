#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <Qt3DCore/QEntity>
#include <Qt3DInput/QMouseDevice>
#include <Qt3DInput/QLogicalDevice>
#include <Qt3DInput/QAction>
#include <Qt3DInput/QActionInput>
#include <Qt3DInput/QAxis>
#include <Qt3DInput/QAnalogAxisInput>
#include <Qt3DRender/QCamera>
#include <Qt3DLogic/QFrameAction>

class cameracontroller: public Qt3DCore::QEntity
{
     Q_OBJECT
public:
    cameracontroller(Qt3DCore::QNode *parent = Q_NULLPTR);

    void setCamera(Qt3DRender::QCamera *camera);
    float lookSpeed() const;
    void setLookSpeed(float lookSpeed);
    float linearSpeed() const;
    void setLinearSpeed(float linearSpeed);

protected slots:
    void activeChanged(bool isActive);
    void valueChanged(float value);
    void frameActionTriggered(float dt);

private:
    Qt3DInput::QMouseDevice *m_mouseDevice;
    Qt3DInput::QLogicalDevice *m_logicalDevice;

    Qt3DInput::QAction *m_leftButtonAction;
    Qt3DInput::QActionInput *m_leftButtonInput;
    Qt3DInput::QAxis *m_xAxis;
    Qt3DInput::QAxis *m_yAxis;
    Qt3DInput::QAnalogAxisInput *m_mouseXInput;
    Qt3DInput::QAnalogAxisInput *m_mouseYInput;

    Qt3DLogic::QFrameAction *m_frameAction;

    Qt3DRender::QCamera *m_camera;
    float m_lookSpeed;
    float m_linearSpeed;

    bool m_leftButtonPressed;

    float m_dx;
    float m_dy;
    bool flag = false;
};

#endif // CAMERACONTROLLER_H
