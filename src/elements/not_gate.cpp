#include "elements/not_gate.h"

namespace libsim{
	namespace elements{
		base::byte Not_gate::eval(const std::vector<Logic_states>& inputs){
			return !inputs[0];
		}
	}
}
