const EventEmitter=require('events').EventEmitter;
//var {p_send,p_init,p_close, on_ready}=require("./build/Release/binding.node");
var add=require("./build/Release/binding.node");

//var read=true;
//var msgs=[];
console.log(add.p_send);
console.log(add.p_init);
console.log(add.on_msg);
console.log(add.on_ready);
console.log(add.p_close);
//var duck={clo(){return add.p_send}}
var suka;
class Worker extends EventEmitter
{
	constructor(){
		super();
		this.setMaxListeners(Infinity);
		this.msgs=[];
		this.read=true;
		this.p_send=add.p_send.bind(this);
		this.on_msg=add.on_msg.bind(this);
		this.process=process;
		this.p_init=add.p_init.bind(this);
		this.on_ready=add.on_ready.bind(this);
		this.p_close=add.p_close.bind(this);
		suka=this.p_close;
		//this.r=duck.clo().bind(this);
		//this.init=this.add.p_init;
		//this.on_msg=on_msg;
		//this.ad=addon;
		//this.un=unix_sock;
		//this.emit('connect','suka');
		//this.emit.bind(this,'connect');
		//this.create_client(this.un);
		//this.emit.bind(this,'connect');
		//this.on('connect',d=>{console.log('WITHIN CLASS dura:',d)})
		//this.on_messaga();
}
create_client(unix_sock){
console.log("STRING",unix_sock);
	//duck.init('k',y=>{console.log('y: ',y)});
	//this.emit.bind(this,'erroro','l');
	//this.su();
	//this.emit('connect','k')
	//p_init(unix_sock,(err,d)=>{console.log(err,d)})
	//var p=add.p_init.bind(this);
//this.p_init
this.p_init(unix_sock,(err,d,m)=>{
//console.log('iiiiiiiii',err,d)
if(err){this.emit('erroro',err);this.read=false;return;}
console.log('addon1: ',d);
this.emit('connect','CONNECTED!');
this.ready_parat();
this.on_messaga();
//this.process.on("EXIT",()=>{console.log("SOME NODEJS EXIT")});
	
})
//var p2=add.on_ready.call(this.add);
//	add.on_ready
/*
	add.on_ready(msg=>{
	i++;
	console.log("messaga came",msg);
	this.emit('message', msg);
	})
	*/
//})
	

return this;

}

do_fuck(){
console.log("***DO_FUCK***DO_FUCK***DO_FUCK***DO_FUCK***");
if(this.msgs.length>0){
let a=this.msgs.shift();
//add
	this.p_send(a,(err,data)=>{
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
	//let p2=add.on_ready.bind(this);
//add.on_ready
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
	console.log("messaga came",msg);
	this.emit('message', msg);
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
//let fuck=add.p_close.bind(add);
//this.p_close
if(suka)suka(function(d){console.log("CLOSING!: \n",d);});
//w.close();
})


module.exports=Worker;