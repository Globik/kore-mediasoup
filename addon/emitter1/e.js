// /home/globik/kore-mediasoup/addon/emitter/build/Release/binding.node
// the original code from https://github.com/NickNaso/addon-event-emitter
const addon=require("./build/Release/binding.node");
const http=require('http');

const EventEmitter=require('events').EventEmitter;
function nr(some_string_data){
	console.log('On "start" event occured.');
	console.log("should be some string data: ");
	console.log(some_string_data);
}
const emitter=new EventEmitter();
emitter.on('start',nr)
//addon.callEmit(emitter.emit.bind(emitter));
emitter.removeListener("start",nr);
addon.callEmit(function(d){console.log('emmmm ',d);})
addon.create_async("g","d",function(f,a){console.log("some data: ", f,a);})
const server=http.createServer((req,res)=>{})
server.listen(3000,"127.0.0.1",()=>{})