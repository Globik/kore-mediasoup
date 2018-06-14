const Koa=require('koa');
const PORT=3000;
const WebSocket=require('/home/globik/alikon/node_modules/ws');
const render=require('koa-rend');
const Router=require('koa-router');
//const add=require("./build/Release/binding.node");
const some_path="/home/globik/fuck";
//const pub_router=require('./routes/pub_roter.js');
const app=new Koa();
const pub_router=new Router();
const Worker=require('./worker.js');
const w=new Worker();
w.on('connect',(v)=>{console.log(v)})
w.on('erroro',e=>console.log('ERRORO: ',e))
w.on('message',msg=>{console.log('msg came from seq_sock_server: ',msg)})
w.create_client(some_path)
w.psend("pupkin");
/*
console.log('p_init ',add.p_init);
console.log('p_close ',add.p_close);
console.log('on_msg ',add.on_msg);
console.log('p_send ',add.p_send);
console.log('on_ready ',add.on_ready);
*/
render(app,{root:'views',development:true});
pub_router.get('/',async ctx=>{
ctx.body=await ctx.render('seqpacket',{})
})
app.use(pub_router.routes()).use(pub_router.allowedMethods())
app.on('error',(err,ctx)=>{console.log(err.message,ctx.request.url)})

const servak=app.listen(PORT);
const wss=new WebSocket.Server({server:servak})
//process.on('exit',()=>{
//console.log("\nNODE.JS EXIT")
//w.close();
//})
wss.on('connection',(ws,req)=>{
console.log("websock client opened!");
ws.send("Hi from server!");
ws.on('message',msg=>{
console.log("msg came: ",msg)
})
ws.on('close',()=>{console.log('ws closed')})
})
//w.create_client(some_path)
console.log(PORT)



