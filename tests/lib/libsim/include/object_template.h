#pragma once

#include <vector>
#include <type_traits>
#include <cstdint>
//#include <cstring>
#include "input.h"
#include "logic_states.h"
#include "network.h"
#include "core/truth_table_utils.h"
//#include <kitty/static_truth_table.hpp>
//#include <kitty/constructors.hpp>
//#include <kitty/kitty.hpp>

//static_assert(false, "This file cannot be included. It is used for documentation");

namespace libsim{
	namespace core{
		template<typename Derived, uint32_t NumVars, bool = (NumVars <= 6 )>
		class Object_template;

		template<typename Derived, uint32_t NumVars>
		class Object_template<Derived, NumVars, true>{
			public:
				static Logic_states eval(const std::array<Logic_states, NumVars>& inputs);

				template<typename N>
				constexpr static typename std::enable_if<std::is_base_of_v<Network, N>, N&>::type
				network_realisation(){
					return N::convert_to(Derived::boolean_vector);
				}

				static bool is_base(){
					return true;
				}

				static uint32_t num_vars(){
					return NumVars;
				}

				static const kitty::static_truth_table<NumVars>& get_boolean_vector(){
					return Derived::boolean_vector;
				}

				//static bool is_equal(const char* boolean_vector){
					//strcmp()
				//}

			private:
				static inline const auto boolean_vector = tt_utils::generate_static_tt<NumVars>(&Derived::eval);
				//static constexpr kitty::static_truth_table<3> boolean_vector = kitty::static_truth_table<3>();
				/*
				Or use:
				static constexpr 	boolean_vector=

				You can also use:
				static constexpr	boolean_vector=

				Use: friend libsim::core::Object_template
				for correct work of CRTP
				*/
		};
	}
}
