#include "ColorFilter.h"

using namespace std;
using namespace cv;

void ColorFilter::processImage(cv::Mat img)
{
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
    showResult();
}

void ColorFilter::split()
{
    cv::split(_frame, _chans);
}

void ColorFilter::showResult()
{
    // Problem 1
     cv::imshow("result", _frame);
    // Problem 2: B
    // cv::imshow("BlueChannel", _chans[0]);
    // Problem 2: G
    // cv::imshow("GreenChannel", _chans[1]);
    // Problem 2: R
    // cv::imshow("RedChannel", _chans[2]);
    // Problem 3: Blue Subtraction
    // cv::imshow("BlueSubtract", bMinusR);
    // Problem 3: Blue Threshold
    // cv::imshow("BThreshold", thresh);
    // Problem 3: Blue Mask
    // cv::imshow("BMask", contourmask);
    // Problem 3: Blue Cup
    //cv::imshow("BlueCup:", blueCupImg);
    // Problem 4: Green Subtraction
    // cv::imshow("GreenSubtract", gMinus);
    // Problem 4: Green Threshold
    // cv::imshow("GThreshold", threshG);
    // Problem 4: Green Mask
    // cv::imshow("GMask", contourmaskG);
    // Problem 4: Green Cup
    // cv::imshow("GreenCup:", GreenCupImg);
    // Problem 5: Red Subtraction
    // cv::imshow("RedSubtract", rMinus);
    // Problem 5: Red Threshold
    // cv::imshow("RThreshold", threshR);
    // Problem 5: Red Mask
    // cv::imshow("RMask", contourmaskR);
    // Problem 5: Red Cup
     cv::imshow("RedCup:", RedCupImg);
}

void ColorFilter::findBlue()
{
    subtract(_chans[0], _chans[2], bMinusR);
    threshold(bMinusR, thresh, 50, 255, cv::THRESH_BINARY);
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for (int i = 0; i < contours.size(); i++)
    {
        int contourSize = cv::contourArea(contours[i]);
        if (contourSize > maxContourSize)
        {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }

    blueCupImg = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    contourmask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(contourmask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);
    _frame.copyTo(blueCupImg, contourmask);
}

void ColorFilter::findGreen() {
    subtract(_chans[1], _chans[0], gMinus);
    threshold(gMinus, threshG, 50, 255, cv::THRESH_BINARY);
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(threshG, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for (int i = 0; i < contours.size(); i++)
    {
        int contourSize = cv::contourArea(contours[i]);
        if (contourSize > maxContourSize)
        {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    GreenCupImg = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    contourmaskG = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(contourmaskG, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);
    _frame.copyTo(GreenCupImg, contourmaskG);
}

void ColorFilter::findRed() {
    subtract(_chans[2], _chans[1], rMinus);
    threshold(rMinus, threshR, 50, 255, cv::THRESH_BINARY);
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(threshR, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for (int i = 0; i < contours.size(); i++)
    {
        int contourSize = cv::contourArea(contours[i]);
        if (contourSize > maxContourSize)
        {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }

    RedCupImg = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    contourmaskR = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(contourmaskR, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);
    _frame.copyTo(RedCupImg, contourmaskR);
}

void ColorFilter::findBGR() {
    
}
