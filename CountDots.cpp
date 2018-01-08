#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	Mat InputImg = imread( "dice6.png"); // Read Input Image
	
	SimpleBlobDetector::Params parameter; // SimpleBlobDetector parameter setup

	// Area filtering to avoid small circles other than dice dots
	parameter.filterByArea = true;
	parameter.minArea = 100;

	// Circularity filtering
	parameter.filterByCircularity = true;
	parameter.minCircularity = 0.7;

	vector<KeyPoint> keypoints; // To store circle blobs 

	// Set up detector with parameters
	Ptr<SimpleBlobDetector>detector = SimpleBlobDetector::create(parameter);   
	detector->detect(InputImg, keypoints); // Detect blobs

	// Draw detected Circles as Green circles and use putText to
	// display the total number of dots in the image
	Mat Img_with_Circles;
	drawKeypoints(InputImg, keypoints, Img_with_Circles, Scalar(0,255,0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

	int Size = keypoints.size(); // total number of keypoints detected
	char Text[20];
	sprintf(Text,"Sum: %d",Size); // text to display on the image

	putText(Img_with_Circles, Text, cvPoint(50,50),FONT_HERSHEY_SIMPLEX, 1, cvScalar(0,255,0), 2, CV_AA);

	// Save and display the output
	imwrite("Output6.png", Img_with_Circles);
	imshow("Output Image",Img_with_Circles);
	waitKey(0);

}

//  Compile
//  g++ -std=c++11 CountDots.cpp `pkg-config --libs --cflags opencv` -o CountDiceDots

//  Run
//  ./CountDiceDots
