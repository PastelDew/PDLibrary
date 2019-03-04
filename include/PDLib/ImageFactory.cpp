#include "ImageFactory.h"
#define WIDTHBYTES(bit) (bit + 31) / 32 * 4


namespace pdl {
	namespace media {
		Image ImageFactory::CreateImage(WORD width, WORD height, Image::Format format) {
			if (width == 0 || height == 0) {
				throw new Exception("ImageFactory::CreateImage(WORD, WORD, Image::Format) error - The width or height of image must be bigger than 0!");
				return Image();
			}
			int bitCount = 16;

			switch (format) {
			case Image::Format::BLACK_N_WHITE: bitCount = 1; break;
			case Image::Format::RLE_4: case Image::Format::RGB_4: bitCount = 4; break;
			case Image::Format::RLE_8: case Image::Format::RGB_8: bitCount = 8; break;
			case Image::Format::RGB_555: case Image::Format::RGBA_4444:
			case Image::Format::BGR_555: case Image::Format::BGRA_4444: bitCount = 16; break;
			case Image::Format::RGB_888: case Image::Format::BGR_888: bitCount = 24; break;
			case Image::Format::RGBA_8888: case Image::Format::BGRA_8888: bitCount = 36; break;
			default:
				throw new Exception("ImageFactory::CreateImage(WORD, WORD, Image::Format) error - Not supported format: " + format);
				return Image();
			}
			WORD length = WIDTHBYTES(bitCount * width) * height;
			byte* data = new byte[length];
			return Image(data, length, width, height, format);
		}

		HBITMAP ImageFactory::ConvertImageToHBitmap(HDC hdc, Image& image) {
			BITMAPINFO btmInfo;
			LONG bufferLength = image.GetLength();
			LONG width = image.GetWidth();
			LONG height = image.GetHeight();
			Image::Format format = image.GetPixelFormat();
			WORD bitCount = image.GetBitCount();

			memset(&btmInfo, 0, sizeof(BITMAPINFO));
			btmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			btmInfo.bmiHeader.biWidth = width;
			btmInfo.bmiHeader.biHeight = height;
			btmInfo.bmiHeader.biPlanes = 1;
			btmInfo.bmiHeader.biBitCount = bitCount;
			btmInfo.bmiHeader.biCompression = BI_RGB;
			btmInfo.bmiHeader.biSizeImage = bufferLength;
			btmInfo.bmiHeader.biXPelsPerMeter = 0;
			btmInfo.bmiHeader.biYPelsPerMeter = 0;
			btmInfo.bmiHeader.biClrUsed = 0;
			btmInfo.bmiHeader.biClrImportant = 0;

			HBITMAP hBitmap;
			hBitmap = CreateDIBitmap(hdc, &btmInfo.bmiHeader, CBM_INIT, image.GetBuffer().Ref(), &btmInfo, DIB_RGB_COLORS);
			/*if(bitCount < 24) hBitmap = CreateDIBitmap(hdc, &btmInfo.bmiHeader, CBM_INIT, image.GetBuffer().Ref(), &btmInfo, DIB_RGB_COLORS);
			else {
			void* buffer = image.GetBuffer().Ref();
			hBitmap = CreateDIBSection(hdc, &btmInfo, DIB_RGB_COLORS, (void**)(&buffer), NULL, 0);
			}*/
			return hBitmap;
		}

