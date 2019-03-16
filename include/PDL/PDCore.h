#pragma warning(disable: 4251)
#pragma warning(disable: 4290)
#pragma warning(disable: 4091)
#ifndef _PDL_PDCORE_H_
#define _PDL_PDCORE_H_

#ifdef PDL_DLL_EXPORTS
#define PDLDLL_API __declspec(dllexport)
#define PDLDLL_EXTERN
#else
#define PDLDLL_API __declspec(dllimport)
#define PDLDLL_EXTERN extern
#endif

#define PDL_VERSION 0.0.1

#include <stdint.h>
#include <atlimage.h>
#include <iostream>

#include "Memory/Ptr.h"
#include "Memory/MemoryPool.h"
//#include "Core/Object.h"

#endif // End of _PDL_PDCORE_H_