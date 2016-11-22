#include "imageOpen.h"

int main()
{
	bmpBITMAP_FILE orig_image;
	bmpBITMAP_FILE copy1;

	Load_Bitmap_File(orig_image);

	Display_FileHeader(orig_image.fileheader);
	Display_InfoHeader(orig_image.infoheader);
	//copies from orig_image to copy1

	Copy_Image(orig_image, copy1);
	cout << endl << "A copy of the file has been " <<
		"made in main memory.";

	Remove_Image(orig_image); // frees dynamic memory too

	cout << endl << "The original image has been " <<
		"removed from main memory.";

	cout << endl << "To show that the copy starts as " <<
		"an exact copy of the original,";

	cout << endl << "Save the copy as a bitmap." << endl;
	Save_Bitmap_File(copy1);

	Remove_Image(copy1);
	char x;
	cin >> x;

	return 0;
}



