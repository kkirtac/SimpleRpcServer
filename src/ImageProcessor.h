/*
 * ImageProcessor.h
 *
 *  Created on: Nov 15, 2016
 *      Author: kadir
 */

#ifndef IMAGEPROCESSOR_H_
#define IMAGEPROCESSOR_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class ImageProcessor {
public:
	ImageProcessor();
	virtual ~ImageProcessor();

	void resizeImage(const Mat& src, int resizeHeight, int resizeWidth, Mat& dst);
	void convertGrayScale(const Mat& src, Mat& dst);

};

#endif /* IMAGEPROCESSOR_H_ */