		Image ImageFactory::ConvertHBitmapToImage(HDC hdc, HBITMAP bitmap) {
			if (bitmap == INVALID_HANDLE_VALUE)
				throw new Exception("ImageFactory::ConvertHBitmapToImage error - HBITMAP is null!");

			BITMAPINFO btmInfo;
			memset(&btmInfo, 0, sizeof(btmInfo));
			btmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			GetDIBits(hdc, bitmap, 0, 1, NULL, (BITMAPINFO *)&btmInfo, DIB_RGB_COLORS);

			// Assert bit compression_
			DWORD bitCompression = btmInfo.bmiHeader.biCompression;
			if (!(bitCompression == BI_PNG
				|| bitCompression == BI_JPEG
				|| bitCompression == BI_RGB
				|| bitCompression == BI_BITFIELDS)) {
				throw new Exception("ImageFactory::ConvertHBitmapToImage error - Not supported compression type!");
				return Image();
			}

			BITMAP btm;
			::GetObject(bitmap, sizeof(BITMAP), &btm);

			LONG size = btm.bmWidthBytes * btm.bmHeight;
			std::cout << "size: " << size << ", width: " << btm.bmWidth << ", height: " << btm.bmHeight << std::endl;
			byte* data = new byte[size];
			memset(data, 0, size);
			GetBitmapBits(bitmap, size, data);

			Image image;
			Image::Format format;
			switch (btmInfo.bmiHeader.biBitCount) {
			case 1:
				image.SetBuffer(data, size, btm.bmWidth, btm.bmHeight, Image::Format::BGR_4);
				Convert1bitTo16bitImage(image);
				return image;
			case 4:
				image.SetBuffer(data, size, btm.bmWidth, btm.bmHeight, Image::Format::BGR_4);
				Convert4bitTo16bitImage(image);
				return image;
			case 8:
				image.SetBuffer(data, size, btm.bmWidth, btm.bmHeight, Image::Format::BGR_4);
				Convert8bitTo16bitImage(image);
				return image;
			case 16: format = (bitCompression == BI_PNG) ? Image::Format::BGRA_4444 : Image::Format::BGR_555; break;
			case 24: format = Image::BGR_888; break;
				/*image.SetBuffer(data, size, btm.bmWidth, btm.bmHeight, Image::Format::BGR_888);
				ConvertBGR24bitToRGB24bit(image);
				return image;*/
			case 32: format = Image::BGRA_8888; break;
			}
			for (int i = 0; i < size; i++)
				std::cout << (int)data[i] << " ";
			image.SetBuffer(data, size, btm.bmWidth, btm.bmHeight, format);
			return image;
		}

