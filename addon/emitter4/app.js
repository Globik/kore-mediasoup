const Koa=require('koa');
const PORT=3000;
const WebSocket=require('/home/globik/alikon/node_modules/ws');
const render=require('koa-rend');
const Router=require('koa-router');
const some_path="/home/globik/fuck";
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
ev.emit('suka',msg);
})
w.create_client(some_path)
//w.psend("pupkin");

render(app,{root:'views', development:true});
pub_router.get('/',async ctx=>{
ctx.body=await ctx.render('seqpacket',{})
})
app.use(pub_router.routes()).use(pub_router.allowedMethods())
app.on('error',(err,ctx)=>{console.log(err.message,ctx.request.url)})

const servak=app.listen(PORT);
const wss=new WebSocket.Server({server:servak})
function babki(ws,bool){
console.log("ON SUKA OCCURED");
function buka(m){
//console.log("ON BSUUUUUUUUKA", m);
ws.send(m);
}
if(bool){
ev.on('suka',buka)
}else{ev.removeListener('suka',buka)}
}

wss.on('connection',(ws,req)=>{
console.log("websock client opened!");
//ev.on('suka',babki);
babki(ws,true)
ws.send("Hi from server!");
ws.on('message',msg=>{
console.log("msg came: ",msg)
w.psend(msg);
})
ws.on('close',()=>{
console.log('ws closed')
babki(ws,false);
})
})

console.log(PORT)



