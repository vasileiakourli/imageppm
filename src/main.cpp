#include <iostream>
#include "ppm_format.h"
#include <string>
using namespace std;
using namespace imaging;
using namespace math;

int main(int argc, char * argv[]){

	string infilename;
	string outfilename;
	//diavazoume eisodo an xreiazetai alliws thetoume ta arxeia mas kateutheian
	if (argc == 1){
		cout << "File name of the image to load: ";
		string str;
		cin >> str;
		infilename = _strdup(str.c_str());
	}
	else if (argc == 4){
		infilename = argv[1];
		outfilename = argv[3];
	}
	else{
		infilename = argv[1];
	}

	//kaloume tin readppm gia na kanoume to stigmiotupo image

	Image im2;
	im2 << infilename;

	int wid = im2.getWidth();
	int hei = im2.getHeight();

	// ektupwnoume tis diastaseis kai ti fwteinotita
	cout << "Image dimensions are: " << wid << " X " << hei << endl;

	//vriskoume ta athroismata
	component_t average_red, average_green, average_blue;
	Color col;
	void *temp = im2.getRawDataPtr();

	for (int i = 0; i < wid; i++){
		for (int j = 0; j < hei; j++){
			col = im2.getPixel(i, j) + col;
		}
	}

	//mesos oros
	average_red = col.r / (wid * hei);
	average_green = col.g / (wid * hei);
	average_blue = col.b / (wid * hei);

	cout << "The average color of the image is (" << average_red << ", " << average_green << ", " << average_blue << ")" << endl;

	//an exoume epileksei kai eggrafi
	if (argc == 4){			
		im2 >> outfilename;
		cout << "Image written to " << argv[3] << endl;
	}

	//apodesmeusi xwro mnimis
	system("pause");
	return 0;
}
