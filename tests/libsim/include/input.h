#pragma once

#include "libsim_global.h"
#include "logic_states.h"

namespace libsim{
	namespace core{
		class input{
			private:
				base::ID_t id;
			public:
				input(base::ID_t id) : id(id){};
				base::ID_t get_id();
				void set_id(base::ID_t id);
				void set_const(Logic_states state);
		};
	}
}
