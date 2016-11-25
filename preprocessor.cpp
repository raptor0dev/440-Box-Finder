#include "preprocessor.h"

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

void edgeDetection(bmpBITMAP_FILE &image)
{

}

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