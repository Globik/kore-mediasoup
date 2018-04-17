#define MS_CLASS "Channel::UnixStreamSocket"
// #define MS_LOG_DEV

#include "Channel/UnixStreamSocket.hpp"
#include "deplibuv.hpp"
#include "Logger.hpp"
#include "MediaSoupError.hpp"
#include <cmath>   // std::ceil()
#include <cstdio>  // sprintf()
#include <cstring> // std::memmove()
#include <sstream> // std::ostringstream
#include <string>
extern "C" {
//#include <netstring.h>
}

namespace Channel
{
	/* Static. */

	// netstring length for a 65536 bytes payload.
	static constexpr size_t MaxSize{ 65543 };
	static constexpr size_t MessageMaxSize{ 65536 };
	static uint8_t WriteBuffer[MaxSize];
	

	/* Instance methods. */

	UnixStreamSocket::UnixStreamSocket(int fd) //: ::UnixStreamSocket::UnixStreamSocket(fd, MaxSize)
	{
		MS_TRACE_STD();
	
		uv_loop_t*mloop=deplibuv::getloop();
		//uv_loop_set_data(mloop,(void*)"some_data");
		uv_loop_set_data(mloop,(void*)this);
		
int rc=uv_callback_init(mloop, &this->to_cpp, UnixStreamSocket::on_to_cpp, UV_DEFAULT);
		std::printf("rc: %d\n",rc);
		
		// Create the JSON reader.
		{
			Json::CharReaderBuilder builder;
			Json::Value settings = Json::nullValue;
			Json::Value invalidSettings;

			builder.strictMode(&settings);

			MS_ASSERT(builder.validate(&invalidSettings), "invalid Json::CharReaderBuilder");

			this->jsonReader = builder.newCharReader();
		}

		// Create the JSON writer.
		{
			Json::StreamWriterBuilder builder;
			Json::Value invalidSettings;

			builder["commentStyle"]            = "None";
			builder["indentation"]             = "";
			builder["enableYAMLCompatibility"] = false;
			builder["dropNullPlaceholders"]    = false;

			MS_ASSERT(builder.validate(&invalidSettings), "invalid Json::StreamWriterBuilder");

			this->jsonWriter = builder.newStreamWriter();
		}
	}

	UnixStreamSocket::~UnixStreamSocket()
	{
MS_TRACE_STD();
std::printf("What the fuck in destractor?\n");
		delete this->jsonReader;
		delete this->jsonWriter;
	}
	
void * UnixStreamSocket::on_to_cpp(uv_callback_t*callback,void*data)
{
	
std::printf("HERE AND HERE ON_TO_CPP occured: %s\n",(char*)data);
	//char * gu=(char*)((uv_handle_t*)callback)->loop->data;
//void*lu=uv_loop_get_data(deplibuv::getloop());
//std::printf("some data came: %s\n",(char*)lu);
//static_cast<UnixStreamSocket*>
void*bu=uv_loop_get_data(deplibuv::getloop());
	static_cast<UnixStreamSocket*>(bu)->listener->mfuck();
	static_cast<UnixStreamSocket*>(bu)->UserOnUnixStreamRead("{\"dama\":\"sama\"}\0");
	
	/*
	Channel::UnixStreamSocket m(4);
//	new Channel::UnixStreamSocket(channelFd);
	m.UserOnUnixStreamRead("{\"dama\":\"sama\"}\0");
	//UnixStreamSocket::UserOnUnixStreamRead("mama\0");
	//UserOnUnixStreamRead("m");
	*/
return nullptr;
}
//Listener  li=this->listener;

	void UnixStreamSocket::SetListener(Listener* listener)
	{
		MS_TRACE_STD();
		std::printf("unixstreamsocket::setlistener()\n");

		this->listener = listener;
		this->listener->mfuck();
	}

	void UnixStreamSocket::Send(Json::Value& msg)
	{
		std::printf("UnixStreamSocket::Send(Json) occured\n");
		std::cout << msg << std::endl;
		//if (this->closed)return;

		// MS_TRACE_STD();
/*
		std::ostringstream stream;
		std::string nsPayload;
		size_t nsPayloadLen;
		size_t nsNumLen;
		size_t nsLen;

		this->jsonWriter->write(msg, &stream);
		nsPayload    = stream.str();
		nsPayloadLen = nsPayload.length();

		if (nsPayloadLen > MessageMaxSize)
		{
			MS_ERROR_STD("mesage too big");

			return;
		}

		if (nsPayloadLen == 0)
		{
			nsNumLen       = 1;
			WriteBuffer[0] = '0';
			WriteBuffer[1] = ':';
			WriteBuffer[2] = ',';
		}
		else
		{
			nsNumLen = static_cast<size_t>(std::ceil(std::log10(static_cast<double>(nsPayloadLen) + 1)));
			std::sprintf(reinterpret_cast<char*>(WriteBuffer), "%zu:", nsPayloadLen);
			std::memcpy(WriteBuffer + nsNumLen + 1, nsPayload.c_str(), nsPayloadLen);
			WriteBuffer[nsNumLen + nsPayloadLen + 1] = ',';
		}

		nsLen = nsNumLen + nsPayloadLen + 2;
*/
		//Write((const uint8_t*)"mama\0", 5);
	}

