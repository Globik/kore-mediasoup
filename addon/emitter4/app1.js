// Linux only it's SOCK_SEQPACKET client
// just quick and dirty example, just a basic concept
const Koa=require('koa');
const PORT=3000;
const WebSocket=require('/home/globik/alikon/node_modules/ws');// see npm ws.js
const render=require('koa-rend'); // npm koa-rend.js
const Router=require('koa-router'); // npm koa-router.js
const serve=require('koa-static');
const unix_sock_path="/home/globik/fuck";//hardcoded ==  I am so sorry for this bad word but I was so tired and angry that night
const EventEmitter=require('events');
const ev=new EventEmitter();
var intervalik;
const intsec=1000*50;
var transi="trans_act_str";
const app=new Koa();
const pub_router=new Router();
const Worker=require('./worker.js');
const w=new Worker();// this is the SOCK_SEQPACKET client for the Janus's phunix transport plugin
const intervaljson={};
intervaljson.janus="keepalive";
intervaljson.transaction=null;
intervaljson.session_id=null;

const psess_ob={};
psess_ob.janus="create";
psess_ob.transaction=transi;
var psess_data=JSON.stringify(psess_ob);
w.on('connect',function conni(v){
console.log("CONNECT",v);
w.psend(psess_data);
});
w.on('erroro',e=>console.log('ERRORO: ',e)) // custom error logic - basic concept
w.on("keepalive_ready",function(s){
console.log("ON_KEEP_ALIVE READY: ", s);
	intervalik=setInterval(function(){
	w.psend(JSON.stringify(intervaljson));
	},1000)
})
w.on('message', msg=>{
console.log('msg came from seq_sock_server Janus webrtc app1: ',msg);
var send_to_client=true;
let r;
try{
r=JSON.parse(msg);
}catch(er){console.log('json err: ',er);}
if(r && r.janus){
if(r.janus=="success_create"){
intervaljson.transaction=r.transaction;
intervaljson.session_id=r.data.id;
w.emit('keepalive_ready','aha');
}else if(r.janus=="pingack"){
//send_to_client=false;
}else{}
}
if(send_to_client==true)ev.emit('from_janus', msg);

})
// TODO remove all Listeners in the end of adventure with Janus
w.create_client(unix_sock_path) // it's a need, without it I dunno how to call these events: connect, erroro, message
//w.psend("pupkin"); // method to send a message to Janus webrtc gateway
app.use(serve(__dirname+'/public'));
render(app,{root:'views', development:true});//development==true is a need for the hot reloader/watcher, 
//as template string literals are always in cash/memory
pub_router.get('/',async ctx=>{
console.log('frontend');
ctx.body=await ctx.render('f',{}) // from views folder, "f.js" file - quick and dirty solution to render some html stuff on server side
})
app.use(pub_router.routes()).use(pub_router.allowedMethods())
app.on('error',(err,ctx)=>{console.log(err.message,ctx.request.url)})

const servak=app.listen(PORT);
const wss=new WebSocket.Server({server:servak})

function noop(){}
function heartbeat(){
this.isAlive=true;
}


wss.on('connection', function websock_community(ws,req){
//ws.isAlive=true;
//ws.on('pong',heartbeat);
console.log("websock client opened!");
function on_janus_msg(m){
console.log('***on_janus_msg*** ');
console.log('ws.readyState: ',ws.readyState);//should be opened.
if(ws.readyState==1)ws.send(m);
}
ev.on('from_janus', on_janus_msg);
	var d={};
	d.type="type";
	d.msg="Hi from server!";
ws.send(JSON.stringify(d));
ws.on('message',function websock_msg(msg){
console.log("msg came from frontend: ", msg);
//send message to janus webRTC gateway
w.psend(msg);
})
ws.on('close',()=>{
console.log('websock client closed!')
ev.removeListener('from_janus', on_janus_msg);
})
})
/*
const interval=setInterval(function ping(){
	wss.clients.forEach(function each(ws){
		if(ws.isAlive===false) return ws.terminate();
		ws.isAlive=false;
		ws.ping(noop);
	});
},30000);
*/

console.log(PORT)



