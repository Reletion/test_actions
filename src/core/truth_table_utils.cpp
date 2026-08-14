#include "core/truth_table_utils.h"
#include <cmath>

namespace libsim{
	namespace tt_utils{
		template<std::uint32_t NumVars>
		kitty::static_truth_table<NumVars>& init_static_tt(const std::string& binary_string){
			kitty::static_truth_table<NumVars> tt;
			kitty::create_from_binary_string(tt, binary_string);
			return tt;
		}
		template<uint32_t NumVars>
		kitty::static_truth_table<NumVars>& generate_static_tt(Logic_states (*eval)(const std::vector<Logic_states>& inputs)){
			std::vector<Logic_states> inputs;
			unsigned long long onset=0;
			for(unsigned long long i{0}; i<std::pow(2,NumVars); ++i){
				unsigned long long i_b = i;
				for(uint32_t b_num{1}; b_num <= NumVars; ++b_num){
					inputs[NumVars-b_num] = static_cast<Logic_states>(i_b & 1);
					i_b = i_b >> 1;
				}
				base::byte state = eval(inputs);
				onset = (onset<<1) | state;
			}

			kitty::static_truth_table<NumVars> tt;
			create_from_words(tt, &onset, &onset+1);
			return tt;
		}
	}
}