		void ImageFactory::SaveBitmap(HBITMAP hbit, const string& path)
		{
			BITMAPFILEHEADER bFile;
			BITMAPINFOHEADER bInfo;
			BITMAP bit;
			BITMAPINFO *pih;
			int PalSize;
			HANDLE hFile;
			DWORD dwWritten, Size;
			HDC hdc;

			hdc = GetDC(NULL);

			GetObject(hbit, sizeof(BITMAP), &bit);
			bInfo.biSize = sizeof(BITMAPINFOHEADER);
			bInfo.biWidth = bit.bmWidth;
			bInfo.biHeight = bit.bmHeight;
			bInfo.biPlanes = 1;
			bInfo.biBitCount = bit.bmPlanes*bit.bmBitsPixel;
			if (bInfo.biBitCount > 8) bInfo.biBitCount = 24;
			bInfo.biCompression = BI_RGB;
			bInfo.biSizeImage = 0;
			bInfo.biXPelsPerMeter = 0;
			bInfo.biYPelsPerMeter = 0;
			bInfo.biClrUsed = 0;
			bInfo.biClrImportant = 0;

			PalSize = (bInfo.biBitCount == 24 ? 0 : 1 << bInfo.biBitCount) * sizeof(RGBQUAD);
			pih = (BITMAPINFO *)malloc(bInfo.biSize + PalSize);
			pih->bmiHeader = bInfo;

			GetDIBits(hdc, hbit, 0, bit.bmHeight, NULL, pih, DIB_RGB_COLORS);
			bInfo = pih->bmiHeader;

			if (bInfo.biSizeImage == 0)
			{
				bInfo.biSizeImage = ((((bInfo.biWidth*bInfo.biBitCount) + 31) & ~31) >> 3) * bInfo.biHeight;
			}

			Size = bInfo.biSize + PalSize + bInfo.biSizeImage;
			pih = (BITMAPINFO *)realloc(pih, Size);

			GetDIBits(hdc, hbit, 0, bit.bmHeight, (PBYTE)pih + bInfo.biSize + PalSize, pih, DIB_RGB_COLORS);

			bFile.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+PalSize;
			bFile.bfReserved1 = 0;
			bFile.bfReserved2 = 0;
			bFile.bfSize = Size + sizeof(BITMAPFILEHEADER);
			bFile.bfType = 0x4d42;

			hFile = CreateFile((LPCTSTR)path.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			WriteFile(hFile, &bFile, sizeof(bFile), &dwWritten, NULL);
			WriteFile(hFile, pih, Size, &dwWritten, NULL);

			ReleaseDC(NULL, hdc);
			CloseHandle(hFile);
		}

		Image ImageFactory::GetImageFromFile(const string& path) {
			CImage img;
			size_t pathSize = path.size();
			LPTSTR tPath = new TCHAR[pathSize + 1];
			for (size_t i = 0; i < pathSize; i++) tPath[i] = path[i];
			tPath[pathSize] = 0;
			if (FAILED(img.Load(tPath))) {
				delete tPath;
				return Image();
			}
			delete tPath;

			HBITMAP hBitmap = img.Detach();
			img.Attach(hBitmap);
			HDC hdc = img.GetDC();
			Image image = ImageFactory::ConvertHBitmapToImage(hdc, hBitmap);
			img.ReleaseDC();
			::DeleteObject(hBitmap);
			return image;
		}

		HBITMAP ImageFactory::GetHBITMAPFromFile(const string& path) {
			CImage img;
			size_t pathSize = path.size();
			LPTSTR tPath = new TCHAR[pathSize + 1];
			for (size_t i = 0; i < pathSize; i++) tPath[i] = path[i];
			tPath[pathSize] = 0;
			if (FAILED(img.Load(tPath))) {
				delete tPath;
				return NULL;
			}
			delete tPath;
			return img.Detach();
		}

		void ImageFactory::ConvertImageFormat(Image& image, Image::Format toFormat) {
			Image::Format format = image.GetPixelFormat();
			switch (toFormat) {
			case Image::Format::RGB_555: {
											 switch (format) {
											 case Image::Format::BLACK_N_WHITE:
												 Convert1bitTo16bitImage(image);
												 break;
											 case Image::Format::BGR_4:
												 Convert4bitTo16bitImage(image);
												 break;
											 default: return;
											 }
											 break;
			}
			default: return;
			}
		}

		void ImageFactory::UpsideDown(Image& image) {
			LONG bufferLength = image.GetLength();
			LONG width = image.GetWidth();
			LONG height = image.GetHeight();
			LONG widthBytes = WIDTHBYTES(16 * width);
			Ptr<byte> buffer = image.GetBuffer();
			LONG reSized = widthBytes * height;
			byte* newBuffer = new byte[reSized];
			memset(newBuffer, 0, reSized);
		}

		void ImageFactory::Convert1bitTo16bitImage(Image& image) {
			LONG bufferLength = image.GetLength();
			LONG width = image.GetWidth();
			LONG height = image.GetHeight();
			LONG widthBytes = WIDTHBYTES(16 * width);
			LONG reSized = widthBytes * height;
			Ptr<byte> buffer = image.GetBuffer();
			byte* newBuffer = new byte[reSized];
			memset(newBuffer, 0, reSized);

			LONG srcWidthBytes = WIDTHBYTES(width);
			bool bData;
			int idx, tmp, ti, tj;
			idx = tmp = ti = tj = 0;

			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++, tj++, tmp++) {
					bData = tmp >= width;
					if (tj > 7 || bData) {
						ti++;
						tj = 0;
						if (bData) {
							tmp = ti % srcWidthBytes;
							if (tmp != 0) {
								while (tmp < srcWidthBytes) {
									tmp++;
									ti++;
								}
								tmp = 0;
							}
						}
					}
					idx = widthBytes * i + j * 2;
					bData = (buffer[ti] >> (7 - tj)) & 0x01;
					if (bData) {
						newBuffer[idx] = 0xFF;
						newBuffer[idx + 1] = 0x7F;
					}
					else {
						newBuffer[idx] = 0x00;
						newBuffer[idx + 1] = 0x00;
					}
				}
				cout << endl;
			}
			image.SetBuffer(newBuffer, reSized, width, height, Image::Format::RGB_555);
		}
		void ImageFactory::Convert4bitTo16bitImage(Image& image) {
			LONG bufferLength = image.GetLength();
			LONG width = image.GetWidth();
			LONG height = image.GetHeight();
			LONG widthBytes = WIDTHBYTES(16 * width);
			LONG reSized = widthBytes * height;
			Ptr<byte> buffer = image.GetBuffer();
			byte* newBuffer = new byte[reSized];
			memset(newBuffer, 0, reSized);

			bool bData;
			int idx, tmp, ti, tj;
			idx = tmp = ti = tj = 0;

			bData = width % 4 > 0 && width % 4 < 3;
			for (int i = 0; i < height; i++, ti++) {
				tj = 0;
				for (int j = 0; j < width; j++, tj++, tmp++) {
					if (tj >= 2) {
						ti++;
						tj = 0;
					}
					idx = ((tj == 0) ? buffer[ti] >> 4 : buffer[ti]) & 0x0F;
					RGBQUAD pixel;
					pixel.rgbRed = ((idx & 0x01) == true) ? 255 : 0;
					pixel.rgbGreen = ((idx >> 1 & 0x01) == true) ? 255 : 0;
					pixel.rgbBlue = ((idx >> 2 & 0x01) == true) ? 255 : 0;
					idx = widthBytes * i + j * 2;
					newBuffer[idx] = ((pixel.rgbGreen & 0x07) << 5) | (pixel.rgbBlue & 0x1F);
					newBuffer[idx + 1] = ((pixel.rgbRed & 0x1F) << 2) | ((pixel.rgbGreen & 0x18) >> 3);
				}
				if (bData) ti++;
			}

			image.SetBuffer(newBuffer, reSized, width, height, Image::Format::RGB_555);
		}

