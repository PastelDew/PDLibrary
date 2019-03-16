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
			void Ref();
			void Unref();
		};

		
		template<typename T>
		static Ptr<T> Create() { return new T(); }
		template<typename T, typename A1>
		static Ptr<T> Create(A1 a1) { return Ptr<T>(new T(a1)); }
		template<typename T, typename A1, typename A2>
		static Ptr<T> Create(A1 a1, A2 a2) { return Ptr<T>(new T(a1, a2)); }
		template<typename T, typename A1, typename A2, typename A3>
		static Ptr<T> Create(A1 a1, A2 a2, A3 a3) { return Ptr<T>(new T(a1, a2, a3)); }
		template<typename T, typename A1, typename A2, typename A3, typename A4>
		static Ptr<T> Create(A1 a1, A2 a2, A3 a3, A4 a4) { return Ptr<T>(new T(a1, a2, a3, a4)); }
		template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
		static Ptr<T> Create(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) { return Ptr<T>(new T(a1, a2, a3, a4, a5)); }
		template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
		static Ptr<T> Create(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) { return Ptr<T>(new T(a1, a2, a3, a4, a5, a6)); }
		template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
		static Ptr<T> Create(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) { return Ptr<T>(new T(a1, a2, a3, a4, a5, a6, a7)); }

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