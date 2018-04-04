#include <iostream>
void* pt2obj;
class tb{
	public:
	void display(char*text){std::cout << text << std::endl;};
	static void wrapper_to_call_display(char*text);
};

void tb::wrapper_to_call_display(char*string){
tb* myself=(tb*)pt2obj;
myself->display(string);
}
void doit(void(*pfunc)(char*text)){
pfunc("hi");
}
void cb_glob(){
tb ob;
pt2obj=(void*)&ob;
doit(tb::wrapper_to_call_display);
}
int main(){
cb_glob();
return 0;
}