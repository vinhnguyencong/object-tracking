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
    ui->thresholdHorizontalSlider->setRange(0,255);
    ui->thresholdHorizontalSlider->setSliderPosition(20);

    //ui->label_2->setPixmap(QPixmap::fromImage(QImage(rawimg.data(), rawimg.col)));
    ui->videoWidget->setp

    ui->label_2->setPixmap(QPixmap::fromImage(imdisplay));
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
