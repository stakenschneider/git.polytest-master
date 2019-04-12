#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>

#define SIGMA 0.8

using namespace cv;
using namespace std;

double gaussianFunc(int x, int y, double sigma) {
	return((1 / (2 * CV_PI*sigma*sigma))*exp(-(x*x + y * y) / (2 * sigma*sigma)));
}

float distance(int x, int y, int i, int j) {
	return float(sqrt(pow(x - i, 2) + pow(y - j, 2)));
}

double gaussian(float x, double sigma) {
	return exp(-(pow(x, 2)) / (2 * pow(sigma, 2))) / (2 * CV_PI * pow(sigma, 2));

}

void generateKernel(int size, Mat& kernel) {
	kernel = Mat(size, size, CV_32F);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			kernel.at<float>(i, j) = gaussianFunc(i - (size - 1) / 2, j - (size - 1) / 2, SIGMA);
		}
	}
}

uchar countGaussValue(int x, int y, Mat& img, Mat& kernel) {
	float acc = 0;
	for (int i = 0; i < kernel.rows; i++) {
		for (int j = 0; j < kernel.cols; j++) {
			if (((y - (kernel.cols - 1) / 2) + i) >= 0 && ((y - (kernel.cols - 1) / 2) + i) < img.rows && ((x - (kernel.cols - 1) / 2) + j) >= 0 && ((x - (kernel.cols - 1) / 2) + j) < img.cols) {

				acc += img.at<uchar>((y - (kernel.cols - 1) / 2) + i, (x - (kernel.cols - 1) / 2) + j)*kernel.at<float>(i, j);
			}
			else continue;
		}
	}
	return (uchar)acc;
}

Mat neighboursValues(int area, Mat& src, int x, int y) {
	Mat values = Mat::zeros(area*area, 1, CV_8U);
	for (int i = 0; i < area; i++) {
		for (int j = 0; j < area; j++) {
			values.at<uchar>(j + i, 0) = src.at<uchar>((x - (area - 1) / 2) + j, (y - (area - 1) / 2) + i);
		}
	}
	return values;
}

double normOfVector(Mat& vec1, Mat& vec2) {
	double norm = 0;
	for (int i = 0; i < vec1.rows; i++) {
		norm = norm + pow((vec1.at<uchar>(i, 0) - vec2.at<uchar>(i, 0)), 2);
	}
	norm = sqrt(norm);
	return norm;
}

void nonLocalMeans(Mat& source, Mat& filteredImage, int x, int y, int diameter, double sigmaI, int height, int width) {
	double iFiltered = 0;
	double wP = 0;
	int xNeighbor = 0;
	int yNeighbor = 0;
	int half = diameter / 2;

	for (int i = 0; i < diameter; i++) {
		for (int j = 0; j < diameter; j++) {
			xNeighbor = x - (i - half);
			yNeighbor = y - (j - half);
			if (xNeighbor < 0) xNeighbor = 0;
			if (yNeighbor < 0) yNeighbor = 0;
			while (xNeighbor >= height - half) xNeighbor--;
			while (yNeighbor >= width - half) yNeighbor--;
			if (x < half) x = half;
			if (y < half) y = half;
			if (x >= height - half) 
				x = height - half;
			if (y >= width - half) 
				y = width - half;
			Mat vector1 = neighboursValues(half, source, x, y);
			Mat vector2 = neighboursValues(half, source, xNeighbor, yNeighbor);
			double vecNorm = normOfVector(vector1, vector2);

			double gr = gaussian(vecNorm, sigmaI);
			double w = gr;
			iFiltered = iFiltered + source.at<uchar>(xNeighbor, yNeighbor) * w;
			wP = wP + w;
		}
	}
	iFiltered = iFiltered / wP;
	filteredImage.at<uchar>(x, y) = (uchar)iFiltered;
}

