#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xobjdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>

cv::CascadeClassifier cascade;

void detectAndDisplay(cv::Mat& frame) {}   

int main() {
    // Load Cascade
    std::string cascade_name = cv::samples::findFile("haarcascade_frontalface_default.xml");
    if (!cascade.load(cascade_name)) {
        std::cout << "Error: Could not load cascade classifier." << std::endl;
        return -1;
    }

    // Load Camera
    cv::VideoCapture capture;
    capture.open(0);
    if (!capture.isOpened()) {
        std::cout << "Error: Could not open camera." << std::endl;
        return -1;
    }
    
    cv::Mat frame;
    while (capture.read(frame)) {
        if (frame.empty()) { std::cerr << "Error: Empty frame." << std::endl; break;}

        detectAndDisplay(frame);
        
        cv::imshow("Wink Ball Camera", frame);
        if (cv::waitKey(1) == 27) { break; }
    }

    return 0;
}