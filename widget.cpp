#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
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

}

void Widget::on_trackingObj_2_PushButton_pressed()
{

}

void Widget::on_trackingObj_3_PushButton_pressed()
{

}

void Widget::on_trackingObj_4_PushButton_pressed()
{

}

void Widget::on_trackingObj_5_PushButton_pressed()
{

}

void Widget::on_playVideoPushButton_pressed()
{
    // Get path to Video
    QString videoPath = ui->videoURLLineEdit->text();

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
