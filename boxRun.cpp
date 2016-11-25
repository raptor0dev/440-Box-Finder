#include "imageOpen.h"
#include "preprocessor.h"

int main()
{
	int exitflag = 0;
	bmpBITMAP_FILE orig_image;
	bmpBITMAP_FILE copy1,copy2;

	Load_Bitmap_File(orig_image);

	Display_FileHeader(orig_image.fileheader);
	Display_InfoHeader(orig_image.infoheader);
	
	//copies from orig_image to copy1(save original) and copy2(editable copy)
	Copy_Image(orig_image, copy1);
	cout << endl << "A copy of the file has been " <<
		"made in main memory.";
	Copy_Image(orig_image, copy2);
	cout << endl << "A second copy of the file has been " <<
		"made to process.";

	//Free memory of image
	Remove_Image(orig_image); // frees dynamic memory too
	cout << endl << "The original image has been " <<
		"removed from main memory.";

	//save copy1 to a output bitmap to show its the same as the original
	cout << endl << "To show that the first copy starts as " <<
		"an exact copy of the original,";
	cout << endl << "Save the copy as a bitmap." << endl;
	Save_Bitmap_File(copy1);
	Remove_Image(copy1);

	//select image processing choice for copy2
	while (exitflag == 0)
	{
		cout << endl << "Choose a processing option." << endl;
		cout << "0: display array, 1: increase brightness, 2: decrease brightness." << endl;
		cout << "3: increase contrast, 4: decrease contrst, 5: median smooth << endl;" << endl;
		cout << "6: equalize, 7: thin, 8: exit and save image copy" << endl;
		char option;
		cin >> option;

		switch (option) {
		case '0':
			cout << "Display bitmap file." << endl;
			Display_Bitmap_File(copy2);
			break;
		case '1':
			cout << "enter amount to increase brightness by." << endl;
			int brightness1;
			cin >> brightness1;
			increaseBrightness(copy2, brightness1);
			break;
		case '2':
			cout << "enter amount to decrease brightness by." << endl;
			int brightness2;
			cin >> brightness2;
			decreaseBrightness(copy2, brightness2);
			break;
		case '3':
			cout << "enter amount greater than 1 to increase contrast by." << endl;
			double contrast1;
			cin >> contrast1;
			increaseContrast(copy2, contrast1);
			break;
		case '4':
			cout << "enter amount less than 1 to decrease contrast by." << endl;
			double contrast2;
			cin >> contrast2;
			decreaseContrast(copy2, contrast2);
			break;
		case '5':
			cout << "Better try again" << endl;
			break;
		case '6':
			cout << "Better try again" << endl;
			break;
		case '7':
			cout << "Better try again" << endl;
			break;
		case '8':
			cout << "Finished" << endl;
			exitflag = 1;
			break;
		default:
			cout << "Invalid input" << endl;
			break;
		}
	}

	//save copy2 to a output bitmap to show the changes
	cout << endl << "To show that the edited copy's changes " << endl;
	cout << "Save the copy as a bitmap." << endl;
	Save_Bitmap_File(copy2);
	Remove_Image(copy2);

	char x;
	cin >> x;
	//test
	return 0;
}



