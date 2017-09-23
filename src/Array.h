//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2015
//
//

#ifndef _ARRAY_
#define _ARRAY_

namespace math
{

	//---------------------------------------------------------------------------------------------
	// Do NOT modify this section. For the implementation, see comment below the class declaration

	template <typename T>
	class Array
	{
	protected:
		T * buffer;
		unsigned int width, height;

	public:

		unsigned int getWidth() const { return width; }      // returns the width of the image
		unsigned int getHeight() const { return height; }    // returns the height of the image

		void * getRawDataPtr();                              // Obtain a pointer to the internal data
		// This is NOT a copy of the internal image data, but rather 
		// a pointer to the internally allocated space, so DO NOT
		// attempt to delete the pointer. 

		T & operator () (int x, int y);                      // return a reference to the element at position (column x, row y) 
		// of the array (zeor-based)

		const T & operator () (int x, int y) const;         // return a reference to the element at position (column x, row y) 
		// of the array (zeor-based)

		Array(unsigned int w, unsigned int h);               // Constructors. No default constructor allowed, as it makes no sense.
		Array(const Array<T> & source);                      //

		Array & operator = (const Array<T> & source);        // Copy assignment operator.

		bool operator == (const Array<T> & source) const;    // returns true of the current array and the source have the same dimensions AND 
		// one by one their elements of type T are the same. 

		void resize(unsigned int new_width, unsigned int new_height);	// Change the internal data storage size to the new ones.
		// If the one or both of the dimensions are smaller, clip the 
		// by discarding the remaining elements in the rows / columns outside
		// the margins. If the new dimensions are larger, pad the old elements
		// with elements initialized ot their default value (i.e. with their default initializer/constructor).

		virtual ~Array();									 // The distructor

	};

	// This is a templated class so include its implementation in the header file below this line:
	//--------------------------------------------------------------------------------------------

	inline unsigned int getSize(unsigned int width, unsigned int height) {
		return width * height;
	}

	template <typename T>
	unsigned int getSize(const Array<T>* arr) {
		return getSize(arr->getWidth(), arr->getHeight());
	}

	template <typename T>
	void * Array<T>::getRawDataPtr() {
		return this->buffer;
	}

	template <typename T>
	bool Array<T>::operator == (const Array<T> & source) const {
		if (this->getWidth() != source.getWidth() || this->getHeight() != source.getHeight()) {
			return false;
		}

		unsigned int size = getSize(this);

		for (unsigned int i = 0; i < size; i++) {
			if (this->buffer[i] != source.buffer[i]) return false;
		}
		return true;
	}

	template <typename T>
	Array<T> & Array<T>::operator = (const Array<T> & source) {
		if (this == &source) {
			return *this;
		}

		unsigned int size = getSize(this);
		unsigned int size_s = getSize(&source);

		if (size != size_s) {
			delete[] this->buffer;
			size = size_s;
			this->width = source.width;
			this->height = source.height;
			this->buffer = new T[size_s];
		}

		for (unsigned int i = 0; i < size; i++) {
			this->buffer[i] = source.buffer[i];
		}

		return *this;
	}

	template <typename T>
	T & Array<T>::operator () (int x, int y) {
		int index = x + y * this->getWidth();

		return this->buffer[index];
	}

	template <typename T>
	const T & Array<T>::operator () (int x, int y) const {
		int index = x + y * this->getWidth();

		return this->buffer[index];
	}

	template <typename T>
	void Array<T>::resize(unsigned int new_width, unsigned int new_height) {
		if (this->getHeight() == new_height && this->getWidth() == new_width) {
			return;
		}

		Array<T> tempArray = Array<T>(new_width, new_height);

		for (unsigned int y = 0; y < new_height; y++) {
			if (y >= this->getHeight()) {
				break;
			}

			for (unsigned int x = 0; x < new_width; x++) {
				if (x >= this->getWidth()) {
					break;
				}

				tempArray(x, y) = (*this)(x, y);
			}
		}

		delete[] this->buffer;
		this->buffer = tempArray.buffer;
		this->width = new_width;
		this->height = new_height;
		tempArray.buffer = nullptr;
	}

	template <typename T>
	Array<T>::Array(unsigned int w, unsigned int h) :width(w), height(h) {
		unsigned int size = getSize(this);
		this->buffer = new T[size];

		for (unsigned int i = 0; i < size; i++) {
			this->buffer[i] = T(); 
		}
	}

	template <typename T>
	Array<T>::Array(const Array<T> & source) :width(source.width), height(source.height) {
		unsigned int size = getSize(&source);
		this->buffer = new T[size];

		for (unsigned int i = 0; i <  size; i++) {
			this->buffer[i] = source.buffer[i];
		}
	}

	template<typename T>
	Array<T>::~Array() {
		if (this->buffer != nullptr) {
			delete[] this->buffer;
		}
	}


} // namespace math
#endif