	void UnixStreamSocket::SendLog(char* nsPayload, size_t nsPayloadLen)
	{
		std::printf("unixstreamsocket::sendlog() occured.\n");
		//if (this->closed)return;

		// MS_TRACE_STD();
/*
		size_t nsNumLen;
		size_t nsLen;

		if (nsPayloadLen > MessageMaxSize)
		{
			MS_ERROR_STD("mesage too big");

			return;
		}

		if (nsPayloadLen == 0)
		{
			nsNumLen       = 1;
			WriteBuffer[0] = '0';
			WriteBuffer[1] = ':';
			WriteBuffer[2] = ',';
		}
		else
		{
			nsNumLen = static_cast<size_t>(std::ceil(std::log10(static_cast<double>(nsPayloadLen) + 1)));
			std::sprintf(reinterpret_cast<char*>(WriteBuffer), "%zu:", nsPayloadLen);
			std::memcpy(WriteBuffer + nsNumLen + 1, nsPayload, nsPayloadLen);
			WriteBuffer[nsNumLen + nsPayloadLen + 1] = ',';
		}

		nsLen = nsNumLen + nsPayloadLen + 2;

		Write(WriteBuffer, nsLen);
	}

	void UnixStreamSocket::SendBinary(const uint8_t* nsPayload, size_t nsPayloadLen)
	{
		if (this->closed)
			return;

		size_t nsNumLen;
		size_t nsLen;

		if (nsPayloadLen > MessageMaxSize)
		{
			MS_ERROR_STD("mesage too big");

			return;
		}

		if (nsPayloadLen == 0)
		{
			nsNumLen       = 1;
			WriteBuffer[0] = '0';
			WriteBuffer[1] = ':';
			WriteBuffer[2] = ',';
		}
		else
		{
			nsNumLen = static_cast<size_t>(std::ceil(std::log10(static_cast<double>(nsPayloadLen) + 1)));
			std::sprintf(reinterpret_cast<char*>(WriteBuffer), "%zu:", nsPayloadLen);
			std::memcpy(WriteBuffer + nsNumLen + 1, nsPayload, nsPayloadLen);
			WriteBuffer[nsNumLen + nsPayloadLen + 1] = ',';
		}

		nsLen = nsNumLen + nsPayloadLen + 2;
		*/

		//Write((const uint8_t*)"papa\0", 5);
	}

void UnixStreamSocket::UserOnUnixStreamRead(char*k)
	{
//MS_TRACE_STD();
std::printf("unixstreamsocket::useronunixstreamread() %s\n",k);
		//mChannel::UnixStreamSocket * Channel::Listener;//=new Channel::UnixStreamSocket::Listener();
		//Channel::UnixStreamSocket Listener(4);//{ nullptr };
		//UnixStreamSocket m(4);
		//channel->listener->mfuck();
		//Listener.listener->mfuck();
		
		//this->listener = listener;
		
		//li->mfuck();
		this->listener->mfuck();
		//this->listener->mfuck();
	//Loop::OnChannelRequest(Channel::UnixStreamSocket* channel, Channel::Request* request)
		//Loop::mfuck();
		//return;
		// Be ready to parse more than a single message in a single TCP chunk.
std::string text="{\"mama\":\"papa\"}";
		
	//	while (true){
			//if (IsClosing())return;

//size_t readLen  = this->bufferDataLen - this->msgStart;
char* jsonStart = nullptr;
size_t jsonLen;

			// If here it means that jsonStart points to the beginning of a JSON string
			// with jsonLen bytes length, so recalculate readLen.
			size_t readLen = 8;//reinterpret_cast<const uint8_t*>(jsonStart) - (/*this->buffer + */this->msgStart);
			          //jsonLen + 1;

			Json::Value json;
			std::string jsonParseError;

			//if (this->jsonReader->parse((const char*)0, (const char*)10, (Json::Value*)"k", &jsonParseError))
			if(this->jsonReader->parse(text.c_str(),text.c_str()+text.size(),&json,&jsonParseError))
			{
				std::printf("Here inner parse\n");
				std::cout << json << std::endl;
				Channel::Request* request = nullptr;

				try
				{
					std::printf("request 1\n");
					request = new Channel::Request(this, json);
					std::printf("request2\n");
				}
				catch (const MediaSoupError& error)
				{
					MS_ERROR_STD("discarding wrong Channel request");
				}

				if (request != nullptr)
				{
					std::printf("request is not nullptr\n");
					//request->Reject("Room already exists");
					// Notify the listener.
					//->mfuck();
					//li->OnChannelRequest(this,request);
					this->listener->OnChannelRequest(this, request);
					this->listener->mfuck();

					std::printf("Delete the Request.\n");
					delete request;
				}
			}
			else
			{
				MS_ERROR_STD("JSON parsing error: %s", jsonParseError.c_str());
			}

			// If there is no more space available in the buffer and that is because
			// the latest parsed message filled it, then empty the full buffer.
			/*
			if ((this->msgStart + readLen) == this->bufferSize)
			{
				this->msgStart      = 0;
				this->bufferDataLen = 0;
			}
			// If there is still space in the buffer, set the beginning of the next
			// parsing to the next position after the parsed message.
			else
			{
				this->msgStart += readLen;
			}
*/
			// If there is more data in the buffer after the parsed message
			// then parse again. Otherwise break here and wait for more data.
			//if (this->bufferDataLen > this->msgStart){continue;}

		//	break;
	//	}
		
		
	}

	

	
	
	void UnixStreamSocket::UserOnUnixStreamSocketClosed(bool isClosedByPeer)
	{
		MS_TRACE_STD();

		this->closed = true;

		if (isClosedByPeer)
		{
			// Notify the listener.
			this->listener->OnChannelUnixStreamSocketRemotelyClosed(this);
		}
	}
} // namespace Channel
