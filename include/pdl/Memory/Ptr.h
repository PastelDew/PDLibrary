#ifndef _PDL_MEMORY_PTR_H_
#define _PDL_MEMORY_PTR_H_

#include "RefCount.h"
#include "../Debug/Debug.h"

using namespace pdl::debug;

namespace pdl {
	namespace memory {
		template<typename T>
		static size_t ArraySize(T& arr) { return sizeof(arr); }
		template<typename T>
		static size_t ArraySize(T*& arr) { return _msize(arr); }
		template<typename T>
		static size_t ArraySize(T* arr) { return _msize(arr); }

		template<typename T>
		class Ptr {
		public:
			Ptr<T>(bool istemp = false) : isTemp(istemp) { mPtr = nullptr; }
			Ptr<T>(const Ptr<T>& ptr, bool istemp = false) : isTemp(istemp) {
				mPtr = nullptr;
				Copy(ptr);
				isTemp = (istemp && !isTemp ? true : isTemp);
			}
			Ptr<T>(T* ptr, bool istemp = false) : isTemp(istemp) { mPtr = nullptr; Copy(ptr); }
			~Ptr<T>() { Unref(); }

			T* Referer() const;
			void Ref();
			void Unref();

			Ptr<T>& operator =(Ptr<T> ptr);
			Ptr<T>& operator =(T* ptr);
			T& operator *();
			T* operator ->();
			bool operator == (const Ptr<T>& ptr) const;
			bool operator == (const T* ptr) const;
			bool operator == (const T& ptr) const;
			bool operator != (const Ptr<T>& ptr) const;
			bool operator != (const T* ptr) const;
			bool operator != (const T& ptr) const;
			bool operator ! () const;
			bool operator < (const Ptr<T>& ptr) const;
			bool operator > (const Ptr<T>& ptr) const;
			bool operator <= (const Ptr<T>& ptr) const;
			bool operator >= (const Ptr<T>& ptr) const;
			bool operator < (const T* ptr) const;
			bool operator > (const T* ptr) const;
			bool operator <= (const T* ptr) const;
			bool operator >= (const T* ptr) const;
			T& operator [] (const size_t idx) const;
			void SetTemp(bool isTemp = true);
			bool IsTemp();
			bool IsValid();
			
		private:
			T * mPtr;
			bool isTemp;

			void Copy(const Ptr<T>& s);
			void Copy(T* s);
		};

		template<typename T1, typename T2>
		static Ptr<T2> Cast(Ptr<T1> ptr) {
			T2* newPtr = (T2*) ptr.Referer();
			Ptr<T2> nPtr = newPtr;
			nPtr.SetTemp(ptr.IsTemp());
			return nPtr;
		}

		template<typename T1, typename T2>
		static Ptr<T2> DynamicCast(Ptr<T1> ptr) {
			T2* newPtr;
			newPtr = dynamic_cast<T2*>(ptr.Referer());
			if (newPtr == NULL) throw new Exception("DynamicCast error - Type incorrect!");
			Ptr<T2> nPtr;
			nPtr = newPtr;
			return nPtr;
		}
		
	}
}

#include "Ptr.hpp"

#endif // End of _PDL_MEMORY_PTR_H_