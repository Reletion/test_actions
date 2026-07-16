#pragma once

#include "../object_template.h"

namespace libsim{
	namespace elements{
		class And_gate : public core::Object_template{
			public:
				static base::byte eval(const std::vector<Logic_states>& inputs);
		};
	}
}
