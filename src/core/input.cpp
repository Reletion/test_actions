#include "input.h"
#include "logic_states.h"

namespace libsim{
	namespace core{
		base::ID_t input::get_id(){
			return id;
		}
		void input::set_id(base::ID_t id){
			this->id = id;
		}
		void input::set_const(Logic_states state){
			id = static_cast<base::ID_t>(state);
		}
	}
}
