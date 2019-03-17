#ifndef CAMERAFACERECOGNITION_H
#define CAMERAFACERECOGNITION_H

#include <QObject>
#include <QCameraInfo>
#include "lib/facerecognitionvideosurface.h"

class CameraFaceRecognition : public QObject
{
    Q_OBJECT
public:
    explicit CameraFaceRecognition(QObject *parent = nullptr);
    QStringList getCameras();
    bool startCamera(QString deviceName = QCameraInfo::defaultCamera().deviceName());

signals:
    /**
     * @brief frameAvailable
     * @param ts Frame timestamp
     * @param frame Frame
     */
    void frameAvailable(qint64 ts, QImage frame);

private:
    bool checkCameraAvailability();
    void loadCameras();

private:
    QHash<QString, QCameraInfo> m_cameras;
    QCamera *m_camera;
    FaceRecognitionVideoSurface *m_faceRecognitionVideoSurface;
};

#endif // CAMERAFACERECOGNITION_H