Mat myNLMeansFilter(Mat& source, int diameter, double sigmaI) {
	Mat resultImage = Mat::zeros(source.rows, source.cols, CV_8U);
	int width = source.cols;
	int height = source.rows;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			nonLocalMeans(source, resultImage, i, j, diameter, sigmaI, height, width);
		}
	}
	return resultImage;
}

void myGaussFilter(Mat& img, int kernelSize) {
	Mat gauss;
	generateKernel(kernelSize, gauss);
	Size imgSize = img.size();
	for (int i = 0; i < imgSize.height; i++) {
		for (int j = 0; j < imgSize.width; j++) {
			img.at<uchar>(i, j) = countGaussValue(j, i, img, gauss);
		}
	}
}

void myBilateralFilter(Mat source, Mat filteredImage, int x, int y, int diameter, double sigmaI, double sigmaS, int height, int width) {
	double iFiltered = 0;
	double wP = 0;
	int neighbor_x = 0;
	int neighbor_y = 0;
	int half = diameter / 2;

	for (int i = 0; i < diameter; i++) {
		for (int j = 0; j < diameter; j++) {
			neighbor_x = x - (i- half);
			neighbor_y = y - (j- half);
			if (neighbor_x < 0) neighbor_x = 0;
			if (neighbor_y < 0) neighbor_y = 0;
			while (neighbor_x >= height) neighbor_x--;
			while (neighbor_y >= width) neighbor_y--;
			double gi = gaussian(source.at<uchar>(neighbor_x, neighbor_y) - source.at<uchar>(x, y), sigmaI);
			double gs = gaussian(distance(x, y, neighbor_x, neighbor_y), sigmaS);
			double w = gi * gs;
			iFiltered = iFiltered + source.at<uchar>(neighbor_x, neighbor_y) * w;
			wP = wP + w;
		}
	}
	iFiltered = iFiltered / wP;
	filteredImage.at<double>(x, y) = iFiltered;


}

Mat myBilateralFilter(Mat source, int diameter, double sigmaI, double sigmaS) {
	Mat filteredImage = Mat::zeros(source.rows, source.cols, CV_64F);
	int width = source.cols;
	int height = source.rows;

	for (int i = 2; i < height - 2; i++) {
		for (int j = 2; j < width - 2; j++) {
			myBilateralFilter(source, filteredImage, i, j, diameter, sigmaI, sigmaS, height, width);
		}
	}
	return filteredImage;
}

int main()
{
	string imgName = "masha.jpg";
	Mat src;
	src = imread(imgName, IMREAD_GRAYSCALE);
	cout << "TYPE: " << typeToString(src.type());

	if (!src.data)
	{
		printf("No image data \n");
		return -1;
	}

	Mat gaussTest;
	Mat gaussTestOpenCV;
	Mat bilateralTest;
	Mat bilateralTestOpenCV;
	Mat NLMeansTest;
	Mat NLMeansTestOpenCV;

	src.copyTo(gaussTest);
	src.copyTo(bilateralTest);
	src.copyTo(NLMeansTest);

    myGaussFilter(gaussTest, 7);
    imwrite("GB_sigma_3.png", gaussTest);

    GaussianBlur(src, gaussTestOpenCV, Size(7, 7), 0.8);
    imwrite("GB_ocv_sigma_08.png", gaussTestOpenCV);


    Mat bilateralFilteredImage = myBilateralFilter(bilateralTest, 5, 50.0, 50.0);
    imwrite("b_5_50_50.png", bilateralFilteredImage);

	bilateralFilter(src, bilateralTestOpenCV_2, 9, 150.0, 150.0);
	imwrite("b_op_9_150_150.png", bilateralTestOpenCV_2);


	Mat NLMeansFilteredImage = myNLMeansFilter(src, 3, 15);
	imwrite("NLM_3_15.png", NLMeansFilteredImage);

	fastNlMeansDenoising(src, NLMeansTestOpenCV_2, 5, 21, 21);
	imwrite("NLM_op_5_21_21.png", NLMeansTestOpenCV_2);

	waitKey(0);
}


