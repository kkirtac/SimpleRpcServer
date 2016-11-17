/*
 * ImageProcessor.cpp
 *
 *  Created on: Nov 15, 2016
 *      Author: kadir
 */

#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {
	// TODO Auto-generated constructor stub

}

ImageProcessor::~ImageProcessor() {
	// TODO Auto-generated destructor stub
}

void ImageProcessor::resizeImage(const Mat& src, int resizeHeight, int resizeWidth, Mat& dst){

	resize(src, dst, Size(resizeWidth, resizeHeight));

}

void ImageProcessor::convertGrayScale(const Mat& src, Mat& dst){

	cvtColor(src, dst, CV_BGR2GRAY);

}

