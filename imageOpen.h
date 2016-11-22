#pragma once
/////////////////////////////////
//
// Program Bitmap_Parser
//
// CSCI 540
//
// Author: Mark A. Renslow markminn@mac.com
//
// Instructor: Dr. B. Julstrom
//
// I am sharing this code in the spirit of collaboration.  I
// have found that it serves my purposes, and I hope it
// improves your learning experience.  Please feel free to
// modify it for your own use.  I would appreciate any
// comments, questions or bug reports.

// I may be reached at: markminn@mac.com
//
// This program will read a binary file containing a bitmap
// and load it into a structure. Each pixel is assumed to be
// represented by 8 bits.  The binary data are maintained in
// the structure as bytes.  This makes reading and writing
// the files easy.  However, when integer values need to be
// extracted, the bytes need to be assembled into integers,
// using the Assemble_Integer() function.
//
// This code was written with the notion in mind that it
// could be scaled to deal with bitmaps other than the ones
// with 256 greys.  However, this version will only work
// with 256 greys. Additonally, extra work will need to be
// done to support bitmaps with bits-per-row not evenly
// divisible by 4.  (This is the "padding" issue)
//
// If you change the size of the image, there are three
// variables in the header which will need to be
// considered for updating.  They are:
//    bfSize
//    biWidth
//    biHeight
//
// Additionally, if the width of your new image is not
// evenly divisible by four bytes, you will have to add
// "padding" bytes to make it so.  This will change
// the size of the file (bfSize), so you should update
// that parameter to reflect padding. However, I do not
// think that biWidth is to be updated to reflect
// padding.  That is a question I have not had to
// answer yet.
//    
////////////////////

#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <iostream>
using namespace std;
typedef unsigned char  byte_t;

// The following two structures were adapted from
// http://users.ece.gatech.edu/~slabaugh/personal/c/bmpwrite.html
struct bmpFILEHEADER
{
	byte_t 	bfType[2];  //Bitmap identifier,  Must be "BM"
	byte_t	bfSize[4];
	byte_t       bfReserved[4];
	byte_t       bfOffbits[4];  //specifies the location
								//(in bytes) in the file of the
								// image data. Should be equal to
								// sizeof(bmpFileHeader + sizeof(bmpInfoHeader)
								//        + sizeof(Palette) 
};

struct bmpINFOHEADER
{
	byte_t	biSize[4];    // Size of the bmpInfoHeader, i.e. sizeof(bmpInfoheader)
	byte_t	biWidth[4];   // Width of bitmap, in pixels change this if you change
						  // the size of the image. see ***** note below

	byte_t  	biHeight[4];  // Height of bitmap, in pixels change this if you change
							  // the size of the image. see ***** note below
	byte_t 	biPlanes[2];  // Should/must be 1.
	byte_t	biBitCount[2]; // The bit depth of the bitmap.
						   // For 8 bit bitmaps, this is 8
	byte_t  	biCompression[4];   // Should be 0 for uncompressed bitmaps
	byte_t       biSizeImage[4];    //The size of the padded image, in bytes
	byte_t       biXPelsPerMeter[4]; //Horizontal resolution, in pixels per meter. Not signif.
	byte_t       biYPelsPermeter[4];  //Vertical resolution, as above.
	byte_t       biClrUsed[4];   //Indicates the number of colors in the palette.
	byte_t       biClrImportant[4]; //Indicates number of colors to display the bitmap.
									// Set to zero to indicate all colors should be used.
};
// *****Note (from above) you will have to write a function to do this. I have not yet.
struct bmpPALETTE
{
	byte_t	palPalette[1024]; // this will need to beimproved if the program is to scale.
							  // unless we change the palette, this will do.
};

struct bmpBITMAP_FILE	// note:  this structure may not be
						// written to file all at once.
						// the two headers may be written
						// normally, but the image requires
						// a write for each line followed
						//  by a possible 1 - 3 padding bytes.
{
	bmpFILEHEADER	fileheader;
	bmpINFOHEADER	infoheader;
	bmpPALETTE		palette;     //this implementation
								 // will not generalize.  Fixed at 256 shades of grey.
	byte_t		**image_ptr; //this points to the 
							 // image. Allows the allocation of a two dimensional
							 // array dynamically
};



//================= Open_input_file =======================
//
// Gets the name of the input file from the user and opens
// it for input
//

void open_input_file
(
	ifstream &in_file           //Pre:  none
								//Post: File name supplied by user
	);

//================ Assemble_Integer ========================
//
// Accepts a pointer to an array of unsigned characters
// (there should be 4 bytes)
// Assembles them into a signed integer and returns the
// result

int Assemble_Integer
(
	unsigned char bytes[]	// Pre: 4 little-endian bytes
							// (least significant byte first)
	);

//============= Display_FileHeader ==========================
//

void Display_FileHeader(bmpFILEHEADER &fileheader);

//============= Display_InfoHeader ==========================
//

void Display_InfoHeader(bmpINFOHEADER &infoheader);

//=============== Calc_Padding ==============================
//
// Returns the number of bytes of padding for an image
// (either 0,1,2,3).
// Each scan line must end on a 4 byte boundry.
// Threfore, if the pixel_width is not evenly divisible
// by 4, extra bytes are added (either 1, 2 or 3 extra
// bytes) when writing each line.  Likewise, when reading
// a bitmap file it may be helpful to remove the padding
// prior to any manipulations.
// This is not needed unless the number of bytes in a row
// are not evenly divisible by 4. See implementation
// section for details.
int Calc_Padding(int pixel_width);  //pre: the width of the
									//     image in pixels

//================= load_Bitmap_File =======================
//
void Load_Bitmap_File(bmpBITMAP_FILE &image);  
							//Post: structure is filled with data from a .bmp file

//============== Display_Bitmap_File =======================
//
void Display_Bitmap_File(bmpBITMAP_FILE &image);

//================== Copy_Image ============================
//
// Pre: image_orig.byte_t points to a 2 dim array
//      image_copy does not have an array associated with byte_t**
// Post: image_copy receives a copy of the structurs in image_orig
void Copy_Image(bmpBITMAP_FILE &image_orig,
	bmpBITMAP_FILE &image_copy);

//================== Remove_Image ==========================
//
// Pre:  image.byte-t contains pointers to a 2-dim array
// Post:  memory that **byte_t points to is freed with the
//        delete operator image.bfType[] is set to "XX"
//
void Remove_Image(bmpBITMAP_FILE &image);

//================= Save_Bitmap_File =======================
//
void Save_Bitmap_File(bmpBITMAP_FILE &image);

//=================== Open_Output_File =====================
//
void Open_Output_File(ofstream &out_file);