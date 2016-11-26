#include "preprocessor.h"

//////////////////////////////////////////
Point::Point()
{}
Point::Point(int xx, int yy)
{x = xx; y = yy;}
int Point::getX()
{return x;}
void Point::setX(int xx)
{x = xx;}
int Point::getY()
{return y;}
void Point::setY(int yy)
{y = yy;}
///////////////////////////////////////////

void increaseBrightness(bmpBITMAP_FILE &image, int brightness)
{
	int width;
	int height;

	height = Assemble_Integer(image.infoheader.biHeight);
	width = Assemble_Integer(image.infoheader.biWidth);

	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (image.image_ptr[i][j] + brightness > 255)
			{
				image.image_ptr[i][j] = image.image_ptr[i][j] + (255 - image.image_ptr[i][j]);
			}
			else
			{
				image.image_ptr[i][j] = image.image_ptr[i][j] + brightness;
			}
		}
	}
}

void decreaseBrightness(bmpBITMAP_FILE &image, int brightness)
{
	int width;
	int height;

	height = Assemble_Integer(image.infoheader.biHeight);
	width = Assemble_Integer(image.infoheader.biWidth);

	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (image.image_ptr[i][j] - brightness < 0)
			{
				image.image_ptr[i][j] = image.image_ptr[i][j] - image.image_ptr[i][j];
			}
			else
			{
				image.image_ptr[i][j] = image.image_ptr[i][j] - brightness;
			}
		}
	}
}

//contrast > 1
void increaseContrast(bmpBITMAP_FILE &image, double contrast)
{
	int width;
	int height;

	height = Assemble_Integer(image.infoheader.biHeight);
	width = Assemble_Integer(image.infoheader.biWidth);

	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (127 + (contrast * (image.image_ptr[i][j] - 127)) > 255)
			{
				image.image_ptr[i][j] = 255;
			}
			else if(127 + (contrast * (image.image_ptr[i][j] - 127)) < 0)
			{
				image.image_ptr[i][j] = 0;
			}
			else
			{
				image.image_ptr[i][j] = 127 + (contrast * (image.image_ptr[i][j] - 127));
			}
			
		}
	}
}

//contrast < 1
void decreaseContrast(bmpBITMAP_FILE &image, double contrast)
{
	int width;
	int height;

	height = Assemble_Integer(image.infoheader.biHeight);
	width = Assemble_Integer(image.infoheader.biWidth);

	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (127 + (contrast * (image.image_ptr[i][j] - 127)) > 255)
			{
				image.image_ptr[i][j] = 255;
			}
			else if (127 + (contrast * (image.image_ptr[i][j] - 127)) < 0)
			{
				image.image_ptr[i][j] = 0;
			}
			else
			{
				image.image_ptr[i][j] = 127 + (contrast * (image.image_ptr[i][j] - 127));
			}
			
		}
	}
}

void insertionSort(int window[])
{
	int temp, i, j;
	for (i = 0; i < 9; i++) {
		temp = window[i];
		for (j = i - 1; j >= 0 && temp < window[j]; j--) {
			window[j + 1] = window[j];
		}
		window[j + 1] = temp;
	}
}

void medianSmooth(bmpBITMAP_FILE &image)
{
	bmpBITMAP_FILE imageCopy;

	int width;
	int height;

	height = Assemble_Integer(image.infoheader.biHeight);
	width = Assemble_Integer(image.infoheader.biWidth);
	
	//create a sliding window of size 9
	int window[9];

	Copy_Image(image, imageCopy);

	for (int i = 1; i < height-1; i++)
	{
		for (int j = 1; j < width-1; j++)
		{
			// Pick up window elements
			window[0] = image.image_ptr[i - 1][j - 1];
			window[1] = image.image_ptr[i][j - 1];
			window[2] = image.image_ptr[i + 1][j - 1];
			window[3] = image.image_ptr[i - 1][j];
			window[4] = image.image_ptr[i][j];
			window[5] = image.image_ptr[i + 1][j];
			window[6] = image.image_ptr[i - 1][j + 1];
			window[7] = image.image_ptr[i][j + 1];
			window[8] = image.image_ptr[i + 1][j + 1];

			// sort the window to find median
			insertionSort(window);

			// assign the median to centered element of the matrix
			imageCopy.image_ptr[i][j] = window[4];
		}
	}
	Copy_Image(imageCopy, image);
}

void histogramEqualization(bmpBITMAP_FILE &image)
{
	int width;
	int height;

	height = Assemble_Integer(image.infoheader.biHeight);
	width = Assemble_Integer(image.infoheader.biWidth);

	int hist[256];

	//initialize histogram
	for (int i = 0; i < 256; i++)
	{
		hist[i] = 0;
	}

	//compute the histogram
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			hist[image.image_ptr[i][j]] += 1;
		}
	}

	//compute the cummulative histogram
	for (int i = 1; i < 256; i++)
	{
		hist[i] = hist[i - 1] + hist[i];
	}

	//normalize the cummulative histogram
	for (int i = 0; i < 256; i++)
	{
		hist[i] = hist[i] * 255 / (height * width);
	}

	//write the equalized values into the image
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			image.image_ptr[i][j] = hist[image.image_ptr[i][j]];
		}
	}
}

