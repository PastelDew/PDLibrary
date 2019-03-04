#pragma warning(disable: 4251)
#ifndef _PDL_DEBUG_EXCEPTION_H_
#define _PDL_DEBUG_EXCEPTION_H_

#include <string>

using namespace std;

namespace pdl {
	namespace debug {
		class PDLDLL_API Exception {
		protected:
			string mMSG;
			int mErrorCode;
		public:
			Exception(string msg, int errCode = 0)
				: mMSG(msg), mErrorCode(errCode) {}
			string GetMessage() { return mMSG; }
			int GetErrorCode() { return mErrorCode; }
		};
	}
}

#endif // End of _PDL_DEBUG_EXCEPTION_H_