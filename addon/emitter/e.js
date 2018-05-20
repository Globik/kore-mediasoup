// /home/globik/kore-mediasoup/addon/emitter/build/Release/binding.node
// the original code from https://github.com/NickNaso/addon-event-emitter
const addon=require("./build/Release/binding.node");
const EventEmitter=require('events').EventEmitter;
const emitter=new EventEmitter();
emitter.on('start',function(some_string_data){
	console.log('On "start" event occured.');
	console.log("should be some string data: ");
	console.log(some_string_data);
})
addon.callEmit(emitter.emit.bind(emitter));