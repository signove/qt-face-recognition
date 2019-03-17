#include "camerafacerecognition.h"
#include <QCameraInfo>

#define CLASS_NAME "::CameraFaceRecognition::"

CameraFaceRecognition::CameraFaceRecognition(QObject *parent) :
    QObject(parent), m_camera(nullptr), m_faceRecognitionVideoSurface(nullptr)
{
    loadCameras();
}

QStringList CameraFaceRecognition::getCameras()
{
    return m_cameras.keys();
}

bool CameraFaceRecognition::startCamera(QString deviceName)
{
    qDebug() << CLASS_NAME << "startCamera - " << deviceName;
    if(!m_cameras.contains(deviceName))
    {
        return false;
    }
    else
    {
        if(m_camera != nullptr)
        {
            m_camera->deleteLater();
            m_camera = nullptr;
        }
        if(m_faceRecognitionVideoSurface != nullptr)
        {
            m_faceRecognitionVideoSurface->deleteLater();
            m_faceRecognitionVideoSurface = nullptr;
        }
        m_camera = new QCamera(m_cameras.value(deviceName));
        m_faceRecognitionVideoSurface = new FaceRecognitionVideoSurface(this);
        connect(m_faceRecognitionVideoSurface, SIGNAL(frameAvailable(qint64, QImage)), this, SIGNAL(frameAvailable(qint64, QImage)));
        m_camera->setViewfinder(m_faceRecognitionVideoSurface);
        m_camera->start();
        return true;
    }
}

void CameraFaceRecognition::loadCameras()
{
    m_cameras.clear();
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras)
    {
        m_cameras.insert(cameraInfo.deviceName(), cameraInfo);
    }
}

bool CameraFaceRecognition::checkCameraAvailability()
{
    if (QCameraInfo::availableCameras().count() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
