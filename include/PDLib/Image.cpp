#include "Image.h"

using namespace pdl::memory;
namespace pdl {
	namespace media {

		Image::Image() : mWidth(0), mHeight(0), mPixelFormat(RGB_888), mBuffer(NULL) {}
		Image::Image(const Image& btm) {
			Copy(btm);
		}

		Image::Image(byte* buffer, LONG dataLength, LONG width, LONG height, Format format) {
			SetBuffer(buffer, dataLength, width, height, format);
		}

		Image& Image::Copy(const Image& btm) {
			this->mWidth = btm.mWidth;
			this->mHeight = btm.mHeight;
			this->mLength = btm.mLength;
			this->mPixelFormat = btm.mPixelFormat;
			this->mBuffer = btm.mBuffer;
			return *this;
		}

		Image Image::Clone() {
			Image img(*this);
			return img;
		}
		void Image::Recycle() {
			mBuffer = NULL;
		}
		Ptr<byte> Image::GetBuffer() {
			return mBuffer;
		}
		void Image::SetBuffer(byte* buffer, LONG dataLength, LONG width, LONG height, Format format) {
			if (mBuffer.IsValid()) mBuffer = NULL;
			mBuffer = buffer;
			SetBuffer(mBuffer, dataLength, width, height, format);
		}
		void Image::SetBuffer(Ptr<byte> buffer, LONG dataLength, LONG width, LONG height, Format format) {
			LONG chkLen = (LONG)ArraySize<byte>(buffer.Ref());
			if (chkLen != dataLength) throw new Exception("Image::Image(byte*,WORD,WORD,WORD) error - The length of byte* argument does not match to 2nd argument WORD!");
			if (width * height == 0) throw new Exception("Image::Image(byte*,WORD,WORD,WORD) error - Width or Height cannot be zero!");
			if(*mBuffer.Ref() != *buffer.Ref()) mBuffer = buffer;
			mWidth = width;
			mHeight = height;
			mLength = dataLength;
			mPixelFormat = format;
		}
		WORD Image::GetBitCount() {
			WORD bitCount;
			switch (mPixelFormat) {
			case Image::Format::BLACK_N_WHITE: bitCount = 1; break;
			case Image::Format::RLE_4: case Image::Format::RGB_4: case Image::Format::BGR_4: bitCount = 4; break;
			case Image::Format::RLE_8: case Image::Format::RGB_8: case Image::Format::BGR_8: bitCount = 8; break;
			case Image::Format::RGB_555: case Image::Format::RGBA_4444:
			case Image::Format::BGR_555: case Image::Format::BGRA_4444: bitCount = 16; break;
			case Image::Format::RGB_888: case Image::Format::BGR_888: bitCount = 24; break;
			case Image::Format::RGBA_8888: case Image::Format::BGRA_8888: bitCount = 36; break;
			default: bitCount = 0;
			}
			return bitCount;
		}
		Image::Format Image::GetPixelFormat() {
			return mPixelFormat;
		}
		LONG Image::GetWidth() {
			return mWidth;
		}
		LONG Image::GetHeight() {
			return mHeight;
		}

		LONG Image::GetLength() {
			return mLength;
		}

		Image& Image::operator = (Image& btm) {
			return Copy(btm);
		}
	}
}