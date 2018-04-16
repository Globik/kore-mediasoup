/**
 * NOTE: This code cannot log to the Channel since this is the base code of the
 * Channel.
 */

#define MS_CLASS "UnixStreamSocket"
// #define MS_LOG_DEV

#include "handles/UnixStreamSocket.hpp"
#include "deplibuv.hpp"
#include "Logger.hpp"
#include "MediaSoupError.hpp"
#include <cstdlib> // std::malloc(), std::free()
#include <cstring> // std::memcpy()

uv_callback_t from_cpp;

/* Static methods for UV callbacks. */

inline static void onAlloc(uv_handle_t* handle, size_t suggestedSize, uv_buf_t* buf)
{
	static_cast<UnixStreamSocket*>(handle->data)->OnUvReadAlloc(suggestedSize, buf);
}

inline static void onRead(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
{
	static_cast<UnixStreamSocket*>(handle->data)->OnUvRead(nread, buf);
}

inline static void onWrite(uv_write_t* req, int status)
{
	auto* writeData          = static_cast<UnixStreamSocket::UvWriteData*>(req->data);
	UnixStreamSocket* socket = writeData->socket;

	// Delete the UvWriteData struct (which includes the uv_req_t and the store char[]).
	std::free(writeData);

	// Just notify the UnixStreamSocket when error.
	if (status != 0)
		socket->OnUvWriteError(status);
}

inline static void onShutdown(uv_shutdown_t* req, int status)
{
	static_cast<UnixStreamSocket*>(req->data)->OnUvShutdown(req, status);
}

inline static void onClose(uv_handle_t* handle)
{
	static_cast<UnixStreamSocket*>(handle->data)->OnUvClosed();
}

inline static void onErrorClose(uv_handle_t* handle)
{
	delete handle;
}

/* Instance methods. */
//void*UnixStreamSocket::

 void*UnixStreamSocket::on_to_cpp(uv_callback_t*callback,void*data){
std::printf("ON_TO_CPP occured: %s\n",(char*)data);
//UnixStreamSocket::dt=(char*)data;
//UnixStreamSocketUserOnUnixStreamRead();
	// void * m=nullptr;
	//const uv_buf_t*ml=(uv_buf_t*)data;
//	static_cast<UnixStreamSocket*>(m)->OnUvRead(17,ml);
	//((UnixStreamSocket*)m)->fuck(12);
	 
	//UnixStreamSocket()->b=1;
	// struct fucker*ml;
	// int s=ml->a;
	// std::printf("%d\n",s);
	 //int su=((UnixStreamSocket*)m)->mina->a;
	 //int s=this->mina->a;
return nullptr;
 }

	
//return nullptr;

inline void UnixStreamSocket::fuck(int a){
std::printf("an int %d\n", a);
std::printf("bb: %d\n",b);
}
UnixStreamSocket::UnixStreamSocket(int fd, size_t bufferSize) : bufferSize(bufferSize)
{
	MS_TRACE_STD();
std::printf("UnixStreamSocket::UnixStreamSocket(int fd, size_t bufferSize) : bufferSize(bufferSize)\n");
	int err;
b=9;
	this->mina=new fucker;
	this->mina->a=3;
	//this->uvHandle       = new uv_pipe_t;
	//this->uvHandle->data = (void*)this;
	//this->b=4;
	//static
int rc=uv_callback_init(deplibuv::getloop(), &this->to_cpp, static_cast<uv_callback_func>(UnixStreamSocket::on_to_cpp), UV_DEFAULT);
	//non static
	//static_cast<UnixStreamSocket*>(req->data)->OnUvShutdown(req, status);

/*cannot convert ‘UnixStreamSocket::on_to_cpp’ 
from type ‘void* (UnixStreamSocket::)(uv_callback_t*, void*) 
{aka void* (UnixStreamSocket::)(uv_callback_s*, void*)}’ 
to type ‘uv_callback_func 
{aka void* (*)(uv_callback_s*, void*)}’
*/
//int rc=uv_callback_init(deplibuv::getloop(), &this->to_cpp, on_to_cpp, UV_DEFAULT);
//std::printf("rc to_cpp init: %d\n",rc);
	
	//int rc=uv_callback_init(deplibuv::getloop(),&from_cpp, on_from_cpp, UV_DEFAULT);
	//std::cout << "in deplibuv.cpp rc2: " << rc << std::endl;
/*
	err = uv_pipe_init(DepLibUV::GetLoop(), this->uvHandle, 0);
	if (err != 0)
	{
		delete this->uvHandle;
		this->uvHandle = nullptr;

		MS_THROW_ERROR_STD("uv_pipe_init() failed: %s", uv_strerror(err));
	}

	err = uv_pipe_open(this->uvHandle, fd);
	if (err != 0)
	{
		uv_close(reinterpret_cast<uv_handle_t*>(this->uvHandle), static_cast<uv_close_cb>(onErrorClose));

		MS_THROW_ERROR_STD("uv_pipe_open() failed: %s", uv_strerror(err));
	}
*/
	// Start reading.
	/*
	err = uv_read_start(
	    reinterpret_cast<uv_stream_t*>(this->uvHandle),
	    static_cast<uv_alloc_cb>(onAlloc),
	    static_cast<uv_read_cb>(onRead));
	if (err != 0)
	{
		uv_close(reinterpret_cast<uv_handle_t*>(this->uvHandle), static_cast<uv_close_cb>(onErrorClose));

		MS_THROW_ERROR_STD("uv_read_start() failed: %s", uv_strerror(err));
	}
*/
	// NOTE: Don't allocate the buffer here. Instead wait for the first uv_alloc_cb().
}

UnixStreamSocket::~UnixStreamSocket()
{
	MS_TRACE_STD();
std::printf("deleting the buffer and uvhandle\n");
	delete this->uvHandle;
	delete[] this->buffer;
}

void UnixStreamSocket::Destroy()
{
	MS_TRACE_STD();
std::printf("unixstreamsocket::destroy()\n");
	if (this->isClosing)
		return;

	int err;

	this->isClosing = true;
/*
	// Don't read more.
	err = uv_read_stop(reinterpret_cast<uv_stream_t*>(this->uvHandle));
	if (err != 0)
		MS_ABORT("uv_read_stop() failed: %s", uv_strerror(err));

	// If there is no error and the peer didn't close its pipe side then close gracefully.
	if (!this->hasError && !this->isClosedByPeer)
	{
		// Use uv_shutdown() so pending data to be written will be sent to the peer before closing.
		auto req  = new uv_shutdown_t;
		req->data = (void*)this;
		err       = uv_shutdown(
        req, reinterpret_cast<uv_stream_t*>(this->uvHandle), static_cast<uv_shutdown_cb>(onShutdown));
		if (err != 0)
			MS_ABORT("uv_shutdown() failed: %s", uv_strerror(err));
	}
	// Otherwise directly close the socket.
	else
	{
		uv_close(reinterpret_cast<uv_handle_t*>(this->uvHandle), static_cast<uv_close_cb>(onClose));
	}
	*/
}

void UnixStreamSocket::Write(const uint8_t* data, size_t len)
{
	std::printf("unixstreamsocket::write(const uint8_t*data,size_t len)\n");
	if (this->isClosing)
		return;

	if (len == 0)
		return;
	std::cout << "write data len occured in handle_unixstreamsocket.cpp." << std::endl;
/*
	uv_buf_t buffer{};
	int written;
	int err;

	// First try uv_try_write(). In case it can not directly send all the given data
	// then build a uv_req_t and use uv_write().

	buffer  = uv_buf_init(reinterpret_cast<char*>(const_cast<uint8_t*>(data)), len);
	written = uv_try_write(reinterpret_cast<uv_stream_t*>(this->uvHandle), &buffer, 1);

	// All the data was written. Done.
	if (written == static_cast<int>(len))
	{
		return;
	}
	// Cannot write any data at first time. Use uv_write().
	if (written == UV_EAGAIN || written == UV_ENOSYS)
	{
		// Set written to 0 so pendingLen can be properly calculated.
		written = 0;
	}
	// Error. Should not happen.
	else if (written < 0)
	{
		MS_ERROR_STD("uv_try_write() failed, closing the socket: %s", uv_strerror(written));

		Destroy();

		return;
	}

	size_t pendingLen = len - written;

	// Allocate a special UvWriteData struct pointer.
	auto* writeData = static_cast<UvWriteData*>(std::malloc(sizeof(UvWriteData) + pendingLen));

	writeData->socket = this;
	std::memcpy(writeData->store, data + written, pendingLen);
	writeData->req.data = (void*)writeData;

	buffer = uv_buf_init(reinterpret_cast<char*>(writeData->store), pendingLen);

	err = uv_write(
	    &writeData->req,
	    reinterpret_cast<uv_stream_t*>(this->uvHandle),
	    &buffer,
	    1,
	    static_cast<uv_write_cb>(onWrite));
	if (err != 0)
		MS_ABORT("uv_write() failed: %s", uv_strerror(err));
	*/
}

inline void UnixStreamSocket::OnUvReadAlloc(size_t /*suggestedSize*/, uv_buf_t* buf)
{
	MS_TRACE_STD();

	// If this is the first call to onUvReadAlloc() then allocate the receiving buffer now.
	if (this->buffer == nullptr)
		this->buffer = new uint8_t[this->bufferSize];

	// Tell UV to write after the last data byte in the buffer.
	buf->base = reinterpret_cast<char*>(this->buffer + this->bufferDataLen);
	// Give UV all the remaining space in the buffer.
	if (this->bufferSize > this->bufferDataLen)
	{
		buf->len = this->bufferSize - this->bufferDataLen;
	}
	else
	{
		buf->len = 0;

		MS_ERROR_STD("no available space in the buffer");
	}
}

inline void UnixStreamSocket::OnUvRead(ssize_t nread, const uv_buf_t*)
{
	std::printf("UnixStreamSocket::OnUvRead(ssize_t nread, const uv_buf_t*) ??\n");
	//std::printf("data: %zu and %s\n",nread,(char*)buf);

	//this->dt=(char*)buf;
	//this->bufferDataLen += static_cast<size_t>(nread);
	//UnixStreamSocket::b=3;
	//UserOnUnixStreamRead();
	/*
	MS_TRACE_STD();

	if (nread == 0)
		return;

	// Data received.
	if (nread > 0)
	{
		// Update the buffer data length.
		this->bufferDataLen += static_cast<size_t>(nread);

		// Notify the subclass.
		UserOnUnixStreamRead();
	}
	// Peer disconneted.
	else if (nread == UV_EOF || nread == UV_ECONNRESET)
	{
		this->isClosedByPeer = true;

		// Close local side of the pipe.
		Destroy();
	}
	// Some error.
	else
	{
		MS_ERROR_STD("read error, closing the pipe: %s", uv_strerror(nread));

		this->hasError = true;

		// Close the socket.
		Destroy();
	}
	*/
}

inline void UnixStreamSocket::OnUvWriteError(int error)
{
	/*
	MS_TRACE_STD();

	if (this->isClosing)
		return;

	if (error != UV_EPIPE && error != UV_ENOTCONN)
		this->hasError = true;

	MS_ERROR_STD("write error, closing the pipe: %s", uv_strerror(error));

	Destroy();
	*/
}

inline void UnixStreamSocket::OnUvShutdown(uv_shutdown_t* req, int status)
{
	/*
	MS_TRACE_STD();

	delete req;

	if (status != 0)
	{
		MS_ERROR_STD("shutdown error: %s", uv_strerror(status));
	}

	// Now do close the handle.
	uv_close(reinterpret_cast<uv_handle_t*>(this->uvHandle), static_cast<uv_close_cb>(onClose));
	*/
}

inline void UnixStreamSocket::OnUvClosed()
{
	MS_TRACE_STD();

	// Notify the subclass.
	UserOnUnixStreamSocketClosed(this->isClosedByPeer);

	// And delete this.
	delete this;
}
