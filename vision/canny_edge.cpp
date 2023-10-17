#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat image;
std::string title = "Canny";

//Call back function
void on(int value, void* userdata)
{
  int th1 = cv::getTrackbarPos("canny low boundary", title);
  int th2 = cv::getTrackbarPos("canny high boundary", title);
  cv::Mat result;
  /*to store the result of the Canny edge detection.*/
  cv::Canny(image, result, th1, th2);
  /*
  This line is performing the Canny edge detection operation on the input image image and storing the result in the result matrix. The Canny edge detection is a popular image processing technique that identifies edges (areas of significant intensity change) in an image. The parameters th1 and th2 are the low and high threshold values for edge detection. Edges with intensities between th1 and th2 are considered potential edges.
  */
  cv::imshow(title, result);
}

int main()
{
  image = cv::imread("cat.jpg", cv::IMREAD_GRAYSCALE);
  /*
  IMREAD_GRAYSCALE: This flag indicates that the image should be read in grayscale mode. 
  */
  if(image.empty()){
    std::cerr << "Error: Unable to load image." << std::endl;
    return 1;
  }

  cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
  cv::imshow(title, image)
  cv::createTrackbar("canny low boundary", title, nullptr, 255, on);
  /*
  This line creates a trackbar in the GUI window with the title "Canny" (as specified by the title variable). This trackbar is labeled as "canny low boundary." It allows the user to interactively adjust a parameter related to the Canny edge detection algorithm.

  The nullptr argument is typically used for the callback function. If you want to associate a user-defined data pointer with the trackbar, you can pass it here. In your case, you're not using it, so it's set to nullptr.
  (User Data Pointer: The cv::createTrackbar function provides an option for you to pass a user data pointer (userdata) as its last argument. This pointer can be used to pass additional data to the callback function, but in your code, it's not being used.)

  The value 255 is the maximum value that the trackbar can have. In this context, it's used to set the upper boundary for the parameter you want to adjust. Users will be able to set the parameter to a value between 0 and 255 using the trackbar.

  The last argument on is the callback function that will be executed whenever the trackbar value is changed. In this case, the on function (defined earlier) will be called when the trackbar value changes. This function adjusts the Canny edge detection parameters and updates the displayed result.

  */
  cv::createTrackbar("canny hight boundary", title, nullptr, 255, on);
  cv::waitKey(0);
  return 0;
}