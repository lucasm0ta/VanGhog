#ifndef IMAGEPROC_H
#define IMAGEPROC_H

#include <math.h>
#include <vector>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

const int THRESHOLD = 90;

class ImageProc
{
public:
    ImageProc();
};
double imgProc(Vec3b color,const cv::Mat& img);
#endif // IMAGEPROC_H
