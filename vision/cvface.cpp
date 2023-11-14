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
    //sets the frame width of the video capture to 640 pixels 
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading Haar Cascade Classifier model." << std::endl;
        return -1;
    }

    cv::Mat orig;                  // Create a variable 'orig' to store the original video frame.
    cv::Mat gray;                  // Create a variable 'gray' to store the grayscale version of the frame.

    while (video.read(orig)) {     // Loop as long as 'video' can read frames into 'orig'.

        std::vector<cv::Rect> faces;  // Create a vector to store detected faces as rectangles.

        // Convert the 'orig' frame to grayscale and store it in 'gray'.
        cv::cvtColor(orig, gray, cv::COLOR_BGR2GRAY);

        // Detect faces in the 'gray' frame using a pre-trained face detection classifier.
        // The detected faces will be stored in the 'faces' vector.
        faceCascade.detectMultiScale(gray, faces, 1.02, 3);

        // Iterate over the detected faces and draw green rectangles around them on the 'orig' frame.
        for (const cv::Rect& f : faces) {
            cv::rectangle(orig, f, cv::Scalar(0, 255, 0), 2);  // Draw a green rectangle.
        }

        // Display the 'orig' frame with detected faces in a window named "image."
        cv::imshow("image", orig);

        // Wait for a key press for 25 milliseconds. If a key is pressed, break out of the loop.
        if (cv::waitKey(25) >= 0) {
            break;
        }
    }

    // End of the video capture and face detection loop.



    cv::destroyAllWindows();
    video.release();
    return 0;
}
