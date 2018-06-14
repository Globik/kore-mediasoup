const EventEmitter=require('events').EventEmitter;
const add=require("./build/Release/binding.node");
/*
console.log(add.p_send);
console.log(add.p_init);
console.log(add.on_msg);
console.log(add.on_ready);
console.log(add.p_close);
*/
let suka;
class Worker extends EventEmitter
{
	constructor(){
		super();
		this.setMaxListeners(Infinity);
		this.msgs=[];
		this.read=true;
		this.p_send=add.p_send.bind(this);
		this.on_msg=add.on_msg.bind(this);

		this.p_init=add.p_init.bind(this);
		this.on_ready=add.on_ready.bind(this);
		this.p_close=add.p_close.bind(this);
		suka=this.p_close;
		
}
create_client(unix_sock){
//console.log("STRING",unix_sock);
	
this.p_init(unix_sock,(err,d)=>{
//console.log('iiiiiiiii',err,d)
if(err){this.emit('erroro',err);this.read=false;return;}
//console.log('addon1: ',d);

this.ready_parat();
this.on_messaga();
this.emit('connect','CONNECTED! '+d);
})

}

do_fuck(){

if(this.msgs.length>0){
console.log("Trying dequeque the messages",this.msgs.length);
let a=this.msgs.shift();
this.p_send(a,(err,data)=>{
if(err){
console.log("ERR in do_fuck() in worker.js: ",err);
if(err=="what_the_fuck"){
this.read=false;
console.log("what the fuck occured 444");
this.msgs.push(a);
}
}
if(data)console.log('data444444444: ',data);
})

console.log("[]: ",this.msgs);
}
if(this.msgs.lentgh==0)this.read=true;

}
	
ready_parat(){
this.on_ready(d=>{
this.read=true;
console.log("READY: ", d);
this.do_fuck();
});
console.log("***PARAT***");
}
on_messaga(){
let i=0;
console.log("ON_MESSSSSSSSSSSSSSSSSSAGA");
this.on_msg(msg=>{
i++;
//console.log("messaga came",msg);
if(i>1)this.emit('message', msg);
});
}
psend(s){
let bri=Buffer.from(s);
if(this.read){
this.p_send(bri,(err,data)=>{
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
close(){
this.p_close(d=>{console.log("SEQ CLOSING: ",d);});
}


}
process.on("SIGINT",function(){
add.p_close(function(d){console.log("CLOSING\n");});
//process.exit(0);
});

process.on('exit',()=>{
console.log("\nNODE.JS EXIT fuckerrr!")
if(suka)suka(function(d){console.log("CLOSING!: \n",d);});
})
module.exports=Worker;