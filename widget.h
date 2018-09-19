#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    cv::Mat detector(QString videoPath);

private slots:
    void on_browseVideoPushButton_pressed();

    void on_playVideoPushButton_pressed();

    void on_trackingObj_1_PushButton_pressed();

    void on_trackingObj_2_PushButton_pressed();

    void on_trackingObj_3_PushButton_pressed();

    void on_trackingObj_4_PushButton_pressed();

    void on_trackingObj_5_PushButton_pressed();

    void on_thresholdHorizontalSlider_valueChanged(int value);


public slots:
    void processFrameAndUpdateGUI();

private:
    Ui::Widget *ui;

    VideoCapture video;
    Mat frame, grayFrame, testFrame, thresholdFrame, temp;
    Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    QImage imgdp;
    QTimer *tmrTimer;

//protected:
//    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_H
