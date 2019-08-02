#ifndef _PDL_IO_SERIALIZABLE_H_
#define _PDL_IO_SERIALIZABLE_H_
#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER

#include "../PDCore.h"
#include "Serialize.h"


namespace pdl {
	namespace collection {
		class Serializer;
		class PDLDLL_API Serializable {
		public:
			virtual const void Serialize(Ptr<Serializer> serz) = 0;
			virtual const void Deserialize(Ptr<Serializer> serz) = 0;
		};
	}
}

#endif // End of _PDL_IO_SERIALIZABLE_H_