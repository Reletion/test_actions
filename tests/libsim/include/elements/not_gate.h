#pragma once

#include "object_template.h"

namespace libsim{
	namespace elements{
		class Not_gate : public core::Object_template{
			public:
				static base::byte eval(const std::vector<Logic_states>& inputs);
			protected:
				static constexpr const char* boolean_vector = "10";
		};
	}
}
