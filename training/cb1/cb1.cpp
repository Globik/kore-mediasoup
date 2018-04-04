#include <iostream>
#include <functional>
using namespace std;
class A{
	private:
	typedef std::function<void(void)> some_void;
	some_void f_;
	public:
	A();
	void setcallback(some_void f);
	void usecallback();
};
A::A(){}
void A::setcallback(some_void f){
f_=f;
}
void A::usecallback(){f_();}

class B{
	private:
	A*g;
	public:
	B();
	void somemethod();
	void othermethod();
};
B::B(){g=new A();}
void B::othermethod(){
g->setcallback(std::bind(&B::somemethod,this));
g->usecallback();
}
void B::somemethod(){
cout << "hello" << endl;
}
int main(){
B b;
b.othermethod();
return 0;
}