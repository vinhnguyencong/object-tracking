#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <qstring.h>

// Convert int to string
std::string intToString(int number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}
