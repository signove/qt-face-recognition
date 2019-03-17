#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib/camerafacerecognition.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CameraFaceRecognition* camera = new CameraFaceRecognition();
    connect(camera, SIGNAL(frameAvailable(qint64, QImage)), this, SLOT(onFrameAvailable(qint64, QImage)));
    camera->startCamera();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFrameAvailable(qint64 ts, QImage frame)
{
    qDebug() << ts << frame.width();
}

void MainWindow::paintImage(QImage)
{

}
