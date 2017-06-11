#include "stdafx.h"

cv::Mat disparity, disparity8;
cv::Rect roi1, roi2;
cv::Mat img1 = cv::imread("./im0.png", 0);
cv::Mat img2 = cv::imread("./im1.png", 0);
cv::Mat img = cv::imread("./im0.png", 1);

const char *windowDisparity = "MatchingBM";

//Stereo parameters
int numberOfDisparities = 0;  //positive integer divisible by 16
int PreFilterCap = 0;
int BlockSize = 0;
int MinDisparity = 0;
int TextureThreshold = 0;
int UniquenessRatio = 0;
int SpeckleWindowSize = 0;
int SpeckleRange = 0;
int Disp12MaxDiff = 0;

void trackbar(int, void*)
{
	cv::Ptr<cv::StereoBM> bm = cv::StereoBM::create(16, 9);
	int disparities = 16 + numberOfDisparities * 16;
	int SADWindowSize = (BlockSize * 2) + 5;
	int MinDis = -128 + MinDisparity;
	//int SADWindowSize = getTrackbarPos("SADWindowSize", windowDisparity);
	bm->setROI1(roi1);
	bm->setROI2(roi2);
	bm->setPreFilterCap(31);
	bm->setBlockSize(SADWindowSize);
	bm->setMinDisparity(MinDis);
	bm->setNumDisparities(disparities);
	bm->setTextureThreshold(TextureThreshold);
	bm->setUniquenessRatio(15);
	bm->setSpeckleWindowSize(100);
	bm->setSpeckleRange(32);
	bm->setDisp12MaxDiff(1);
	//-- 3. Calculate the disparity image
	bm->compute(img1, img2, disparity);

	//-- Check its extreme values
	double minVal; double maxVal;

	cv::minMaxLoc(disparity, &minVal, &maxVal);


	//-- 4. Display it as a CV_8UC1 image
	disparity.convertTo(disparity8, CV_8UC1, 255 / (maxVal - minVal));
	cv::imshow(windowDisparity, disparity8);
}
int main()
{
	cv::namedWindow(windowDisparity, 1);

	cv::createTrackbar("Disparities", windowDisparity, &numberOfDisparities, img1.size().height / 16 - 16, trackbar);
	cv::createTrackbar("SADWindowSize", windowDisparity, &BlockSize, 10, trackbar);
	cv::createTrackbar("TextureThreshold", windowDisparity, &TextureThreshold, 100, trackbar);
	cv::createTrackbar("MinDisparity", windowDisparity, &MinDisparity, 256, trackbar);
	cv::waitKey(0);
	return 0;
}