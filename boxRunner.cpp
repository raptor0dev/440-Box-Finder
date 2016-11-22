#define _CRT_SECURE_NO_DEPRECATE
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <iostream>

/*int main()
{
	unsigned char buffer[787512];

	ifstream myFile("im7-c.bmp", ios::in | ios::binary);
	myFile.read(buffer, 787512);

	ofstream hFile("test.bmp", ios::out | ios::binary);
	hFile.write(buffer, 787512);
}
*/

/*
fileName[in] : the name of the bitmap file (with .bmp extension) to open
header[out] : an unallocated pointer to store the header's data into
data[out] : an unallocated unsigned char pointer to store the integer data in

returns : 0 for failure, 1 for success
*/

int openBitmapAndGetInts(char fileName[], char **header, unsigned char **data);

void main(void)
{
	char *header;
	unsigned char *data;
	int ret = 0;

	//open the bitmap file...
	ret = openBitmapAndGetInts("im4-c.bmp", &header, &data);

	if (ret != 0)
	{
		/*
		This is where you do all your processing since everything went fine
		*/

		// Make certain to free our data...after all, we're not Microsoft...we
		// can't afford memory leaks
		free(header);
		free(data);
	}
}

int openBitmapAndGetInts(char fileName[], char **header, unsigned char **data)
{
	int headerSize = 14 +
		40 + 1026;
	FILE *file = fopen(fileName, "rb");
	int num = 0;

	//problem opening the file
	if (file == 0)
		return 0;

	//make the room for the header
	(*header) = (char *)malloc(headerSize);
	memset(*header, 0, headerSize);

	//make the room for the data
	(*data) = (unsigned char *)malloc(1024 * 768);
	memset(*data, 0, 1024 * 768);

	//problem getting the space for the header
	if ((*header) == 0)
		return 0;

	if ((*data) == 0)
		return 0;

	//read in the header for the bitmap
	num = fread((*header), 1, headerSize, file);

	//error reading in header
	if (num != headerSize)
		return 0;

	//read in the integer data
	num = fread((*data), 1, 1024 * 768, file);

	//error reading in data
	if (num != 1024 * 768)
		return 0;

	//close the file
	fclose(file);

	return 1;
}
