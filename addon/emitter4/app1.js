// Linux only it's SOCK_SEQPACKET client
// just quick and dirty example, just a basic concept
const Koa=require('koa');
const PORT=3000;
const WebSocket=require('/home/globik/alikon/node_modules/ws');
const koaBody=require('koa-body');
const render=require('koa-rend');
const Router=require('koa-router');
const serve=require('koa-static');
const unix_sock_path="/home/globik/fuck";
const EventEmitter=require('events');
const ev=new EventEmitter();
var intervalik;
const intsec=1000*50;
var transi="trans_act_str";
const app=new Koa();
const pub_router=new Router();
const Worker=require('./worker.js');
const w=new Worker();// this is the SOCK_SEQPACKET
//const intervaljson={};
//intervaljson.janus="ping";//"keepalive";
//intervaljson.transaction="ping";//null;
//intervaljson.session_id=null;


w.on('connect',function(v){console.log("CONNECT",v);});
w.on('erroro',function(e){console.log('ERRORO: ',e)});

/*
w.on("keepalive_ready", function(s){
console.log("ON_KEEP_ALIVE READY: ", s);
intervalik=setInterval(function dint(){
console.log("interval?");
let v=JSON.stringify(intervaljson);
console.log(v);
w.psend(v);
},intsec);
})
*/ 
w.on('message', function(msg){
console.log('msg came from seq_sock_server Janus webrtc app1: ',msg);
var send_to_client=true;
if(send_to_client==true){console.log("*** SENT TO WS***");ev.emit('from_janus', msg);}

})
w.create_client(unix_sock_path) 
app.use(serve(__dirname+'/public'));
render(app,{root:'views', development:true});
app.use(koaBody());
pub_router.get('/',async ctx=>{
console.log('frontend');
ctx.body=await ctx.render('f',{});
})
pub_router.post('/testEvent', async ctx=>{
console.log("EVENT_BODY", __filename,'\n', JSON.stringify(ctx.request.body));
ctx.body={info: "ok"};
})
app.use(pub_router.routes()).use(pub_router.allowedMethods())
app.on('error',(err,ctx)=>{console.log(err.message,ctx.request.url)})

const servak=app.listen(PORT);
const wss=new WebSocket.Server({server:servak})

function noop(){}
function heartbeat(){
this.isAlive=true;
}





wss.on('connection', function(ws,req){
console.log("websock client opened!");

function on_janus_msg(m){
console.log('***on_janus_msg*** ');
let ml;
try{ml=JSON.parse(m);if(ml.janus)ml.type="janus";}catch(e){console.log(m);return;}
if(ws.readyState==1)if(ml)ws.send(JSON.stringify(ml));
}

ev.on('from_janus', on_janus_msg);

/*let d={};
d.type="hello_user";
d.msg="Hi from server!";
ws.send(JSON.stringify(d));
*/
ws.on('message',function(msg){
console.log("msg came from frontend: ", msg);
let l;
var send_to_clients=0;
try{
l=JSON.parse(msg);	
}catch(e){return;}
if(l.janus){
w.psend(msg);
send_to_clients=1;
}

if(send_to_clients==0){
ws.send(msg);	
}
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

console.log("soll on port: ", PORT)
// sudo leafpad /usr/local/etc/janus/janus.eventhandler.sampleevh.cfg
