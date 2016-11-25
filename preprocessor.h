#pragma once
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "imageOpen.h"
using namespace std;

void increaseBrightness(bmpBITMAP_FILE &image, int brightness);
void decreaseBrightness(bmpBITMAP_FILE &image, int brightness);

void increaseContrast(bmpBITMAP_FILE &image, double contrast);
void decreaseContrast(bmpBITMAP_FILE &image, double contrast);

void medianSmooth(bmpBITMAP_FILE &image);

void histogramEqualization(bmpBITMAP_FILE &image);

void thinningAlg(bmpBITMAP_FILE &image);

