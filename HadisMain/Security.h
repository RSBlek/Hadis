#pragma once
#include <intrin.h>

namespace Security {
	static unsigned long long getUIObjectID(unsigned int objectid) {
		unsigned long long output = objectid;
		output = ~output;
		output = _rotl64(output, 19);
		return output;
	}

	static unsigned int getRealObjectID(unsigned long long objectid) {
		objectid = _rotr64(objectid, 19);
		objectid = ~objectid;
		unsigned int output = static_cast<unsigned int>(objectid);
		return output;
	}

}