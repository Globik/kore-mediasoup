//#include "common.hpp"
//#include "DepLibSRTP.hpp"
#include "deplibuv.hpp"
//#include "DepOpenSSL.hpp"
//#include "Logger.hpp"
#include "Loop.hpp"
//#include "MediaSoupError.hpp"
//#include "Settings.hpp"
//#include "Utils.hpp"
#include "Channel/UnixStreamSocket.hpp"
/*
#include "RTC/DtlsTransport.hpp"
#include "RTC/SrtpSession.hpp"
#include "RTC/TcpServer.hpp"
#include "RTC/UdpSocket.hpp"
*/
#include <uv.h>
#include "uv_callback.h"
//#include <cerrno>
//#include <csignal>  // sigaction()
//#include <cstdlib>  // std::_Exit(), std::genenv()
//#include <iostream> // std::cout, std::cerr, std::endl
//#include <map>
//#include <string>
#include <unistd.h> // getpid(), usleep()

static void init();
static void ignoreSignals();
static void destroy();
static void exitSuccess();
static void exitWithError();
uv_callback_t to_cpp;

void*on_from_cpp(uv_callback_t*cb,void*data){
printf("on_from_cpp occurred!!! => %s\n",(char*)data);
char*s=(char*)data;
if(!strcmp(s,"exit")){printf("EXIT!!!\n");
uv_stop(get_loopi());				 
}
return NULL;
}

int main(){
class_init();
void*chl=set_channel();
init();
const char*s="{\"mama\":\"papa\"}";
int rc=uv_callback_fire(&to_cpp,(void*)s, NULL);
printf("rc fire %d\n",rc);
suka(chl);// it's a Loop loop(channel)
destroy();
exitSuccess();
return 0;
}

void init()
{

	//ignoreSignals();
	deplibuv_printversion();

	// Initialize static stuff.
	/*
	DepOpenSSL::ClassInit();
	DepLibSRTP::ClassInit();
	Utils::Crypto::ClassInit();
	RTC::UdpSocket::ClassInit();
	RTC::TcpServer::ClassInit();
	RTC::DtlsTransport::ClassInit();
	RTC::SrtpSession::ClassInit();
	*/
	//RTC::Room::ClassInit();
	rtc_room_classinit();
}

void destroy()
{
	//MS_TRACE();

	// Free static stuff.
	//RTC::DtlsTransport::ClassDestroy();
	//Utils::Crypto::ClassDestroy();
printf("destroy()\n");
	//uv_stop(deplibuv::getloop());
	class_destroy();
	//usleep(100000);
	
	//DepOpenSSL::ClassDestroy();
	//DepLibSRTP::ClassDestroy();
}

void exitSuccess()
{
	//printf(" SUCCESS: Wait a bit so peding messages to stdout/Channel arrive to the main process.\n");
	usleep(100000);
	printf("SUCCESS: And exit with success status.\n");
	_exit(0);
}