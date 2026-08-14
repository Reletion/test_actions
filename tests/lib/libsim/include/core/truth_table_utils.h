#pragma once

#include <kitty/kitty.hpp>
//#include <kitty/static_truth_table.hpp>
//#include <kitty/quaternary_truth_table.hpp>
#include <cstdint>
#include <string>
#include "logic_states.h"
#include <variant>

namespace libsim{
	namespace tt_utils{
		template<std::uint32_t NumVars>
		kitty::static_truth_table<NumVars> init_static_tt(const std::string& binary_string){
			kitty::static_truth_table<NumVars> tt;
			kitty::create_from_binary_string(tt, binary_string);
			return tt;
		}

		template<uint32_t NumVars, typename FUNC>
		kitty::static_truth_table<NumVars> generate_static_tt(FUNC eval){
			std::array<Logic_states, NumVars> inputs;
			const uint64_t n_comb = 1ULL<<NumVars;
			kitty::static_truth_table<NumVars> tt;

			for(uint64_t i{0}; i<n_comb; ++i){
				uint64_t i_b = i;
				for(uint32_t b_num{NumVars}; --b_num > 0;){
					if constexpr (NumVars <= 18){
						inputs[b_num] = static_cast<Logic_states>(i_b & 1);
						i_b = i_b >> 1;
					}
					else{
						if(inputs[b_num] == Logic_states::LOW) {
							inputs[b_num] = Logic_states::HIGHT;
							break;
						};
						inputs[b_num] = Logic_states::LOW;
					}
				}
				Logic_states state = eval(inputs);
				if(state == Logic_states::HIGHT) kitty::set_bit(tt, i);
			}

			return tt;
		}

		template<uint32_t NumVars, typename FUNC>
		kitty::static_truth_table<NumVars>& generate_static_heap_tt(FUNC eval){
			std::array<Logic_states, NumVars> inputs;
			const uint64_t n_comb = 1ULL<<NumVars;
			kitty::static_truth_table<NumVars>* tt = new kitty::static_truth_table<NumVars>;

			for(uint64_t i{0}; i<n_comb; ++i){
				uint64_t i_b = i;
				for(uint32_t b_num{NumVars}; --b_num > 0;){
					if constexpr (NumVars <= 18){
						inputs[b_num] = static_cast<Logic_states>(i_b & 1);
						i_b = i_b >> 1;
					}
					else{
						if(inputs[b_num] == Logic_states::LOW) {
							inputs[b_num] = Logic_states::HIGHT;
							break;
						};
						inputs[b_num] = Logic_states::LOW;
					}
				}
				Logic_states state = eval(inputs);
				if(state == Logic_states::HIGHT) kitty::set_bit(tt, i);
			}

			return tt;
		}

/*
		template<uint32_t NumVars, typename FUNC>
		kitty::static_truth_table<NumVars> generate_static_tt(FUNC eval){
			std::array<Logic_states, NumVars> inputs;
			const uint64_t n_comb = 1ULL<<NumVars;
			kitty::static_truth_table<NumVars> tt;

			if constexpr (NumVars <= 6){
				uint64_t onset=0;
				for(uint64_t i{0}; i<n_comb; ++i){
					uint64_t i_b = i;
					//for(uint32_t b_num{1}; b_num <= NumVars; ++b_num){
					//	inputs[NumVars - b_num] = static_cast<Logic_states>(i_b & 1);
					//	i_b = i_b >> 1;
					//}
					for(uint32_t b_num{NumVars}; --b_num > 0;){
						if(inputs[b_num] == Logic_states::LOW) {
							inputs[b_num] = Logic_states::HIGHT;
							break;
						};
						inputs[b_num] = Logic_states::LOW;
					}
					//uint64_t state = static_cast<uint64_t>(eval(inputs));
					base::byte state = static_cast<base::byte>(eval(inputs));
					onset |= (state<<i);
				}

				kitty::create_from_words(tt, &onset, &onset+1);
			}
			else {
				for(uint64_t i{0}; i<n_comb; ++i){
					uint64_t i_b = i;
					for(uint32_t b_num{1}; b_num <= NumVars; ++b_num){
						inputs[NumVars - b_num] = static_cast<Logic_states>(i_b & 1);
						i_b = i_b >> 1;
					}
					Logic_states state = eval(inputs);
					if(state == Logic_states::HIGHT) kitty::set_bit(tt, i);
				}
			}

			return tt;
		}
*/
		template<uint32_t NumVars>
		std::variant<kitty::static_truth_table<NumVars>, kitty::quaternary_truth_table<kitty::static_truth_table<NumVars>>> multiple_static_generator(Logic_states (*eval)(const std::array<Logic_states, NumVars>& inputs)){
			std::array<Logic_states, NumVars> inputs;
			const uint64_t n_comb = 1ULL<<NumVars;
			bool is_quaternary = false;

			if constexpr (NumVars <= 6){
				uint64_t onset=0;
				uint64_t offset=0;
				for(uint64_t i{0}; i<n_comb; ++i){
					uint64_t i_b = i;
					for(uint32_t b_num{1}; b_num <= NumVars; ++b_num){
						inputs[NumVars - b_num] = static_cast<Logic_states>(i_b & 1);
						i_b = i_b >> 1;
					}
					uint64_t state = static_cast<uint64_t>(eval(inputs));
					onset |=  ((state&1)<<i);
					offset |= (!((state&1) ^ (state>>1))<<i);
					if(state>1 && !is_quaternary) is_quaternary = true;
				}

				if(is_quaternary){
					kitty::quaternary_truth_table<kitty::static_truth_table<NumVars>> q_tt;
					kitty::create_from_words(q_tt._onset, &onset, &onset+1);
					kitty::create_from_words(q_tt._offset, &offset, &offset+1);

					return q_tt;
				}

				kitty::static_truth_table<NumVars> tt;
				kitty::create_from_words(tt, &onset, &onset+1);

				return tt;
			}
			else{
				kitty::quaternary_truth_table<kitty::static_truth_table<NumVars>> q_tt;
				kitty::static_truth_table<NumVars> tt;

				for(uint64_t i{0}; i<n_comb; ++i){
					uint64_t i_b = i;
					for(uint32_t b_num{1}; b_num <= NumVars; ++b_num){
						inputs[NumVars - b_num] = static_cast<Logic_states>(i_b & 1);
						i_b = i_b >> 1;
					}
					Logic_states state = eval(inputs);

					if(static_cast<base::byte>(state) > 1 && !is_quaternary) is_quaternary = true;
					if(state == Logic_states::HIGHT || state == Logic_states::X) {
						if(!is_quaternary) kitty::set_bit(tt, i);
						kitty::set_bit(q_tt._onset, i);
					}
					if(state == Logic_states::LOW || state == Logic_states::X) kitty::set_bit(q_tt._offset, i);
				}
				if(is_quaternary) return q_tt;
				return tt;
			}
		}
	}
}

/*
namespace libsim{
	namespace tt_utils{
		template<std::uint32_t NumVars>
		kitty::static_truth_table<NumVars>& init_static_tt(const std::string& binary_string);
		template<uint32_t NumVars>
		kitty::static_truth_table<NumVars>& generate_static_tt(Logic_states (*eval)(const std::vector<Logic_states>&));

	}
}
*/
