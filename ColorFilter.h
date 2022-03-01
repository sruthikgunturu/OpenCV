#ifndef COLOR_FILTER_H
#define COLOR_FILTER_H

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

class ColorFilter
{
protected:
    cv::Mat _frame;
    std::vector<cv::Mat> _chans;

    cv::Mat bMinusR;
    cv::Mat thresh;
    cv::Mat contourmask;
    cv::Mat blueCupImg;

    cv::Mat rMinus;
    cv::Mat threshR;
    cv::Mat contourmaskR;
    cv::Mat RedCupImg;

    cv::Mat gMinus;
    cv::Mat threshG;
    cv::Mat contourmaskG;
    cv::Mat GreenCupImg;

public:
    void processImage(cv::Mat img);

    void split();

    void findBlue();
    void findGreen();
    void findRed();
    void findBGR();

    void showResult();
};

#endif
