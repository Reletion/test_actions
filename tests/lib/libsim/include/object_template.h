#pragma once

#include <vector>
#include <type_traits>
#include <cstring>
#include "input.h"
#include "logic_states.h"
#include "network.h"
//#include "../lib/kitty/kitty/static_truth_table.hpp"
#include <kitty/static_truth_table.hpp>

//static_assert(false, "This file cannot be included. It is used for documentation");

namespace libsim{
	namespace core{
		template<typename Derived>
		class Object_template{
			public:
				static base::byte eval(const std::vector<Logic_states>& inputs);

				template<typename N>
				constexpr static typename std::enable_if<std::is_base_of_v<Network, N>, N&>::type
				return_network(){
					return N::convert_to(Derived::boolean_vector);
				}

				static bool is_base(){
					return true;
				}

				static const char* const get_boolean_vector(){
					return Derived::boolean_vector;
				}

				//static bool is_equal(const char* boolean_vector){
					//strcmp()
				//}

			private:
				static constexpr   boolean_vector="";
				
		};
	}
}
