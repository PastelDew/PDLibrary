#ifndef _PDL_MEMORY_PTR_H_
#define _PDL_MEMORY_PTR_H_

#include <map>
#include "PDCore.h"
#include "Debug.h"

using namespace pdl::debug;

namespace pdl {
	namespace memory {
		template<typename T>
		static size_t ArraySize(T& arr) { return sizeof(arr); }
		template<typename T>
		static size_t ArraySize(T*& arr) { return _msize(arr); }
		template<typename T>
		static size_t ArraySize(T* arr) { return _msize(arr); }

		static std::map<void*, unsigned long long> _POINTER_COUNT;
		template<typename T>
		class Ptr {
		public:
			Ptr<T>() : isTemp(false) { mPtr = NULL; }
			Ptr<T>(const Ptr<T>& ptr) : isTemp(false) { Copy(ptr); }
			Ptr<T>(T* ptr) : isTemp(false) { Copy(ptr); }
			~Ptr<T>() { Delete(); }

			T* Ref();
			Ptr<T>& operator =(Ptr<T> ptr);
			Ptr<T>& operator =(T* ptr);
			T& operator *();
			T* operator ->();
			bool operator == (Ptr<T>& ptr);
			bool operator == (T* ptr);
			bool operator == (T& ptr);
			bool operator != (Ptr<T>& ptr);
			bool operator != (T* ptr);
			bool operator != (T& ptr);
			bool operator ! ();
			T& operator [] (size_t idx);
			void SetTemp(bool isTemp);
			bool IsValid();

		private:
			T * mPtr;
			bool isTemp;

			void Copy(const Ptr<T>& s) {
				if (mPtr == s.mPtr) return;
				T* target = mPtr;
				std::map<void*, unsigned long long>::iterator it = _POINTER_COUNT.find(target);
				if (it != _POINTER_COUNT.end()) Delete();

				target = s.mPtr;
				it = _POINTER_COUNT.find(target);
				if (it != _POINTER_COUNT.end()) _POINTER_COUNT[target]++;
				else _POINTER_COUNT[target] = 1;
				mPtr = target;
			}

			void Copy(T* s) {
				if (mPtr == s) return;
				T* target = mPtr;
				std::map<void*, unsigned long long>::iterator it = _POINTER_COUNT.find(target);
				if (it != _POINTER_COUNT.end()) Delete();

				target = s;
				it = _POINTER_COUNT.find(target);
				if (it != _POINTER_COUNT.end()) _POINTER_COUNT[target]++;
				else _POINTER_COUNT[target] = 1;
				mPtr = target;
			}

			void Delete() {
				if (mPtr && !isTemp) {
					std::map<void*, unsigned long long>::iterator it = _POINTER_COUNT.find(mPtr);
					if (it != _POINTER_COUNT.end()) {
						_POINTER_COUNT[mPtr]--;
						if (_POINTER_COUNT[mPtr] == 0) delete mPtr;
					}
				}
			}
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
		static Ptr<T1> DynamicCast(Ptr<T2> ptr) {
			T1* newPtr;
			newPtr = dynamic_cast<T1*>(ptr.Ref());
			if (newPtr == NULL) throw new Exception("DynamicCast error - Type incorrect!");
			Ptr<T1> nPtr;
			nPtr = newPtr;
			return nPtr;
		}
	}
}

#include "Ptr.hpp"

#endif // End of _PDL_MEMORY_PTR_H_