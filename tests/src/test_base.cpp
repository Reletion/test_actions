#include "libsim.h"
#include <iostream>

int main(){
	libsim::info::print_info();
	libsim::core::input a{8};
	a.set_const(libsim::Logic_states::LOW);
	std::cout<<a.get_id()<<std::endl;
	std::vector<libsim::Logic_states> data{libsim::Logic_states::HIGHT,libsim::Logic_states::HIGHT};
//	unsigned char b = libsim::elements::And_gate::eval(data);
//	std::cout<<(int)b<<std::endl;

//	std::cout<<libsim::elements::Not_gate::get_boolean_vector();
	return 0;
}

