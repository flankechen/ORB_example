// orb_example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ORBextractor.h"
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int nFeatures = 2000;
	float fScaleFactor = 1.2;
	int nLevels = 8;
	int fIniThFAST = 20;
	int fMinThFAST = 7;

	ORB_SLAM2::ORBextractor* mpORBextractor;
	mpORBextractor = new ORB_SLAM2::ORBextractor(nFeatures, fScaleFactor, nLevels, fIniThFAST, fMinThFAST);

	Mat src_gray = imread("src.jpg",0);
	resize(src_gray, src_gray, cv::Size(src_gray.size().width / 2, src_gray.size().height / 2));
	imshow("src", src_gray);
	waitKey();

	Mat mDescriptors;
 	std::vector<cv::KeyPoint> mvKeys;

	double tic = (double)cvGetTickCount();

	(*mpORBextractor)(src_gray, cv::Mat(), mvKeys, mDescriptors);

	double toc = (double)cvGetTickCount();
	double detectionTime = (toc - tic) / ((double)cvGetTickFrequency() * 1000);
	cout << "orb extractor in : " << detectionTime << endl;

	cout << "key count:" << mvKeys.size() << endl;

	for (int i = 0; i < mvKeys.size(); i++)
	{
		cv::Point2f pt1;
		pt1.x = mvKeys[i].pt.x;
		pt1.y = mvKeys[i].pt.y;

		circle(src_gray, pt1, 3, Scalar(255, 0, 0));
	}

	imshow("key_points", src_gray);
	waitKey();

	return 0;
}

