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

void medianSmooth(bmpBITMAP_FILE &image)
{

}

void histogramEqualization(bmpBITMAP_FILE &image)
{

}

void thinningAlg(bmpBITMAP_FILE &image)
{
	
}