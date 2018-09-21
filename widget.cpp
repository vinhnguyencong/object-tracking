#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <QtCore>

using namespace std;
using namespace cv;

// Threshold value
static int threshold_value = 20;
static int numberofObject = 0;
static int objectNumber = 0;


//
// Kalman Filter
int stateSize = 6;
int measSize = 4;
int contrSize = 0;

//bounding rectangle of the object, we will use the center of this as its position.
Rect objectBoundingRectangle = Rect(0,0,0,0);

//we'll have just one object to search for
//and keep track of its position.
float theObject[2] = {0,0};

unsigned int type = CV_32F;
cv::KalmanFilter kf(stateSize, measSize, contrSize, type);

Mat state(stateSize, 1, type);  // [x,y,v_x,v_y,w,h]
Mat meas(measSize, 1, type);    // [z_x,z_y,z_w,z_h]l

//Mat procNoise(stateSize, 1, type);
// [E_x,E_y,E_v_x,E_v_y,E_w,E_h]

// Transition State Matrix A
// Note: set dT at each processing step!
// [ 1 0 dT 0  0 0 ]
// [ 0 1 0  dT 0 0 ]
// [ 0 0 1  0  0 0 ]
// [ 0 0 0  1  0 0 ]
// [ 0 0 0  0  1 0 ]
// [ 0 0 0  0  0 1 ]



//


// Convert int to string
std::string intToString(int number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    this->setWindowState(Qt::WindowMaximized);

    ui->thresholdHorizontalSlider->setRange(0,255);
    ui->thresholdHorizontalSlider->setSliderPosition(20);

    tmrTimer = new QTimer(this);


//    VideoCapture video;
//    video.open("/home/vinhnc/Downloads/sukhoi.mp4");
//    Mat frame;
//    video.read(frame);
//    video.open("/home/vinhnc/Videos/sukhoi.mp4");
//    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
//    tmrTimer->start(30);
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
    if(numberofObject == 0)
    {
        QMessageBox::about(this, "Warning", "No object detected");
    }
    else
    {
        objectNumber = 1;
    }
}

void Widget::on_trackingObj_2_PushButton_pressed()
{
    if(numberofObject < 2)
    {
        QMessageBox::about(this, "Warning", "Object 2 does not existed");
    }
    else
    {
        objectNumber = 2;
    }
}

void Widget::on_trackingObj_3_PushButton_pressed()
{
    if(numberofObject < 3)
    {
        QMessageBox::about(this, "Warning", "Object 3 does not existed");
    }
    else
    {
        objectNumber = 3;
    }
}

void Widget::on_trackingObj_4_PushButton_pressed()
{
    if(numberofObject < 4)
    {
        QMessageBox::about(this, "Warning", "Object 4 does not existed");
    }
    else
    {
        objectNumber = 4;
    }
}

