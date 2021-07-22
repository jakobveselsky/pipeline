#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/ximgproc.hpp"
using namespace cv;
using namespace cv::ximgproc;

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

  Mat left_disp,right_disp;
  double matching_time, filtering_time;
  Ptr<DisparityWLSFilter> wls_filter;
  Mat filtered_disp,solved_disp,solved_filtered_disp;
 
  Ptr<StereoSGBM> left_matcher = StereoSGBM::create(160,255);
  wls_filter = createDisparityWLSFilter(left_matcher);
  Ptr<StereoMatcher> right_matcher = createRightMatcher(left_matcher);
  double lambda = 8000.0;
  double sigma  = 1.5;
  double vis_mult = 1.0;
            
  cvtColor(imageLeft,  imageLeft,  COLOR_BGR2GRAY);
  cvtColor(imageRight, imageRight, COLOR_BGR2GRAY);
            
  matching_time = (double)getTickCount();
  left_matcher-> compute(imageLeft, imageRight, left_disp);
  right_matcher-> compute(imageRight, imageLeft, right_disp);
  matching_time = ((double)getTickCount() - matching_time)/getTickFrequency();

  wls_filter->setLambda(lambda);
  wls_filter->setSigmaColor(sigma);
  filtering_time = (double)getTickCount();
  wls_filter->filter(left_disp,imageLeft,filtered_disp,right_disp);
  filtering_time = ((double)getTickCount() - filtering_time)/getTickFrequency();

  Mat raw_disp_vis;
  getDisparityVis(left_disp,raw_disp_vis,vis_mult);
  namedWindow("raw disparity", WINDOW_AUTOSIZE);
  imshow("raw disparity", raw_disp_vis);
  Mat filtered_disp_vis;
  getDisparityVis(filtered_disp,filtered_disp_vis,vis_mult);
  namedWindow("filtered disparity", WINDOW_AUTOSIZE); 
  imshow("filtered disparity", filtered_disp_vis);

  Mat XYZ(filtered_disp.size(),CV_32FC3);
  //reprojectImageTo3D(filtered_disp, XYZ, Q, false);

  waitKey(0);
  return 0;}
