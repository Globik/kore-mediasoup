const Koa=require('koa');
const PORT=3000;
const WebSocket=require('/home/globik/alikon/node_modules/ws');
const koaBody=require('koa-body');
const render=require('koa-rend');
const Router=require('koa-router');

const unix_sock_path="/home/globik/fuck"; // I am sorry for that but I was so tired
const EventEmitter=require('events');
const ev=new EventEmitter();

const app=new Koa();
const pub_router=new Router();

const Worker=require('./worker.js');
const w=new Worker();
w.on('connect',(v)=>{console.log("*** Janus Client CONNECTED! ***",v)})
w.on('erroro',e=>console.log('*** Janus ERRORO: ***',e))
w.on('message',msg=>{
//console.log('msg came from seq_sock_server: ',msg);
ev.emit('janus_msg',msg);
})
w.create_client(unix_sock_path)
//w.psend("pupkin");

render(app,{root:'views', development:true});
app.use(koaBody());

pub_router.get('/',async ctx=>{
ctx.body=await ctx.render('seqpacket',{})
})
pub_router.post('/testEvent', async function food(ctx){
	console.log(this.name);
console.log("event_body", __filename,'\n', JSON.stringify(ctx.request.body));
ctx.body={info:"ok"}	
})
app.use(pub_router.routes()).use(pub_router.allowedMethods())
app.on('error',(err,ctx)=>{console.log(err.message,ctx.request.url)})

const servak=app.listen(PORT);
const wss=new WebSocket.Server({server:servak})


wss.on('connection',function websock_community(ws,req){
console.log("websock client opened!");
function on_janus_msg(message){
console.log("*** on_janus_msg! ***");
wsend(message);
}
ev.on('janus_msg',on_janus_msg);

wsend({type:"msg",msg:"Hi from server!"});
ws.on('message', function d_msg(msg){
console.log("msg came: ",msg);
//if(msg.janus){
w.psend(msg);
//}
})
ws.on('close',()=>{
console.log('ws closed')
ev.removeListener('janus_msg', on_janus_msg);
})

function wsend(ob){
let a;
try{a=JSON.stringify(ob);}catch(e){retrun;}	
if(ws && ws.readyState==1)ws.send(a);
}
})

console.log(PORT)



