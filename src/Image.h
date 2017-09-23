//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2015
//
//

#ifndef _IMAGE
#define _IMAGE

#include "Array.h"
#include "Vec3.h"
#include "Serializable.h"

using namespace math;

// We put every class or function associated with the image storage, compression and manipulation 
// in the "imaging" namespace
namespace imaging
{
	typedef float component_t;
	typedef Vec3<component_t> Color;

	//------------------------------------ class Image ------------------------------------------------
	// 
	// It is the class that represents a generic data container for an image. It holds the actual buffer
	// of the pixel values and provides methods for accessing them either as individual pixels or as
	// a memory block. The Image class alone does not provide any functionality for loading and storing an image, as
	// it is the result or input to such a procedure. 
	//
	// The internal buffer of an image object stores the actual bytes (data) of the color image as
	// a contiguous sequence of RGB triplets. Hence, the size of the buffer variable holding these data is 
	// 3 X width X height bytes.

	class Image : public Array<Color>, Serializable
	{
	public:
		enum channel_t { RED = 0, GREEN, BLUE };          // now you can use the names RED, GREEN, BLUE instead of 0,1,2
		// to index individual channels

	public:

		Color getPixel(unsigned int x, unsigned int y) const;    // get the color of the image at location (x,y)
		// Do any necessary bound checking. Also take into account
		// the "interleaved" flag to fetch the appropriate data
		// Return a black (0,0,0) color in case of an out-of-bounds
		// x,y pair

		// data mutators
		void setPixel(unsigned int x, unsigned int y, Color & value);
		// Set the RGB values for an (x,y) pixel. Do all 
		// necessary bound checks and respect the "interleaved"
		// flag when updating our data.

		void setData(const component_t * & data_ptr);            // Copy the data from data_ptr to the internal buffer.

		bool operator << (std::string filename);
		bool operator >> (std::string filename);

		// constructors and destructor
		Image();											     // default: zero dimensions, nullptr for the buffer.	
		Image(unsigned int width, unsigned int height);
		Image(unsigned int width, unsigned int height, const component_t * data_ptr);
		Image(const Image &src);
		~Image();

	};


	inline Color Image::getPixel(unsigned int x, unsigned int y) const {

		if (x>this->getWidth() - 1 || y>this->getHeight() - 1) {
			return Color();
		}
		return (*this)(x, y);
	}

	inline void Image::setPixel(unsigned int x, unsigned int y, Color & value) {
		if (x>this->getWidth() - 1 || y>this->getHeight() - 1) {
			return;
		}

		(*this)(x, y) = value;
	}

	inline void Image::setData(const component_t * & data_ptr) {
		for (unsigned int x = 0; x < this->getWidth(); x++) {
			for (unsigned int y = 0; y < this->getHeight(); y++) {
				unsigned int index = 3 * (y * this->getWidth() + x);
				Color c;
				c.x = data_ptr[index + channel_t::RED];
				c.y = data_ptr[index + channel_t::GREEN];
				c.z = data_ptr[index + channel_t::BLUE];
				this->setPixel(x, y, c);

			}
		}
	}

	inline Image::Image() :Array(0, 0) {}

	inline Image::Image(unsigned int width, unsigned int height) : Array(width, height) {}

	inline Image::Image(unsigned int width, unsigned int height, const component_t * data_ptr) : Array(width, height) {
		this->setData(data_ptr);
	}

	inline Image::Image(const Image &src) : Array(src) {}

	inline Image::~Image() {
		int i = 0;
	}

	Image * ReadPPM(const char * filename);
	bool WritePPM(Image & image, const char * filename);

	inline bool Image::operator << (std::string filename) {
		Image* img = ReadPPM(filename.c_str());

		if (img == nullptr) {
			return false;
		}

		this->width = img->getWidth();
		this->height = img->getHeight();

		if (this->buffer != nullptr) {
			delete[] buffer;
		}

		this->buffer = img->buffer;
		img->buffer = nullptr;
		delete img;

		return true;
	}

	inline bool Image::operator >> (std::string filename) {
		return WritePPM(*this, filename.c_str());
	}

} //namespace imaging

#endif
