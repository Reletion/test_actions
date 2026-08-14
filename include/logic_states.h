#pragma once

#include "libsim_global.h"
#include <cstddef>

namespace libsim{
	enum class Logic_states : base::byte {
		LOW,
		HIGHT,
		Z,
		X,
	};
}