		void ImageFactory::Convert8bitTo16bitImage(Image& image) {
			LONG bufferLength = image.GetLength();
			LONG width = image.GetWidth();
			LONG height = image.GetHeight();
			LONG widthBytes = WIDTHBYTES(16 * width);
			LONG reSized = widthBytes * height;
			Ptr<byte> buffer = image.GetBuffer();
			byte* newBuffer = new byte[reSized];
			memset(newBuffer, 0, reSized);

			int idx, tmp, ti;
			idx = tmp = ti = 0;
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++, ti++) {
					idx = widthBytes * i + j * 2;
					tmp = buffer[ti];
					newBuffer[idx] = (tmp & 0xE0 >> 3);
					newBuffer[idx + 1] = (tmp & 0x1C) << 3 | tmp & 0x07;
				}
			}

			image.SetBuffer(newBuffer, reSized, width, height, Image::Format::RGB_555);
		}

		void ConvertRGB24bitToBGR24bit(Image& image) {
			//ConvertRGB24bitToBGR24bit(image);
			throw new Exception("Not Implemented Function!");
		}

		void ImageFactory::ConvertBGR24bitToRGB24bit(Image& image) {
			LONG bufferLength = image.GetLength();
			LONG width = image.GetWidth();
			LONG height = image.GetHeight();
			Ptr<byte> buffer = image.GetBuffer();

			int idx, tmp;
			idx = tmp = 0;
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					idx = (i * width + j) * 3;
					tmp = buffer[idx];
					buffer[idx] = buffer[idx + 2];
					buffer[idx + 2] = tmp;
				}
			}
			image.SetBuffer(buffer, bufferLength, width, height, Image::RGB_888);
		}
	}
}