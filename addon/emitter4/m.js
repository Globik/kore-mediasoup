
const Worker=require('./worker.js');
const some_path="/home/globik/fuck";
const str="pupkin";//6 
const str2="HELLO";
const b=Buffer.from(str);
const b2=Buffer.from(str2);
function dura(some_path){
const w=new Worker(some_path);
//w.create_client(some_path);
w.on("connect",d=>{
console.log("out ***on_connect A?:*** ",d);
w.emit("nina","nina_data");
});
//w.create_client(some_path);
w.on("erroro",function(e){
console.log("out on_err: ",e);
});
//w.create_client(some_path);
//w.ready_parat();
//w.psend(str);
//w.psend(b2);
//w.psend(b);
//w.psend(b2);
	/*
w.on('message',msg=>{
console.log('***MESSAGE***: ',msg);
})
*/
w.create_client(some_path);
return {client:w,send(s){return this.client.psend(s);},on_connect(c){w.on('nina',d=>{console.log('c7777777777777777777777777777onn');c(d)})},
	  onm(cb){this.client.on('message',g=>{cb(g)})}
	   }
}
let d=dura(some_path);
d.on_connect(p=>{console.log("***NjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjINA***",p)})
d.onm(j=>{console.log("***PPPPPPPPPPPPPPPPPPPPPPP***: ",j);})
//d.on("connect",(d)=>{console.log("coooooooooo")});
//d.send(str);

/*
setTimeout(()=>{
w.psend(b2);
},1000)
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
//read=true;
do_fuck();
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