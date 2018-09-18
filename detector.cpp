#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <QString>
#include <QDebug>

using namespace std;
using namespace cv;

// Convert int to string
std::string intToString(int number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}

// Sensitivity value and the Number of objects detected
extern int *threshold_value;
extern int *obj_number;

Mat detect(QString videoPath)
{
    //some boolean variables for added functionality
    //bool objectDetected = false;
    bool trackingEnabled = true;
    //pause and resume code
    bool pause = false;

    // Brief stdstrVideoPath
    string stdstrVideoPath = videoPath.toUtf8().constData();

    // Capture video
    VideoCapture video(stdstrVideoPath);
//    namedWindow( "Display window", WINDOW_AUTOSIZE );

    Mat rawFrame, grayFrame, thresholdFrame;

    for(;;)
    {
        while(video.get(CAP_PROP_POS_FRAMES) < video.get(CAP_PROP_FRAME_COUNT)-1)
        {
            // Read video frame
            video.read(rawFrame);

            // Convert RGB frame to gray
            cv::cvtColor(rawFrame,grayFrame,COLOR_BGR2GRAY);

            // Find edge line of object
            Canny(grayFrame, grayFrame, 10, 150, 3);
            cv::threshold(grayFrame,thresholdFrame,*threshold_value,255,THRESH_BINARY);

            //blur the image to get rid of the noise. This will output an intensity image
            cv::blur(thresholdFrame,thresholdFrame,cv::Size(3,3));

            //threshold again to obtain binary image from blur output
            cv::threshold(thresholdFrame,thresholdFrame,*threshold_value,255,THRESH_BINARY);

            // Return rectangular structuring element with size 5x5
            cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));

            cv::dilate(thresholdFrame, thresholdFrame, structuringElement5x5);
            cv::dilate(thresholdFrame, thresholdFrame, structuringElement5x5);
            cv::erode(thresholdFrame, thresholdFrame, structuringElement5x5);

            if(trackingEnabled)
            {
                bool objectDetected = false;
                Mat temp;
                thresholdFrame.copyTo(temp);
                //these two vectors needed for output of findContours
                vector< vector<Point> > contours;
                vector<Vec4i> hierarchy;

                // Find boundary of onject
                findContours(temp,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );

                // Handle left mouse click
//                setMouseCallback("Display window", onMouse, 0);


                // Found object with the number of contours > 0
                *obj_number = contours.size();

                if(contours.size() > 0)
                {
                    objectDetected=true;
                }
                else
                {
                    objectDetected = false;
                    putText(rawFrame, "No Object Detected", Point(0, 0),1,1,Scalar(255,0,0),2);
                }

                vector<Rect> objectBoundRect(contours.size());
                vector<vector<Point> > hull( contours.size() );

                if(objectDetected)
                {
                    for (size_t i = 0; i < contours.size(); i++)
                    {
                        // Find convex hull of contours
                        convexHull( Mat(contours[i]), hull[i], false );
                        objectBoundRect[i] = boundingRect(Mat(hull[i]));
                        rectangle( rawFrame, objectBoundRect[i].tl(), objectBoundRect[i].br(), CV_RGB(0,0,255), 2, 8, 0 );
                    }

                }
            //show our captured frame
            //namedWindow( "Display window", WINDOW_AUTOSIZE );
//            imshow("Display window",rawFrame);

//            switch(waitKey(30))
//            {
//            // Pause or Resume by press Space
//            case 32:
//                pause = !pause;
//                if(pause == true)
//                {
//                    while (pause == true)
//                    {
//                        //stay in this loop until
//                        switch (waitKey(60))
//                        {
//                        case 32:
//                            // Resume
//                            pause = false;
//                            break;
//                        }
//                    }
//                }
//            }

            // Handle pause and resume -- End

        }

    }

    // Detele the video capture object
    video.release();

    // Close all windows frame
    destroyAllWindows();
    }
    cvtColor(rawFrame, rawFrame, CV_BGR2RGB);
    return rawFrame;
}
