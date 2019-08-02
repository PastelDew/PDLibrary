#include "Serialize.h"

namespace pdl {
	namespace collection {
		Serialize::~Serialize() {
			buffer.Clear();
		}
		void Serialize::Clear() {
			buffer.Clear();
		}
		void Serialize::WriteUInt8(uint8_t data) {
			buffer << data;
		}
		void Serialize::WriteUInt16(uint16_t data) {
			uint8_t idata;
			for (int i = 1; i >= 0 && (idata == (idata = data >> (i * 8))); i--) buffer << idata;
		}
		void Serialize::WriteUInt32(uint32_t data) {
			uint8_t idata;
			for (int i = 3; i >= 0 && (idata == (idata = data >> (i * 8))); i--) buffer << idata;
		}
		void Serialize::WriteUInt64(uint64_t data) {
			uint8_t idata;
			for (int i = 7; i >= 0 && (idata == (idata = (uint8_t)(data >> (i * 8)))); i--) buffer << idata;
		}
		uint8_t Serialize::ReadUInt8() {
			size_t size = GetSize();
			if (size < 1) throw new Exception("Serialize::ReadUInt8() error - Cannot read data uint8. The buffer size is less than the data size.");
			uint8_t data = buffer[0];
			buffer.RemoveAt(0);
			return data;
		}
		uint16_t Serialize::ReadUInt16() {
			size_t size = GetSize();
			if (size < 2) throw new Exception("Serialize::ReadUInt16() error - Cannot read data uint16. The buffer size is less than the data size.");
			uint16_t data = (buffer[1] << 8) | (buffer[0]);
			for (int i = 0; i < 2; i++)
				buffer.RemoveAt(0);
			return data;
		}
		uint32_t Serialize::ReadUInt32() {
			size_t size = GetSize();
			if (size < 4) throw new Exception("Serialize::ReadUInt32() error - Cannot read data uint32. The buffer size is less than the data size.");
			uint32_t data = (buffer[3] << 24) | (buffer[2] << 16)
				| (buffer[1] << 8) | (buffer[0]);
			for (int i = 0; i < 4; i++)
				buffer.RemoveAt(0);
			return data;
		}
		uint64_t Serialize::ReadUInt64() {
			size_t size = GetSize();
			if (size < 8) throw new Exception("Serialize::ReadUInt64() error - Cannot read data uint64. The buffer size is less than the data size.");
			uint64_t data1 = (buffer[7] << 24) | (buffer[6] << 16)
				| (buffer[5] << 8) | (buffer[4]);
			uint32_t data2 = (buffer[3] << 24) | (buffer[2] << 16)
				| (buffer[1] << 8) | (buffer[0]);
			uint64_t data = (data1 << 32) | data2;
			for (int i = 0; i < 8; i++)
				buffer.RemoveAt(0);
			return data;
		}
		
		size_t Serialize::GetSize() {
			return buffer.Size();
		}
	}
}