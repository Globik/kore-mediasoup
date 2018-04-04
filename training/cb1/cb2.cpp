#include <iostream>
#include <functional>
#include <string>

void goodbye(const std::string& s){
std::cout<<"goodbye " << s << '\n';
}
class Object{
	public:
	void hello(const std::string& s){
	std::cout << "hello " << s << '\n';
	}
};
int main(){
typedef std::function<void(const std::string&)> examplefunc;
	Object instance;
	std::string str("World");
	examplefunc f=std::bind(&Object::hello,&instance,std::placeholders::_1);
	//instance.hello(str)
	f(str);
	f=std::bind(&goodbye,std::placeholders::_1);
	f(str);
	f(str);
	return 0;
}