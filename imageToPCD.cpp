#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char** argv ){  
  //if ( argc != 2 ){ printf("usage: ./imageToPCD <Image_Path> <Image_Path>\n"); return -1; }

  Mat imageLeft = imread( argv[1], 1 );
  Mat imageRight = imread( argv[2], 1 );
  
  if ( !imageLeft.data ) { printf("No left image data \n"); return -1; }
  if ( !imageRight.data ) { printf("No right image data \n"); return -1; }

  namedWindow("Display Left Image", WINDOW_AUTOSIZE );
  imshow("Display Left Image", imageLeft);

  namedWindow("Display Right Image", WINDOW_AUTOSIZE );
  imshow("Display Right Image", imageRight);
  
  waitKey(0);
  return 0;}
