#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include <detector.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <QtCore>

using namespace std;
using namespace cv;

// Threshold value
static int SENS_VAL = 20;
static int OBJ_NUM = 0;

int *obj_number = &OBJ_NUM;
int *threshold_value = &SENS_VAL;

static Mat rawimg;

//QImage imdisplay;
QImage imdisplay((uchar*)rawimg.data, rawimg.cols, rawimg.rows, rawimg.step, QImage::Format_RGB888);

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    ui->thresholdHorizontalSlider->setRange(0,255);
    ui->thresholdHorizontalSlider->setSliderPosition(20);

    tmrTimer = new QTimer(this);


//    VideoCapture video;
//    video.open("/home/vinhnc/Downloads/sukhoi.mp4");
//    Mat frame;
//    video.read(frame);
    video.open("/home/vinhnc/Downloads/sukhoi.mp4");
    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
    tmrTimer->start(5);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_browseVideoPushButton_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Video", QDir::currentPath(), "Video (*.mp4 *.avi)");
    if(QFile::exists(fileName))
    {
        ui->videoURLLineEdit->setText(fileName);
    }
}

void Widget::on_trackingObj_1_PushButton_pressed()
{
    if(OBJ_NUM == 0)
    {
        QMessageBox::about(this, "Warning", "No object detected");
    }
    else
    {

    }
}

void Widget::on_trackingObj_2_PushButton_pressed()
{
    if(OBJ_NUM < 2)
    {
        QMessageBox::about(this, "Warning", "No object detected");
    }
    else
    {

    }
}

void Widget::on_trackingObj_3_PushButton_pressed()
{
    if(OBJ_NUM < 3)
    {
        QMessageBox::about(this, "Warning", "No object detected");
    }
    else
    {

    }
}

void Widget::on_trackingObj_4_PushButton_pressed()
{
    if(OBJ_NUM < 4)
    {
        QMessageBox::about(this, "Warning", "No object detected");
    }
    else
    {

    }
}

void Widget::on_trackingObj_5_PushButton_pressed()
{
    if(OBJ_NUM < 5)
    {
        QMessageBox::about(this, "Warning", "No object detected");
    }
    else
    {

    }
}

void Widget::on_playVideoPushButton_pressed()
{
    // Get path to Video
    QString videoPath = ui->videoURLLineEdit->text();

    // Throw a message box when video path is blank
    if(videoPath == "")
    {
        QMessageBox::about(this, "Warning", "Please choose a video");
    }
    else
    {
        cv::Mat img = detector(videoPath);
        rawimg = img;
    }
}

//void Widget::closeEvent(QCloseEvent *event)
//{
//    int result = QMessageBox::warning(this, "Exit", "Are you sure you want to close this program?", QMessageBox::Yes, QMessageBox::No);

//    if(result == QMessageBox::Yes)
//    {
//        event->accept();
//    }
//    else
//    {
//        event->ignore();
//    }
//}

void Widget::on_thresholdHorizontalSlider_valueChanged(int value)
{
    QString tValue = QString::number(value);
    ui->thresholdValueLineEdit->setText(tValue);
    *threshold_value = value;
}

cv::Mat Widget::detector(QString videoPath)
{
    cv::Mat img = detect(videoPath);
    return img;
}

void Widget::processFrameAndUpdateGUI()
{

    video.read(frame);
    cvtColor(frame, frame, CV_BGR2RGB);
    QImage imgdp((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    ui->imgViewer->setPixmap(QPixmap::fromImage(imgdp));
}