// Computes the x component of the gradient vector
// at a given point in a image.
// returns gradient in the x direction
int xGradient(bmpBITMAP_FILE &image, int x, int y)
{
	return image.image_ptr[y - 1][x - 1] +
		2 * image.image_ptr[y][x - 1] +
		image.image_ptr[y + 1][x - 1] -
		image.image_ptr[y - 1][x + 1] -
		2 * image.image_ptr[y][x + 1] -
		image.image_ptr[y + 1][x + 1];
}

// Computes the y component of the gradient vector
// at a given point in a image
// returns gradient in the y direction

int yGradient(bmpBITMAP_FILE &image, int x, int y)
{
	return image.image_ptr[y - 1][x - 1] +
		2 * image.image_ptr[y - 1][x] +
		image.image_ptr[y - 1][x + 1] -
		image.image_ptr[y + 1][x - 1] -
		2 * image.image_ptr[y + 1][x] -
		image.image_ptr[y + 1][x + 1];
}

//uses the aove two functions as helper functions
void sobelEdgeDetection(bmpBITMAP_FILE &image)
{
	bmpBITMAP_FILE imageCopy;
	Copy_Image(image, imageCopy);

	int width;
	int height;
	int gx, gy, sum;

	height = Assemble_Integer(image.infoheader.biHeight);
	width = Assemble_Integer(image.infoheader.biWidth);

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			imageCopy.image_ptr[y][x] = 0;

	for (int y = 1; y < height - 1; y++) 
	{
		for (int x = 1; x < width - 1; x++) 
		{
			gx = xGradient(image, x, y);
			gy = yGradient(image, x, y);
			sum = abs(gx) + abs(gy);
			sum = sum > 255 ? 255 : sum;
			sum = sum < 0 ? 0 : sum;
			imageCopy.image_ptr[y][x] = sum;
		}
	}
	Copy_Image(imageCopy, image);
}

void grayToBlackWhite(bmpBITMAP_FILE &image)
{
	int width;
	int height;

	height = Assemble_Integer(image.infoheader.biHeight);
	width = Assemble_Integer(image.infoheader.biWidth);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (image.image_ptr[i][j] > 127) //change threshold for dif conversions
			{
				image.image_ptr[i][j] = 255;
			}
			else
			{
				image.image_ptr[i][j] = 0;
			}
		}
	}
}

//backwards gray to binary converter for thinning algorithm
void grayToBinary(bmpBITMAP_FILE &image)
{
	int width;
	int height;

	height = Assemble_Integer(image.infoheader.biHeight);
	width = Assemble_Integer(image.infoheader.biWidth);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (image.image_ptr[i][j] == 0) //change threshold for dif conversions
			{
				image.image_ptr[i][j] = 1;
			}
			else
			{
				image.image_ptr[i][j] = 0;
			}
		}
	}
}

//backwards gray to binary converter for thinning algorithm
void binaryToGray(bmpBITMAP_FILE &image)
{
	int width;
	int height;

	height = Assemble_Integer(image.infoheader.biHeight);
	width = Assemble_Integer(image.infoheader.biWidth);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (image.image_ptr[i][j] == 1) //change threshold for dif conversions
			{
				image.image_ptr[i][j] = 0;
			}
			else
			{
				image.image_ptr[i][j] = 255;
			}
		}
	}
}

//everything below here doesnt work yet
//placeholder code, doesnt do shit yet
void thinningAlg(bmpBITMAP_FILE &image)
{
	bmpBITMAP_FILE imageCopy;
	Copy_Image(image, imageCopy);

	int width;
	int height;

	height = Assemble_Integer(image.infoheader.biHeight);
	width = Assemble_Integer(image.infoheader.biWidth);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			image.image_ptr[i][j] = 1;
		}
	}
	Copy_Image(imageCopy, image);
}

	/**
	* @param givenImage
	* @param changeGivenImage decides whether the givenArray should be modified or a clone should be used
	* @return a 2D array of binary image after thinning using zhang-suen thinning algo.
	*/
