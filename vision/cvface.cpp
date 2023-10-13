#include <opencv2/opencv.hpp>
#include <iostream>
int main(int argc, const char** argv)
{
    cv::VideoCapture video (0);
    if (!video.isOpened())
    {
        std::cout << "Unable to get video from the camera!" << std::endl;
        return -1;
    }
    video.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading Haar Cascade Classifier model." << std::endl;
        return -1;
    }

    cv::Mat orig;
    cv::Mat gray;
    while (video.read(orig))
    {
        std::vector<cv::Rect> faces;
        cv::cvtColor(orig, gray, cv::COLOR_BGR2GRAY);
        faceCascade.detectMultiScale(gray, faces, 1.02, 3);
        for (const cv::Rect& f : faces)
            cv::rectangle(orig, f, cv::Scalar(0, 255, 0), 2);
        cv::imshow("image", orig);
        if (cv::waitKey(25) >= 0)
            break;
    }
    cv::destroyAllWindows();
    video.release();
    return 0;
}
