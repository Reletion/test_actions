#pragma once

#include <vector>
#include <cstdint>
#include <type_traits>
#include "input.h"
#include "network.h"

namespace libsim{
	namespace core{
		class Object_template{
			public:
				static std::byte eval(std::vector<input> inputs);

				template<typename T>
				requires std::is_base_of_v<Network, T>
				consteval static T& return_network(){
					return T::convert_to(boolean_vector);
				}

				static bool is_base(){
					return true;
				}

			protected:
				static const char* const boolean_vector;
		};
	}
}
