#pragma once
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "imageOpen.h"
using namespace std;

void increaseBrightness(bmpBITMAP_FILE &image, int brightness);
void decreaseBrightness(bmpBITMAP_FILE &image, int brightness);

void increaseContrast(bmpBITMAP_FILE &image, double contrast);
void decreaseContrast(bmpBITMAP_FILE &image, double contrast);

void insertionSort(int window[]);
void medianSmooth(bmpBITMAP_FILE &image);

void histogramEqualization(bmpBITMAP_FILE &image);

//www.programming-techniques.com/2013/03/sobel-and-prewitt-edge-detector-in-c.html
void sobelEdgeDetection(bmpBITMAP_FILE &image);

//convert to black and white
void grayToBlackWhite(bmpBITMAP_FILE &image);
void grayToBinary(bmpBITMAP_FILE &image);
void binaryToGray(bmpBITMAP_FILE &image);

//these dont work yet
void thinningAlg(bmpBITMAP_FILE &image);
void thinning(bmpBITMAP_FILE &image);
void doZhangSuenThinning(bmpBITMAP_FILE &image);

class Point 
{
private:
	int x;
	int y;
public:
	Point::Point();
	Point(int xx, int yy);
	int getX();
	void setX(int xx);
	int getY();
	void setY(int yy);
};

