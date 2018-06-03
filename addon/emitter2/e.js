// /home/globik/kore-mediasoup/addon/emitter/build/Release/binding.node
// the original code from https://github.com/NickNaso/addon-event-emitter


const addon=require("./build/Release/binding.node");
//var utils=require('util');
//const http=require('http'); // it sucks vholostuju segm faults

//const EventEmitter=require('events').EventEmitter;
function nr(some_string_data){
	console.log('On "start" event occured.');
	console.log("should be some string data: ");
	console.log(some_string_data);
}
//const emitter=new EventEmitter();
//emitter.on('start',nr)
//addon.callEmit(emitter.emit.bind(emitter));
//emitter.removeListener("start",nr);
addon.callEmit(function(d){console.log('FROM ADDON: ',d);})
addon.create_async("g","d",function(f,a){console.log("SOME DATA: ", f,a);})
//const server=http.createServer((req,res)=>{});server.listen(3000,"127.0.0.1",()=>{});
process.on('SIGINT',function(e){

console.log('node  sigint');
process.exit(0);

});
process.on('SIGTERM',function(e){
		   console.log("node term");
		   prosess.exit(0);
//process.kill(process.pid,'');
		   })