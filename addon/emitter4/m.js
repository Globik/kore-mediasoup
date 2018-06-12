
const Worker=require('./worker.js');
const some_path="/home/globik/fuck";
const str="pupkin";//6 
const str2="HELLO";
const b=Buffer.from(str);
const b2=Buffer.from(str2);

const w=new Worker(some_path);
w.on("connect",d=>{
console.log("out ***on_connect A?:*** ",d);
});

w.on("erroro",function(e){
console.log("out on_err: ",e);
});
w.create_client();
/*
addon.p_init(function(d){console.log('FROM p_init: ',d);});
addon.on_ready(function(d){console.log("READY: ",d);
if(d=="now_readable"){
//read=true;
do_fuck();
}
});
addon.on_msg(function(msg){
console.log("MSG_DATA***!***: ",msg);
})
*/
/*
addon.p_send(b, function(err,d){
if(err) console.log("ERI: ",err);
console.log('FROM p_send: ', d);
console.log("BBBBBBBBBBB: ",b);
						   
})
//setTimeout(function(){
addon.p_send(b2, function(err,d){
console.log('FROM p_send: ',err, d);
if(err) console.log("ERRI2: ",err);
})
*/
//},9);
/*
setTimeout(function(){
addon.p_close(function(d){console.log('FROM p_close: ',d);})
},2000);
*/

/*
function psend(s){
let bri=Buffer.from(s);
if(read){
addon.p_send(bri,function(err,data){
if(err){
console.log("ERR: ",err);
if(err=="what_the_fuck"){
	read=false;
console.log("what the fuck occured");
msgs.push(bri)
}
}
if(data)console.log('data: ',data);
})

}else{
msgs.push(bri);
}
console.log("msgs: ",msgs);
}
*/

//psend(str);
//psend(str2);

//psend(str);
//psend(str2);

/*addon.on_ready("s",function(data){
console.log("on ready occured");
read=true;
do_send();
})
*/
/*
function do_fuck(){
console.log("***DO_FUCK***DO_FUCK***DO_FUCK***DO_FUCK***");
if(msgs.length>0){
let a=msgs.shift();
addon.p_send(a,function(err,data){
if(err){
console.log("ERR444: ",err);
if(err=="what_the_fuck"){
read=false;
console.log("what the fuck occured 444");
msgs.push(bri)
}
}
if(data)console.log('data444444444: ',data);
})

console.log("MSGS_444444444444444444444444444444444444444444: ",msgs);

}
if(msgs.lentgh==0)read=true;
}

*/



/*
var m=[];
m.push("a");
m.push("b");
if(m.length>0){
	console.log(m);
var s=m.shift();
	console.log(m)
	console.log("s: ",s);
	s=m.shift();
	console.log(m);
	console.log("s2: ",s);
	console.log(m.shift())
	console.log(m);
}
*/