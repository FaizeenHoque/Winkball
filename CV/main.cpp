#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xobjdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>

cv::CascadeClassifier faceCascade;
cv::CascadeClassifier eyeCascade;

void detectAndDisplay(cv::Mat& frame);

int main() {
    // Load Cascade
    if (!faceCascade.load("./haarcascade_frontalface_default.xml")) {
        std::cerr << "Error: Could not load face cascade." << std::endl;
        return -1;
    }
    if (!eyeCascade.load("./haarcascade_eye.xml")) {
        std::cerr << "Error: Could not load eye cascade." << std::endl;
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

void detectAndDisplay(cv::Mat& frame) {
    cv::Mat frame_gray;
    cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);

    // Detect face;
    std::vector<cv::Rect> face;
    faceCascade.detectMultiScale(frame_gray, face);

    for (size_t i = 0; i < face.size(); i++)
    {
        cv::Point center(face[i].x + face[i].width / 2, face[i].y + face[i].height / 2);
        cv::ellipse(frame, center, cv::Size(face[i].width / 2, face[i].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 4);

        cv::Mat faceROI = frame_gray(face[i]);

        std::vector<cv::Rect> eyes;
        eyeCascade.detectMultiScale(faceROI, eyes);

        for (size_t j = 0; j < eyes.size(); j++)
        {
            cv::Point eye_center(face[i].x + eyes[j].x + eyes[j].width / 2, face[i].y + eyes[j].y + eyes[j].height / 2);
            int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
            cv::circle(frame, eye_center, radius, cv::Scalar(255, 0, 0), 4);
        }
    }
    
    cv::imshow("Detected Faces", frame);
}   