const Koa=require('koa');
const PORT=3000;
//const WebSocket=require('/home/globik/alikon/node_modules/ws');
const koaBody=require('koa-body');
const render=require('koa-rend');

const Router=require('koa-router');

const app=new Koa();
var router=new Router();


render(app,{root:'views', development:true});

app.use(koaBody(/*{multipart:true,formidable:{}}*/));


router.get('/', ctx=>{
ctx.body=`<html><body><button onclick="ajax();">ajax</button>
<script>
function ajax(){
let xhr=new XMLHttpRequest();
xhr.open("POST","/testEvent");
xhr.setRequestHeader("Content-Type","application/json","utf-8");
xhr.onload=function(s){
if(xhr.status==200){
console.log(this.response);	
}else{console.log(this.response);}	
}
xhr.onerror=function(e){
console.error(e);	
}
let b={};
b.msg="hello";
xhr.send(JSON.stringify(b));	
}
</script></body></html>`;
//await ctx.render('ajax',{})
});
router.post('/testEvent', async (ctx)=>{
console.log("event_body", ctx.request.body);
ctx.body={info:"ok"}	
})

app.use(router.routes())/*.use(router.allowedMethods());*/

const servak=app.listen(PORT/*,"my_app_local.ru"*/);
console.log("PORT: ", PORT);
