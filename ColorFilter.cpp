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

}

void ColorFilter::findBlue() {
    cv::Mat bMinusR;
    cv::subtract(_chans[0], _chans[2], bMinusR);
    cv::Mat thresh;
    cv::threshold(bMinusR, thresh, 50, 255, cv::THRESH_BINARY);
    
}

void ColorFilter::findGreen() {}

void ColorFilter::findRed() {}

void ColorFilter::findBGR() {}
