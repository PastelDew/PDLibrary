#include "TestBase.h"

#include "PDLib/Serialize.h"
#include "PDLib/Ptr.h"

using namespace pdl::io;
using namespace pdl::memory;

class TestByteRead : public TestBase {
public:
	void Run() {
		Ptr<Serialize> mSerz = Create<Serialize>();
	}
};