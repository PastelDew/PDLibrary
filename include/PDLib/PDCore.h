#pragma warning(disable: 4251)
#ifndef _PDL_PDCORE_H_
#define _PDL_PDCORE_H_

#ifdef PDL_DLL_EXPORTS
#define PDLDLL_API __declspec(dllexport)
#define PDLDLL_TEMPLATE extern
#else
#define PDLDLL_API __declspec(dllimport)
#define PDLDLL_TEMPLATE
#endif

#include <stdint.h>
#include <atlimage.h>
#include <iostream>

#include "Ptr.h"

#define PDL_VERSION 1.0.0

#endif // End of _PDL_PDCORE_H_