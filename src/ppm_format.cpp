#include <fstream>
#include <iostream>
#include <string>
#include "ppm_format.h"

using namespace std;

namespace imaging {

	Image * ReadPPM(const char * filename){
		unsigned int w, h, b;
		ifstream file(filename, ios::binary);	//anoigma arxeiou

		if (!file){							//elegxos anoigmatos arxeiou
			cerr << "Error opening file" << endl;
			exit(1);
		}

		string p6;
		file >> p6;

		//check an einai P6 format
		if (p6 != "P6") {
			cerr << "Invalid image format" << endl;
			exit(1);
		}

		//thetoume tis diastaseis tis eikonas
		file >> w;
		file >> h;
		file >> b;
		//elegxos an einai tou enos byte
		if (b > 255) {
			cerr << "file has not 1 byte components" << endl;
			exit(1);
		}
		//telos me tin kefalida

		//prosperasi twn parakatw xaraktirwn kai gemisma tou data me ta dedomena tis eikonas

		bool headerComplete = false;
		component_t * data = new component_t[3 * w * h];
		int i = 0;
		while (!file.eof() && i < 3 * w * h) {
			unsigned char col = file.get();

			if (!headerComplete && (col == ' ' || col == '\n' || col == '\r' || col == '\t')) {
				continue;
			}

			headerComplete = true;
			data[i++] = col / 255.f;
		}

		Image* image = new Image(w, h, data); //ftiaksame to stigmiotupo eikonas

		file.close();						//kleisimo arxeiou
		return image;						//epistrefoume to stigmiotupo

	}

	bool WritePPM(Image & image, const char * filename) {
		ofstream out = ofstream(filename,ios::binary);

		if (!out) {
			return false;
		}

		int b = 255;
		out << "P6 " << image.getWidth() << " " << image.getHeight() << " " << b << " ";

		if (out.fail()) {
			return false;
		}

		char* bytes = new char[getSize(&image) * 3];
		unsigned int i = 0;

		for (unsigned int y = 0; y < image.getHeight(); y++) {
			for (unsigned int x = 0; x < image.getWidth(); x++) {
				Color c = image.getPixel(x, y);
				bytes[i++] = char(c.x * b);
				bytes[i++] = char(c.y *b);
				bytes[i++] = char(c.z * b);
			}
		}

		out.write(bytes, i);
		delete[] bytes;

		return !out.fail();
		out.close();//kleisimo arxeiou
	}
}
