Trying to mimic the mediasoup stuff. To implement the two-communication pipe based on uv_callback.c Trying to remove UnixStreamSocket handler
class.

## So far so good

```
here class init
rc to cpp init: 0
rc from_cpp init: 0
rc stop_w init: 0
version:  1.19.3-dev
Parse all RTP capabilities.
rc fire 0
Set us as Channel's listener.
unixstreamsocket::setlistener()
loop::mfuck
loop::mfuck
starting libuv loop
Loop was allocated?
HERE AND HERE ON_TO_CPP occured: {"mama":"papa"}
loop::mfuck
unixstreamsocket::useronunixstreamread() {"mama":"papa"}
loop::mfuck
Here inner parse
{
	"mama" : "papa"
}
request 1
here must be within request::request
{
	"mama" : "papa"
}
unixstreamsocket::sendlog() occured.
[id:unset] Channel::UnixStreamSocket::UserOnUnixStreamRead() | discarding wrong Channel request
^Csignal INT received, exiting
loop::close() occured
CLOSE SIGNALSHANDLER DESTROY
rc fire from_cpp: 0
What the fuck in destractor in unixstreamsocket?jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
on_from_cpp occurred!!! => exit
EXIT!!!
libuv loop ended
SUUUUUUUUUUUUUUUUUUUKA!
loop destructer occured llllllllllllllllllllllllloooop destructure
destroy()
Loop was destroyd?
SUCCESS: And exit with success status.

```
