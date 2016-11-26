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
	
	Copy_Image(orig_image, copy2);
	cout << endl << "A second copy of the file has been " <<
		"made to process.";

	//Free memory of image
	//Remove_Image(orig_image); // frees dynamic memory too
	//cout << endl << "The original image has been " <<
		//"removed from main memory." << endl;

	//select image processing choice for copy2
	while (exitflag == 0)
	{
		cout << endl << "Choose a processing option." << endl;
		cout << "0: display array, 1: increase brightness, 2: decrease brightness" << endl;
		cout << "3: increase contrast, 4: decrease contrast, 5: median smooth" << endl;
		cout << "6: equalize, 7: edge detect, 8: thin, 9: convert to black and white" << endl;
		cout << "b: convert to binary(test), g: convert to gray scale" << endl;
		cout << "s: save current image, r: reset image, e: exit" << endl;
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
			cout << "median smoothing" << endl;
			medianSmooth(copy2);
			break;
		case '6':
			cout << "equalizing" << endl;
			histogramEqualization(copy2);
			break;
		case '7':
			cout << "sobel edge detect" << endl;
			sobelEdgeDetection(copy2);
			break;
		case '8':
			cout << "crappy thin" << endl;
			//thinning(copy2);
			doZhangSuenThinning(copy2);
			break;
		case '9':
			cout << "converting grayscale to black and white" << endl;
			grayToBlackWhite(copy2);
			break;
		case 'b':
			cout << "converting grayscale to binary" << endl;
			grayToBinary(copy2);
			break;
		case 'g':
			cout << "converting binary to grayscale" << endl;
			binaryToGray(copy2);
			break;
		case 's':
			cout << endl << "To show the edited copy's changes " << endl;
			cout << "Save the copy as a bitmap." << endl;
			Save_Bitmap_File(copy2);
			break;
		case 'r':
			cout << endl << "Resetting changes to image" << endl;
			Copy_Image(orig_image, copy2);
			break;
		case 'e':
			cout << "Finished" << endl;
			exitflag = 1;
			break;
		default:
			cout << "Invalid input" << endl;
			break;
		}
	}
	//save copy2 to a output bitmap to show the changes
	//cout << endl << "To show the edited copy's changes " << endl;
	//cout << "Save the copy as a bitmap." << endl;
	Remove_Image(orig_image);
	Remove_Image(copy2);

	return 0;
}



