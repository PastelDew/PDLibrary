#ifndef _PDL_IO_SERIALIZE_H_
#define _PDL_IO_SERIALIZE_H_
#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER

#include "../PDCore.h"
#include "LinkedList.h"

using namespace std;
using namespace pdl::debug;

namespace pdl {
	namespace collection {
		class PDLDLL_API Serialize
		{
		public:
			~Serialize();
			void							Clear();
			void							WriteUInt8(uint8_t data);
			void							WriteUInt16(uint16_t data);
			void							WriteUInt32(uint32_t data);
			void							WriteUInt64(uint64_t data);
			uint8_t							ReadUInt8();
			uint16_t						ReadUInt16();
			uint32_t						ReadUInt32();
			uint64_t						ReadUInt64();
			template<typename T> void		WriteObject(T data);
			template<typename T> Ptr<T>		ReadObject();
			size_t							GetSize();

		private:
			LinkedList<uint8_t>				buffer;
		};

		PDLDLL_EXTERN template class PDLDLL_API LinkedList<uint8_t>;
	}
}

#include "Serialize.hpp"

#endif // End of _PDL_IO_SERIALIZE_H_