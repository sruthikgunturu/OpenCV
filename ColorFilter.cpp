#include "ColorFilter.h"

using namespace std;
using namespace cv;

void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
    showResult();
}

void ColorFilter::split() {
    cv::split(_frame, _chans);
}

void ColorFilter::showResult() {
    //Problem 1
    //cv::imshow("result", _frame);
   //Problem 2: B
   //cv::imshow("BlueChannel", _chans[0]);
   //Problem 2: G
   //cv:imshow("GreenChannel", _chans[1]);
   //Problem 2: R
   //cv:imshow("RedChannel", _chans[2]);
    //Problem 3: Blue Subtraction
    cv:imshow("BlueSubtract", bMinusR);
    //Problem 3: Blue Threshold
    cv:imshow("BThresholh", thresh);
    //Problem 3: Blue Mask
    cv:imshow("BMask", contourmask);
    //Problem 3: Blue Cup
    cv:imshow("BlueCup:, blueCupImg);
    

}

void ColorFilter::findBlue() {
    cv::subtract(_chans[0], _chans[2], bMinusR);
    cv::threshold(bMinusR, thresh, 50, 255, cv::THRESH_BINARY);
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
    int maxSizeContour = 0;
    int maxContourSize = 0;
    for(int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if(contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    cv::Mat contourimage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    drawContours(contourimage, contours, maxSizeContour, cv::Scalar(255,255,255),
                 cv::LineTypes::FILLED, 8, hierarchy );
    contourmask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours( contourmask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);
    _frame.copyTo(blueCupImg, contourmask);
    
}

void ColorFilter::findGreen() {
}

void ColorFilter::findRed() {
        //FIX THIS
    cv::subtract(_chans[0], _chans[2], rMinusB);
    cv::threshold(rMinusB, threshR, 50, 255, cv::THRESH_BINARY);
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(threshR, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
    int maxSizeContour = 0;
    int maxContourSize = 0;
    for(int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if(contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    cv::Mat contourimage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    drawContours(contourimage, contours, maxSizeContour, cv::Scalar(255,255,255),
                 cv::LineTypes::FILLED, 8, hierarchy );
    contourmaskR = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours( contourmaskR, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);
    _frame.copyTo(RedCupImg, contourmaskR);
}

void ColorFilter::findBGR() {}
