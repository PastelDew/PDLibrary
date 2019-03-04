#ifndef _PDL_IMAGE_IMAGEFACTORY_H_
#define _PDL_IMAGE_IMAGEFACTORY_H_

#include "Image.h"

namespace pdl {
	namespace media {
		class PDLDLL_API ImageFactory {
		public:
			static Image	CreateImage(WORD width, WORD height, Image::Format format);
			static HBITMAP	ConvertImageToHBitmap(HDC hdc, Image& image);
			static Image	ConvertHBitmapToImage(HDC hdc, HBITMAP bitmap);
			static void		SaveBitmap(HBITMAP bitmap, const string& path);
			static Image	GetImageFromFile(const string& path);
			static HBITMAP	GetHBITMAPFromFile(const string& path);
			static void		ConvertImageFormat(Image& image, Image::Format toFormat);
		private:
			static void		UpsideDown(Image& image);
			static void		Convert1bitTo16bitImage(Image& image);
			static void		Convert4bitTo16bitImage(Image& image);
			static void		Convert8bitTo16bitImage(Image& image);
			static void		ConvertRGB24bitToBGR24bit(Image& image);
			static void		ConvertBGR24bitToRGB24bit(Image& image);
		};
	}
}

#endif // End of _PDL_IMAGE_IMAGEFACTORY_H_