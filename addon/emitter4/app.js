const Koa=require('koa');
const PORT=3000;
const WebSocket=require('/home/globik/alikon/node_modules/ws');
const render=require('koa-rend');
const Router=require('koa-router');
const unix_sock_path="/home/globik/fuck"; // I am sorry for that but I was so tired
const EventEmitter=require('events');
const ev=new EventEmitter();

const app=new Koa();
const pub_router=new Router();
const Worker=require('./worker.js');
const w=new Worker();
w.on('connect',(v)=>{console.log("CONNECT",v)})
w.on('erroro',e=>console.log('ERRORO: ',e))
w.on('message',msg=>{
//console.log('msg came from seq_sock_server: ',msg);
ev.emit('janus_msg',msg);
})
w.create_client(unix_sock_path)
//w.psend("pupkin");

render(app,{root:'views', development:true});
pub_router.get('/',async ctx=>{
ctx.body=await ctx.render('seqpacket',{})
})
app.use(pub_router.routes()).use(pub_router.allowedMethods())
app.on('error',(err,ctx)=>{console.log(err.message,ctx.request.url)})

const servak=app.listen(PORT);
const wss=new WebSocket.Server({server:servak})


wss.on('connection',function websock_community(ws,req){
console.log("websock client opened!");
function on_janus_msg(message){
if(ws.readyState==1)ws.send(message);
}
ev.on('janus_msg',on_janus_msg);

ws.send("Hi from server!");
ws.on('message',msg=>{
console.log("msg came: ",msg)
w.psend(msg);
})
ws.on('close',()=>{
console.log('ws closed')
ev.removeListener('janus_msg', on_janus_msg);
})
})

console.log(PORT)



