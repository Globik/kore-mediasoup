const EventEmitter=require('events').EventEmitter;
const addon=require("./build/Release/binding.node");

//var read=true;
//var msgs=[];
class Worker extends EventEmitter
{
	constructor(){
		super();
		this.setMaxListeners(Infinity);
		this.msgs=[];
		this.read=true;
		//this.on('connect',d=>{console.log('WITHIN CLASS dura:',d)})
		//this.on_messaga();
}
create_client(unix_sock){
console.log("STRING",unix_sock);
addon.p_init(unix_sock,(err,d,m)=>{
//console.log(err,d,m)
if(err){this.emit('erroro',err);return;}
console.log('addon1: ',d);
this.emit('connect','CONNECTED!');
this.ready_parat();
this.on_messaga();
})
}

do_fuck(){
console.log("***DO_FUCK***DO_FUCK***DO_FUCK***DO_FUCK***");
if(this.msgs.length>0){
let a=this.msgs.shift();
addon.p_send(a,(err,data)=>{
if(err){
console.log("ERR444: ",err);
if(err=="what_the_fuck"){
this.read=false;
console.log("what the fuck occured 444");
this.msgs.push(a);
}
}
if(data)console.log('data444444444: ',data);
})

console.log("MSGS_444444444444444444444444444444444444444444: ",this.msgs);
}
if(this.msgs.lentgh==0)this.read=true;

}
ready_parat(){
addon.on_ready(d=>{
this.read=true;
console.log("READY: ", d);
this.do_fuck();
});
}
	
	on_messaga(){
	let i=0;
	console.log("ON_MESSSSSSSSSSSSSSSSSSAGA");
	addon.on_msg(msg=>{
	i++;
	console.log("messaga came",msg);
	this.emit('message',msg);
	});
	
	}
	
psend(s){
let bri=Buffer.from(s);
if(this.read){
addon.p_send(bri,(err,data)=>{
if(err){
console.log("ERR: ",err);
if(err=="what_the_fuck"){
	this.read=false;
console.log("what the fuck occured");
this.msgs.push(bri)
}
}
if(data)console.log('data: ',data);
})

}else{
this.msgs.push(bri);
}
console.log("this.msgs: ",this.msgs);
}

}

process.on("SIGINT",function(){
addon.p_close(function(d){console.log("CLOSING\n");});
//process.exit(0);
});


module.exports=Worker;