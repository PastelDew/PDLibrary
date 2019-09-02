#pragma warning(disable: 4251)
#pragma warning(disable: 4290)
#pragma warning(disable: 4091)
#ifndef _PDL_PDCORE_H_
#define _PDL_PDCORE_H_

#if defined(__GNUC__) && defined(__unix__)

#define PDLDLL_API __attribute__((__visibility__("default")))
#define PDLDLL_EXTERN extern "C"

#elif defined(__clang__) // For mac

#define PDLDLL_API __attribute__((__visibility__("default")))
#define PDLDLL_EXTERN extern "C"

#elif defined(WIN32)

#ifdef PDL_DLL_EXPORTS

#define PDLDLL_API __declspec(dllexport)
#define PDLDLL_EXTERN

#else

#define PDLDLL_API __declspec(dllimport)
#define PDLDLL_EXTERN extern

#endif

#endif

#if defined(__clang__)
#define PDL_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#define PDL_COMPILER_GNU
#elif defined(_MSC_VER)
#define PDL_COMPILER_MSC
#endif

#define PDL_VERSION_MAJOR           1
#define PDL_VERSION_MINOR           0
#define PDL_VERSION_PATCHLEVEL      0
#define PDL_VERSION    (PDL_VERSION_MAJOR * 1000 + PDL_VERSION_MINOR * 100 + PDL_VERSION_PATCHLEVEL)

#include <stdint.h>
//#include <atlimage.h>
#include <iostream>

#include "Memory/Ptr.h"
#include "Memory/MemoryPool.h"
//#include "Core/Object.h"

#endif // End of _PDL_PDCORE_H_
