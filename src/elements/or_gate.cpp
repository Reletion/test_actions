#include "elements/or_gate.h"

namespace libsim{
	namespace elements{
		base::byte Or_gate::eval(const std::vector<Logic_states>& inputs){
			if(inputs[0]==Logic_states::HIGHT || inputs[1]==Logic_states::HIGHT) return Logic_states::HIGHT;
			return Logic_states::LOW;
		}
	}
}
