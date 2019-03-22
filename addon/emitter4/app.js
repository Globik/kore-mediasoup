const Koa=require('koa');
const PORT=3000;
const WebSocket=require('/home/globik/alikon/node_modules/ws');
const koaBody=require('koa-body');
const render=require('koa-rend');
const serve=require('koa-static');
const Router=require('koa-router');

const unix_sock_path="/home/globik/fuck"; // I am sorry for that but I was so tired
const EventEmitter=require('events');
const ev=new EventEmitter();

const app=new Koa();
const pub_router=new Router();

const Worker=require('./worker.js');
const w=new Worker();
w.on('connect', function(v){console.log("*** Janus Client CONNECTED! ***",v)})
w.on('erroro', function(e){console.log('*** Janus ERRORO: ***',e)})
w.on('message', function (msg){
//console.log('***msg came from seq_sock_server: ***\n');
ev.emit('janus_msg',msg);
})
w.create_client(unix_sock_path)
app.use(serve(__dirname+'/public'));
render(app,{root:'views', development:true});
app.use(koaBody());

pub_router.get('/',async ctx=>{
ctx.body=await ctx.render('seqpacket',{})
})
pub_router.post('/testEvent', async function food(ctx){
console.log("event_body", __filename,'\n', JSON.stringify(ctx.request.body));
ctx.body={info:"ok"}	
})
app.use(pub_router.routes()).use(pub_router.allowedMethods())
app.on('error',(err,ctx)=>{console.log(err.message,ctx.request.url)})

const servak=app.listen(PORT);
const wss=new WebSocket.Server({server:servak})



function send_target(trans, obj){
console.log("trg sessId: ", trans);
wss.clients.forEach(function(el){
if(el.trans==trans){
console.log("trg Yes. It's target! ",el.trans, trans);
if(el.readyState===WebSocket.OPEN)el.send(JSON.stringify(obj));	
}	
});
}
function on_janus_msg(msg){
let l;
try{l=JSON.parse(msg);}catch(e){console.log(msg);return;}	
l.type="janus";
if(l.transaction){
let a=l.transaction.split("_");
l.transi=a[1];
send_target(a[0],l);
}
 if(l.janus=="media"){}
}
ev.on('janus_msg',on_janus_msg);

wss.on('connection', function(ws,req){
console.log("websock client opened!");
ws.trans=null;
ws.sid=0;
ws.hid=0;
/*
function on_janus_msg(message){
console.log("*** on_janus_msg! ***");
let ml;
try{ml=JSON.parse(message);if(ml.janus)ml.type="janus";}catch(e){console.log(message);return;}
if(ml.janus=="success"){
if(ml.transaction=="session_create"){
console.log("session create!");
ws.sid=ml.data.id;
}else if(ml.transaction=="session_destroy"){
//ws.sid=0;	
}else{}
}else if(ml.janus=="timeout"){
//ws.sid=0;
}else{}
//send_target(ws.sid,ml);
//if(ws.readyState==1)if(ml)ws.send(JSON.stringify(ml));


}*/
//ev.on('janus_msg',on_janus_msg);

wsend({type:"usid", msg: "Hi from server!"});
ws.on('message', function d_msg(msg){
console.log("msg came: ",msg);
let l;var sens_to_clients=0;
try{
l=JSON.parse(msg);	
}catch(e){return;}
if(l.janus){
w.psend(msg);
send_to_clients=1;
}
if(l.type=="onuser"){
console.log("MSG type: ", l.type);
ws.trans=l.username;
send_to_clients=1;	
}

if(send_to_clients==0){
ws.send(msg);	
}
})
ws.on('close',()=>{
console.log('ws closed')
//ev.removeListener('janus_msg', on_janus_msg);
})

function wsend(ob){
let a;
try{a=JSON.stringify(ob);}catch(e){retrun;}	
if(ws && ws.readyState==1)ws.send(a);
}
})

console.log(PORT)



