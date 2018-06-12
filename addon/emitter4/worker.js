const EventEmitter=require('events').EventEmitter;
const addon=require("./build/Release/binding.node");

var read=true;
var msgs=[];
class Worker extends EventEmitter
{
	constructor(str){
		console.log('string: ',str);
		super();
		this.setMaxListeners(Infinity);
		//this.on('connect',d=>{console.log('WITHIN CLASS dura:',d)})
}
create_client(){
addon.p_init('s',(err,d,m)=>{
//console.log(err,d,m)
if(err){this.emit('erroro',err);return;}
console.log('addon1: ',d);
this.emit('connect','CONNECTED!');
})
}
	
}

process.on("SIGINT",function(){
addon.p_close(function(d){console.log("CLOSING\n");});
//process.exit(0);
});


module.exports=Worker;