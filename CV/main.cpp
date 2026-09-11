#include <opencv5/opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) { std::cerr << "Error: Could not open camera." << std::endl; return -1;}

    std::cout << "Camera opened successfully!" << std::endl;
    cv::Mat frame;

    while (true) {
        cap >> frame;
        if (frame.empty()) { std::cerr << "Error: Empty frame." << std::endl; break;}
        
        cv::imshow("Wink Ball Camera", frame);
        if (cv::waitKey(1) == 27) { break; }
    }

    return 0;
}