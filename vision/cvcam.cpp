#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <iostream>
int main(int argc, const char** argv)
{
    cv::VideoCapture video (0);
    /* This line initializes a VideoCapture object named video to capture video from a camera. The argument 0 specifies the camera device index. In this case, 0 typically represents the default camera (e.g., the built-in webcam).*/
    if (!video.isOpened())
    {
        std::cout << "Unable to get video from the camera!" << std::endl;
        return -1;
    }
    cv::Mat frame;
    /*frame that will be used to store individual frames captured from the camera. The captured video frames will be stored in this matrix.*/
    while (video.read(frame))
    /*captures video frames and stores them in the frame matrix*/
    {
        cv::imshow("Video feed", frame);
        if (cv::waitKey(25) >= 0)
            break;
    }
    cv::destroyAllWindows();
    /*used to close all OpenCV windows created during the program's execution.*/
    video.release();
    /*This line releases the camera resource held by the video object.*/
    return 0;
}
