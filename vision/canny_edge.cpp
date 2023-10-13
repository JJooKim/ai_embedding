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
  cv::Canny(image, result, th1, th2);
  cv::imshow(title, result);
}

int main()
{
  image = cv::imread("cat.jpg", cv::IMREAD_GRAYSCALE);
  if(image.empty()){
    std::cerr << "Error: Unable to load image." << std::endl;
    return 1;
  }

  cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
  cv::imshow(title, image)
  cv::createTrackbar("canny low boundary", title, nullptr, 255, on);
  cv::createTrackbar("canny hight boundary", title, nullptr, 255, on);
  cv::waitKey(0);
  return 0;
}