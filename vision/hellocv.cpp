#include <opencv4/highgui/highgui.hpp>

using namespace cv;
/* This line declares that you're using the cv namespace, which is short for "OpenCV." It means you can access OpenCV functions and classes without explicitly specifying the namespace each time.*/

int main()
{
  Mat image(300, 400, CV_8UC1, Scalar(255)); 
  /* Here, you're creating an OpenCV Mat object called "image." A Mat is a multi-dimensional matrix that can represent images. The Mat constructor is used to create a 300x400 pixel image with a single channel (CV_8UC1) and initialize it with a white color (Scalar(255)).

  -300 and 400 are the dimensions of the image (height and width).
  -CV_8UC1 specifies that the image has 8-bit unsigned characters and one channel, representing grayscale.
  -Scalar(255) initializes all pixels in the image with a white color (255 is the maximum intensity for an 8-bit image, which is white).*/
  imshow("Hello World", image); 
  /*This line displays the image on the screen. The imshow function is used for this purpose. The first argument is a window name, which you've set to "Hello World," and the second argument is the image you want to display.*/
  waitKey(0); 
  /*The waitKey function is used to wait for user input. In this case, it waits until a key is pressed (the argument 0 indicates an indefinite wait). This allows you to keep the window open until you decide to close it. When a key is pressed, the function will return the key code.*/

  return 0;
}