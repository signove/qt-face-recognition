#ifndef FACERECOGNITIONVIDEOSURFACE_H
#define FACERECOGNITIONVIDEOSURFACE_H

#include <QAbstractVideoSurface>

class FaceRecognitionVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit FaceRecognitionVideoSurface(QObject *parent = nullptr);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const;

    bool present(const QVideoFrame &frame);

signals:

    /**
     * @brief frameAvailable
     * @param ts Frame timestamp
     * @param frame Frame
     */
    void frameAvailable(qint64 ts, QImage frame);

private:
    qint64 m_latestPresentCall;

};

#endif // FACERECOGNITIONVIDEOSURFACE_H
