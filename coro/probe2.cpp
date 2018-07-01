#include <iostream>
#include <future>
#include <thread>
// n
int main(){
	std::packaged_task<int()> task([]{return 7;});
	
	std::thread t(std::move(task));
	std::future<int> f2=std::async(std::launch::async,[]{return 8;});
	f2.wait();
	std::cout << f2.get() << '\n';
	t.join();
	return 0;
	}
