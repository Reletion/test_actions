#include "libsim.h"
#include <iostream>

int main(){
	libsim::base::print_info();
	libsim::core::input a{8};
	a.set_const(libsim::Logic_states::LOW);
	std::cout<<a.get_id()<<std::endl;
	return 0;
}

