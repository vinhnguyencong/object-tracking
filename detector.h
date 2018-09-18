#ifndef DETECTOR_H
#define DETECTOR_H

#include <QString>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

cv::Mat detect(QString videoPath);

#endif // DETECTOR_H
