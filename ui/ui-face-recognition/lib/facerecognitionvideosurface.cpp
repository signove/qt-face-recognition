#include "facerecognitionvideosurface.h"
#include <QDebug>
#include <QDateTime>

#define CLASS_NAME "::FaceRecognitionVideoSurface::"

FaceRecognitionVideoSurface::FaceRecognitionVideoSurface(QObject *parent) : QAbstractVideoSurface(parent), m_latestPresentCall(0)
{

}

QList<QVideoFrame::PixelFormat> FaceRecognitionVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const
{
    qDebug() << CLASS_NAME << "supportedPixelFormats :: " << type;
    if(type == QAbstractVideoBuffer::NoHandle)
    {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_RGB24
                << QVideoFrame::Format_RGB565
                << QVideoFrame::Format_RGB555
                << QVideoFrame::Format_ARGB8565_Premultiplied
                << QVideoFrame::Format_BGRA32
                << QVideoFrame::Format_BGRA32_Premultiplied
                << QVideoFrame::Format_BGR32
                << QVideoFrame::Format_BGR24
                << QVideoFrame::Format_BGR565
                << QVideoFrame::Format_BGR555
                << QVideoFrame::Format_BGRA5658_Premultiplied
                << QVideoFrame::Format_AYUV444
                << QVideoFrame::Format_AYUV444_Premultiplied
                << QVideoFrame::Format_YUV444
                << QVideoFrame::Format_YUV420P
                << QVideoFrame::Format_YV12
                << QVideoFrame::Format_UYVY
                << QVideoFrame::Format_YUYV
                << QVideoFrame::Format_NV12
                << QVideoFrame::Format_NV21
                << QVideoFrame::Format_IMC1
                << QVideoFrame::Format_IMC2
                << QVideoFrame::Format_IMC3
                << QVideoFrame::Format_IMC4
                << QVideoFrame::Format_Y8
                << QVideoFrame::Format_Y16
                << QVideoFrame::Format_Jpeg
                << QVideoFrame::Format_CameraRaw
                << QVideoFrame::Format_AdobeDng;
    }
    else
    {
        return QList<QVideoFrame::PixelFormat>();
    }
}

bool FaceRecognitionVideoSurface::present(const QVideoFrame &frame)
{
    qint64 currentCall = QDateTime::currentMSecsSinceEpoch();
    if (frame.isValid()) {
        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
        qDebug() << cloneFrame.pixelFormat();
        qDebug() << QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat());
        QImage image(cloneFrame.bits(),
                     cloneFrame.width(),
                     cloneFrame.height(),
                     cloneFrame.bytesPerLine(),
                     QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat()));
        qDebug() << image.size();
        emit frameAvailable(currentCall - m_latestPresentCall, image);
        m_latestPresentCall = currentCall;
        cloneFrame.unmap();
        return true;
    }
    return false;
}