int getA(bmpBITMAP_FILE binaryImage, int y, int x)
{
	int width;
	int height;

	height = Assemble_Integer(binaryImage.infoheader.biHeight);
	width = Assemble_Integer(binaryImage.infoheader.biWidth);

	int count = 0;
	//p2 p3
	if (y - 1 >= 0 && x + 1 < width && binaryImage.image_ptr[y - 1][x] == 0 && binaryImage.image_ptr[y - 1][x + 1] == 1)
	{
		count++;
	}
	//p3 p4
	if (y - 1 >= 0 && x + 1 < width && binaryImage.image_ptr[y - 1][x + 1] == 0 && binaryImage.image_ptr[y][x + 1] == 1)
	{
		count++;
	}
	//p4 p5
	if (y + 1 < height && x + 1 < width && binaryImage.image_ptr[y][x + 1] == 0 && binaryImage.image_ptr[y + 1][x + 1] == 1)
	{
		count++;
	}
	//p5 p6
	if (y + 1 < height && x + 1 < width && binaryImage.image_ptr[y + 1][x + 1] == 0 && binaryImage.image_ptr[y + 1][x] == 1)
	{
		count++;
	}
	//p6 p7
	if (y + 1 < height && x - 1 >= 0 && binaryImage.image_ptr[y + 1][x] == 0 && binaryImage.image_ptr[y + 1][x - 1] == 1)
	{
		count++;
	}
	//p7 p8
	if (y + 1 < height && x - 1 >= 0 && binaryImage.image_ptr[y + 1][x - 1] == 0 && binaryImage.image_ptr[y][x - 1] == 1)
	{
		count++;
	}
	//p8 p9
	if (y - 1 >= 0 && x - 1 >= 0 && binaryImage.image_ptr[y][x - 1] == 0 && binaryImage.image_ptr[y - 1][x - 1] == 1)
	{
		count++;
	}
	//p9 p2
	if (y - 1 >= 0 && x - 1 >= 0 && binaryImage.image_ptr[y - 1][x - 1] == 0 && binaryImage.image_ptr[y - 1][x] == 1)
	{
		count++;
	}
	return count;
}

int getB(bmpBITMAP_FILE binaryImage, int y, int x)
{
	return binaryImage.image_ptr[y - 1][x] + binaryImage.image_ptr[y - 1][x + 1] + binaryImage.image_ptr[y][x + 1]
		+ binaryImage.image_ptr[y + 1][x + 1] + binaryImage.image_ptr[y + 1][x] + binaryImage.image_ptr[y + 1][x - 1]
		+ binaryImage.image_ptr[y][x - 1] + binaryImage.image_ptr[y - 1][x - 1];
}

void doZhangSuenThinning(bmpBITMAP_FILE &binaryImage)
{
	int width;
	int height;

	height = Assemble_Integer(binaryImage.infoheader.biHeight);
	width = Assemble_Integer(binaryImage.infoheader.biWidth);

	vector<Point> pointsToChange;
		int a, b;
		
		grayToBlackWhite(binaryImage);
		grayToBinary(binaryImage);

		//List<Point> pointsToChange = new LinkedList();
		bool hasChange;
		do {
			hasChange = false;
			for (int y = 1; y + 1 < height; y++) 
			{
				for (int x = 1; x + 1 < width; x++)
				{
					a = getA(binaryImage, y, x);
					b = getB(binaryImage, y, x);
					if (binaryImage.image_ptr[y][x] == 1 && 2 <= b && b <= 6 && a == 1
						&& (binaryImage.image_ptr[y - 1][x] * binaryImage.image_ptr[y][x + 1] * binaryImage.image_ptr[y + 1][x] == 0)
						&& (binaryImage.image_ptr[y][x + 1] * binaryImage.image_ptr[y + 1][x] * binaryImage.image_ptr[y][x - 1] == 0))
					{
						Point pt;
						pt.setX(x);
						pt.setY(y);
						pointsToChange.push_back(pt);
						//binaryImage[y][x] = 0;
						hasChange = true;
					}
				}
			}
			for (Point point : pointsToChange) 
			{
				binaryImage.image_ptr[point.getY()][point.getX()] = 0;
			}
			pointsToChange.clear();
			for (int y = 1; y + 1 < height; y++) 
			{
				for (int x = 1; x + 1 < width; x++) 
				{
					a = getA(binaryImage, y, x);
					b = getB(binaryImage, y, x);
					if (binaryImage.image_ptr[y][x] == 1 && 2 <= b && b <= 6 && a == 1
						&& (binaryImage.image_ptr[y - 1][x] * binaryImage.image_ptr[y][x + 1] * binaryImage.image_ptr[y][x - 1] == 0)
						&& (binaryImage.image_ptr[y - 1][x] * binaryImage.image_ptr[y + 1][x] * binaryImage.image_ptr[y][x - 1] == 0))
					{
						Point pt;
						pt.setX(x);
						pt.setY(y);
						pointsToChange.push_back(pt);
						hasChange = true;
					}
				}
			}
			for (Point point : pointsToChange) 
			{
				binaryImage.image_ptr[point.getY()][point.getX()] = 0;
			}
			pointsToChange.clear();
		} while (hasChange);
		binaryToGray(binaryImage);
}












