#include "libsim.h"
#include <benchmark/benchmark.h>

//libsim::Logic_states eval_qua(const std::array<libsim::Logic_states,7>& inputs){
//	return (inputs[6] == libsim::Logic_states::HIGHT) ? libsim::Logic_states::X : libsim::Logic_states::LOW;
//}

template<uint32_t NumVars>
void generate_tt_mask(benchmark::State& state){
	for(auto s : state){
		auto tt = libsim::tt_utils::generate_static_tt<NumVars>([](const std::array<libsim::Logic_states, NumVars>& inputs){
				return (inputs[2] == libsim::Logic_states::HIGHT) ? libsim::Logic_states::HIGHT : libsim::Logic_states::LOW;
		});

		benchmark::DoNotOptimize(tt);
		benchmark::ClobberMemory();
	}
}

template<uint32_t NumVars>
void generate_tt_state(benchmark::State& state){
	for(auto s : state){
		auto tt = libsim::tt_utils::generate_static_tt<NumVars>([](const std::array<libsim::Logic_states, NumVars>& inputs){
				return (inputs[2] == libsim::Logic_states::HIGHT) ? libsim::Logic_states::HIGHT : libsim::Logic_states::LOW;
		});

		benchmark::DoNotOptimize(tt);
		benchmark::ClobberMemory();
	}
}

//BENCHMARK(libsim::tt_utils::generate_static_tt<3>)->Arg(eval_test);
BENCHMARK(generate_tt_mask<7>);
BENCHMARK(generate_tt_state<7>);
BENCHMARK(generate_tt_mask<8>);
BENCHMARK(generate_tt_state<8>);
BENCHMARK(generate_tt_mask<9>);
BENCHMARK(generate_tt_state<9>);
BENCHMARK(generate_tt_mask<10>);
BENCHMARK(generate_tt_state<10>);
BENCHMARK(generate_tt_mask<11>);
BENCHMARK(generate_tt_state<11>);
BENCHMARK(generate_tt_mask<12>);
BENCHMARK(generate_tt_state<12>);
BENCHMARK(generate_tt_mask<13>);
BENCHMARK(generate_tt_state<13>);
BENCHMARK(generate_tt_mask<14>);
BENCHMARK(generate_tt_state<14>);
BENCHMARK(generate_tt_mask<15>);
BENCHMARK(generate_tt_state<15>);
BENCHMARK(generate_tt_mask<16>);
BENCHMARK(generate_tt_state<16>);
BENCHMARK(generate_tt_mask<17>);
BENCHMARK(generate_tt_state<17>);
BENCHMARK(generate_tt_mask<18>);
BENCHMARK(generate_tt_state<18>);
BENCHMARK(generate_tt_mask<19>);
BENCHMARK(generate_tt_state<19>);
BENCHMARK(generate_tt_mask<20>);
BENCHMARK(generate_tt_state<20>);
BENCHMARK(generate_tt_mask<21>);
BENCHMARK(generate_tt_state<21>);
BENCHMARK(generate_tt_mask<22>);
BENCHMARK(generate_tt_state<22>);
BENCHMARK(generate_tt_mask<23>);
BENCHMARK(generate_tt_state<23>);
BENCHMARK(generate_tt_mask<24>);
BENCHMARK(generate_tt_state<24>);
BENCHMARK(generate_tt_mask<25>);
BENCHMARK(generate_tt_state<25>);

BENCHMARK_MAIN();

/*
BENCHMARK(generate_tt_mask<26>);
BENCHMARK(generate_tt_state<26>);
BENCHMARK(generate_tt_mask<27>);
BENCHMARK(generate_tt_state<27>);
BENCHMARK(generate_tt_mask<28>);
BENCHMARK(generate_tt_state<28>);
BENCHMARK(generate_tt_mask<29>);
BENCHMARK(generate_tt_state<29>);
BENCHMARK(generate_tt_mask<30>);
BENCHMARK(generate_tt_state<30>);
BENCHMARK(generate_tt_mask<31>);
BENCHMARK(generate_tt_state<31>);
*/

//int main(){
//	auto tt = libsim::tt_utils::generate_static_tt<3>(eval_test);
//	return 0;
//}
