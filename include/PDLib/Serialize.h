#ifndef _PDL_IO_SERIALIZE_H_
#define _PDL_IO_SERIALIZE_H_

#include "ArrayList.h"

using namespace pdl::list;
using namespace pdl::debug;

namespace pdl {
	namespace io {
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
			ArrayList<uint8_t>				buffer;
		};

	}
}

#endif // End of _PDL_IO_SERIALIZE_H_