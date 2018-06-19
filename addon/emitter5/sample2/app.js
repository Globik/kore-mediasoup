const Koa=require('koa');
const PORT=3000;
const WebSocket=require('/home/globik/alikon/node_modules/ws');// see npm ws.js
const render=require('koa-rend'); // npm koa-rend.js
const Router=require('koa-router'); // npm koa-router.js
const serve=require('koa-static');
const addon=require("./build/Release/binding.node");
const EventEmitter=require('events');
let p_create=addon.p_create.bind(this);
p_create(function(d){
console.log("[app.js]: Here the message from addon on thread created: ", d);
})
const ev=new EventEmitter();

const app=new Koa()
const pub_router=new Router()

app.use(serve(__dirname+'/public'))
render(app,{root:'views', development:true})
pub_router.get('/',async ctx=>{
console.log('frontend');
ctx.body=await ctx.render('frontend',{title:"echo",username:"Bob"}) 
})
app.use(pub_router.routes()).use(pub_router.allowedMethods())
app.on('error',(err,ctx)=>{console.log(err.message,ctx.request.url)})

const servak=app.listen(PORT);
const wss=new WebSocket.Server({server:servak})
//var ew=addon.p_create.bind(this);

var mr=addon.on_msg.bind(this);
mr(function(da){
console.log('[s.js]: from addon on_msg (d): ',da);
ev.emit("from_janus",da);
})


wss.on('connection',function(ws,req){
console.log("[app.js]: Websocket connected!");
function on_from_janus(msg_janus){
if(ws.readyState==1)ws.send(msg_janus);
}
ev.on('from_janus', on_from_janus);
ws.on('message', function(msg){
//send to janus
var td=addon.p_send.bind(this);
td(Buffer.from(msg),function(err,data){
console.log('[app.js]: from addon p_send: ',err,data);
})
})
ws.on('close', function(){
console.log("[app.js]: Websocket client closed!");
ev.removeListener('from_janus',on_from_janus);
})
})

setTimeout(function(){
// this is ok
//let k=addon.p_close.bind(this);
//k(function(d){console.log('[app.js]: from addon p_close: ',d)})
},2000)

process.on("exit",function(){
console.log("[app.js]: EXIT NOW!*********************************************");
//setTimeout(function(){
//let k=addon.p_close.bind(this);
//k(function(d){console.log('[app.js]: from addon p_close: ',d)})
//exit(0);
//},2000)
//	nothing to do if there in addon on sigint signal
})

process.on('SIGINT',function(){
	//let k=addon.p_close.bind(this);
	console.log('sigineger*******************************')
//k(function(d){console.log('[app.js]: from addon p_close: ',d)})
	//exit(0);
//	nothing to do if there in addon on sigint signal
})


console.log(PORT)