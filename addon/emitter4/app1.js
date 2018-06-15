// Linux only it's SOCK_SEQPACKET client
// just quick and dirty example, just a basic concept
const Koa=require('koa');
const PORT=3000;
const WebSocket=require('/home/globik/alikon/node_modules/ws');// see npm ws.js
const render=require('koa-rend'); // npm koa-rend.js
const Router=require('koa-router'); // npm koa-router.js
const unix_sock_path="/home/globik/fuck";//hardcoded ==  I am so sorry for this bad word but I was so tired and angry that night
const EventEmitter=require('events');
const ev=new EventEmitter();

const app=new Koa();
const pub_router=new Router();
const Worker=require('./worker.js');
const w=new Worker();// this is the SOCK_SEQPACKET client for the Janus's phunix transport plugin
w.on('connect',(v)=>{console.log("CONNECT",v)})
w.on('erroro',e=>console.log('ERRORO: ',e)) // custom error logic - basic concept
w.on('message', msg=>{
console.log('msg came from seq_sock_server Janus webrtc app1: ');
ev.emit('from_janus', msg);
})
// TODO remove all Listeners in the end of adventure with Janus
w.create_client(unix_sock_path) // it's a need, without it I dunno how to call these events: connect, erroro, message
//w.psend("pupkin"); // method to send a message to Janus webrtc gateway

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

wss.on('connection', function websock_community(ws,req){
console.log("websock client opened!");
function on_janus_msg(m){
console.log('***on_janus_msg*** ');
console.log('ws.readyState: ',ws.readyState);//should be opened.
if(ws.readyState==1)ws.send(m);
}
ev.on('from_janus', on_janus_msg);
ws.send("Hi from server!");
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

console.log(PORT)



