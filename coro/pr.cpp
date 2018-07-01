// /home/globik/q/build/lib/libq.a
// /home/globik/q/libs/q/include/q/promise.hpp

#include <iostream>
#include <q/lib.hpp>
#include <q/promise.hpp>
#include <q/execution_context.hpp>
#include <q/promise/make.hpp>
void fuck();
int main(){

	auto q_scope=q::scoped_initialize();
	auto ec=q::make_execution_context<q::blocking_dispatcher>("main");
	int a=0;
	q::with(ec->queue(),9)
	.then([&a](int f){
		std::cout << "hello world"<< f << std::endl;
		a=f;
	})
	.finally([ec](){
		ec->dispatcher()->terminate(q::termination::linger);
		});
		std::cout<<"before"<<"\n";
		
		
		//ec->dispatcher()->start();
		//auto prom=q::make_promise(q::queue(),[](){return 7;});
		std::cout<<"after und end\n" << a << "\n";
		return 0;
	}
