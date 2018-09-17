#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include <detector.h>

// Threshold value
static int SENS_VAL = 20;
static int OBJ_NUM = 0;
int *obj_number = &OBJ_NUM;
int *threshold_value = &SENS_VAL;


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->thresholdHorizontalSlider->setRange(0,255);
    ui->thresholdHorizontalSlider->setSliderPosition(20);
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
    detector(videoPath);

    // Throw a message box when video path is blank
//    if(videoPath == "")
//    {
//        QMessageBox::about(this, "Warning", "Please choose a video");
//    }
//    else
//    {
//        detector(videoPath);

//    }
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

void Widget::detector(QString videoPath)
{
    detect(videoPath);
}