void Widget::on_trackingObj_5_PushButton_pressed()
{
    if(numberofObject < 5)
    {
        QMessageBox::about(this, "Warning", "Object 5 does not existed");
    }
    else
    {
        objectNumber = 5;
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
        string stdstrVideoPath = videoPath.toUtf8().constData();
        video.open(stdstrVideoPath);
        connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
        tmrTimer->start(55);
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
    threshold_value = value;
}

void Widget::processFrameAndUpdateGUI()
{
    cv::setIdentity(kf.transitionMatrix);
    // Measure Matrix H
    // [ 1 0 0 0 0 0 ]
    // [ 0 1 0 0 0 0 ]
    // [ 0 0 0 0 1 0 ]
    // [ 0 0 0 0 0 1 ]
    kf.measurementMatrix = cv::Mat::zeros(measSize, stateSize, type);
    kf.measurementMatrix.at<float>(0) = 1.0f;
    kf.measurementMatrix.at<float>(7) = 1.0f;
    kf.measurementMatrix.at<float>(16) = 1.0f;
    kf.measurementMatrix.at<float>(23) = 1.0f;

    // Process Noise Covariance Matrix Q
    // [ Ex   0   0     0     0    0  ]
    // [ 0    Ey  0     0     0    0  ]
    // [ 0    0   Ev_x  0     0    0  ]
    // [ 0    0   0     Ev_y  0    0  ]
    // [ 0    0   0     0     Ew   0  ]
    // [ 0    0   0     0     0    Eh ]
    //cv::setIdentity(kf.processNoiseCov, cv::Scalar(1e-2));
    kf.processNoiseCov.at<float>(0) = 1e-2;
    kf.processNoiseCov.at<float>(7) = 1e-2;
    kf.processNoiseCov.at<float>(14) = 5.0f;
    kf.processNoiseCov.at<float>(21) = 5.0f;
    kf.processNoiseCov.at<float>(28) = 1e-2;
    kf.processNoiseCov.at<float>(35) = 1e-2;

    // Measures Noise Covariance Matrix R
    cv::setIdentity(kf.measurementNoiseCov, cv::Scalar(1e-1));
    // End Kalman Filter

    // Transition matrix ( eg. p(k) = p(k-1) + v(k-1)*dT ), init dT = 1
    double dT = 0.05;  // assume ~20fps

    video.read(rawFrame);

    if(rawFrame.empty() == true)
    {
        numberofObject = 0;
        objectNumber = 0;
        tmrTimer->stop();
        return;
    }

    rawFrame.copyTo(frame);
    cv::cvtColor(frame,grayFrame,COLOR_BGR2GRAY);
    Canny(grayFrame, grayFrame, 10, 150, 3);
    cv::threshold(grayFrame,thresholdFrame,threshold_value,255,THRESH_BINARY);

    cv::dilate(thresholdFrame, thresholdFrame, structuringElement5x5);
    //cv::dilate(thresholdFrame, thresholdFrame, structuringElement5x5);
    //cv::erode(thresholdFrame, thresholdFrame, structuringElement5x5);

    thresholdFrame.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;

    // Find boundary of onject
    findContours(temp,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );

    // Number of object detected
    numberofObject = contours.size();

    bool objectDetected;

    if(contours.size() > 0)
    {
        objectDetected = true;
    }
    else
    {
        objectDetected = false;
        putText(rawFrame, "No Object Detected", Point(200, 200),1,1,Scalar(255,0,0),2);
    }

    vector<Rect> objectBoundRect(contours.size());
    vector<vector<Point> > hull( contours.size() );

    if(objectDetected)
    {
        //kf.correct(meas);

//        for (size_t i = 0; i < contours.size(); i++)
//        {
//            // Find convex hull of contours
//            convexHull( Mat(contours[i]), hull[i], false );
//            objectBoundRect[i] = boundingRect(Mat(hull[i]));

//            if(objectNumber == 0)
//            {
//                rectangle(rawFrame, objectBoundRect[i].tl(), objectBoundRect[i].br(), CV_RGB(0,0,255), 2, 8, 0 );
//                putText(rawFrame, " Object " + intToString(i+1) , Point(objectBoundRect[i].br().x, objectBoundRect[i].br().y),1,1,Scalar(255,0,0),2);
//            }
//        }

        vector< vector<Point> > largestContourVec;
        largestContourVec.push_back(contours.at(contours.size()-1));
        //make a bounding rectangle around the largest contour then find its centroid
        //this will be the object's final estimated position.
        objectBoundingRectangle = boundingRect(largestContourVec.at(0));
        int xpos = objectBoundingRectangle.x + objectBoundingRectangle.width/2;
        int ypos = objectBoundingRectangle.y + objectBoundingRectangle.height/2;

        //update the objects positions by changing the 'theObject' array values
        theObject[0] = xpos , theObject[1] = ypos;

        kf.transitionMatrix.at<float>(2) = dT;
        kf.transitionMatrix.at<float>(9) = dT;

        state = kf.predict();
        cv::Rect predRect;
        predRect.width = state.at<float>(4);
        predRect.height = state.at<float>(5);
        predRect.x = state.at<float>(0) - predRect.width / 2;
        predRect.y = state.at<float>(1) - predRect.height / 2;
        cv::rectangle(rawFrame, predRect, CV_RGB(255,0,0), 2);

    }

    meas.at<float>(0) = theObject[0];
    meas.at<float>(1) = theObject[1];
    meas.at<float>(2) = (float)objectBoundingRectangle.width;
    meas.at<float>(3) = (float)objectBoundingRectangle.height;

    // >>>> Initialization
    kf.errorCovPre.at<float>(0) = 1; // px
    kf.errorCovPre.at<float>(7) = 1; // px
    kf.errorCovPre.at<float>(14) = 1;
    kf.errorCovPre.at<float>(21) = 1;
    kf.errorCovPre.at<float>(28) = 1; // px
    kf.errorCovPre.at<float>(35) = 1; // px

    state.at<float>(0) = meas.at<float>(0);
    state.at<float>(1) = meas.at<float>(1);
    state.at<float>(2) = 0;
    state.at<float>(3) = 0;
    state.at<float>(4) = meas.at<float>(2);
    state.at<float>(5) = meas.at<float>(3);
    // <<<< Initialization

    kf.statePost = state;


    //draw some crosshairs around the object
   // circle(frame1,Point(state.at<float>(0), state.at<float>(1)), 40,Scalar(0,255,0),2);

    Rect etm;
    etm.width = state.at<float>(4);
    etm.height = state.at<float>(5);
    etm.x = state.at<float>(0) - etm.width / 2;
    etm.y = state.at<float>(1) - etm.height / 2;
    rectangle(rawFrame, etm, Scalar(0,255,0), 1, CV_AA, 0);

    //write the position of the object to the screen
    putText(rawFrame,"Tracking object at (" + intToString(state.at<float>(0))+","+intToString(state.at<float>(1))+")",Point(state.at<float>(0), state.at<float>(1)),1,1,Scalar(255,0,0),2);

    cv::cvtColor(rawFrame, rawFrame, CV_BGR2RGB);
    QImage imgdp((uchar*)rawFrame.data, rawFrame.cols, rawFrame.rows, rawFrame.step, QImage::Format_RGB888);
    ui->imgViewer->setPixmap(QPixmap::fromImage(imgdp));
}
