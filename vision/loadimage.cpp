#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
  Mat image = imread("sample.png", IMREAD_COLOR);
  imshow("Load Image", image); /* "Load image" 창에 이미지 표시*/
  waitKey(0); /*사용자의 키 입력을 대기한다. */
  return 0;
}