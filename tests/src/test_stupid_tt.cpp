#include "libsim.h"
#include <benchmark/benchmark.h>
#include <chrono>
#include <iostream>

libsim::Logic_states eval_test(const std::array<libsim::Logic_states, 20>& inputs){
	return (inputs[2] == libsim::Logic_states::HIGHT) ? libsim::Logic_states::HIGHT : libsim::Logic_states::LOW;
}

libsim::Logic_states eval_test_4(const std::array<libsim::Logic_states, 4>& inputs){
	return (inputs[2] == libsim::Logic_states::HIGHT) ? libsim::Logic_states::HIGHT : libsim::Logic_states::LOW;
}

libsim::Logic_states eval_test_6(const std::array<libsim::Logic_states, 6>& inputs){
	return (inputs[2] == libsim::Logic_states::HIGHT) ? libsim::Logic_states::HIGHT : libsim::Logic_states::LOW;
}

libsim::Logic_states eval_test_7(const std::array<libsim::Logic_states, 7>& inputs){
	return (inputs[2] == libsim::Logic_states::HIGHT) ? libsim::Logic_states::HIGHT : libsim::Logic_states::LOW;
}

libsim::Logic_states eval_qua(const std::array<libsim::Logic_states,3>& inputs){
	if(inputs[0] == libsim::Logic_states::HIGHT) return libsim::Logic_states::LOW;
	if(inputs[1]==libsim::Logic_states::LOW) return libsim::Logic_states::HIGHT;
	if(inputs[0] == libsim::Logic_states::LOW && inputs[1] == libsim::Logic_states::HIGHT) return libsim::Logic_states::X;
	return libsim::Logic_states::Z;
}

int main(){
	std::cout<<"!!!!!"<<"\n";
//	kitty::static_truth_table<26> tt;

	auto tt = libsim::tt_utils::generate_static_tt<20>(eval_test);
//	std::array<libsim::Logic_states,26> inputs{libsim::Logic_states::LOW};

//	std::cout<<static_cast<libsim::base::byte>(inputs[0])<<"\n";
//	kitty::set_bit(tt,67108862);
	std::cout<<kitty::get_bit(tt,25)<<"\n";
	return 0;
}
