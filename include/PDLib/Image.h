#ifndef _PDL_IMAGE_IMAGE_H_
#define _PDL_IMAGE_IMAGE_H_

#include "Ptr.h"

using namespace pdl::memory;

namespace pdl {
	namespace media {
		class PDLDLL_API Image {
		public:
			enum Format {
				BLACK_N_WHITE, RGB_4, RGB_8, RLE_4, RLE_8, BGR_4, BGR_8,
				RGB_555, RGB_888, RGBA_4444, RGBA_8888,
				BGR_555, BGR_888, BGRA_4444, BGRA_8888
			};
			Image();
			Image(const Image& btm);
			Image(byte* buffer, LONG dataLength, LONG width, LONG height, Format format);
			Image&		Copy(const Image& btm);
			Image		Clone();
			void		Recycle();

			void		SetBuffer(byte* buffer, LONG dataLength, LONG width, LONG height, Format format);
			void		SetBuffer(Ptr<byte> buffer, LONG dataLength, LONG width, LONG height, Format format);

			WORD		GetBitCount();
			Ptr<byte>	GetBuffer();
			Format		GetPixelFormat();
			LONG		GetWidth();
			LONG		GetHeight();
			LONG		GetLength();

			Image&		operator = (Image& btm);
		private:
			LONG		mWidth;
			LONG		mHeight;
			LONG		mLength;
			Format		mPixelFormat;
			Ptr<byte>	mBuffer;
		};
	}
}

#endif // End of _PDL_IMAGE_IMAGE_H_