#include "elements/and_gate.h"

namespace libsim{
	namespace elements{
		base::byte And_gate::eval(const std::vector<Logic_states>& inputs){
			return (inputs[0]==Logic_states::HIGHT && inputs[1]==Logic_states::HIGHT) ? return Logic_states::HIGHT : Logic_states::LOW;
		}
	}
}
