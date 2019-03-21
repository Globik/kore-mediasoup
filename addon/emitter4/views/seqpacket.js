// some basic concept "ping-pong" test with Janus phunix transport with type SOCK_SEQPACKET
const seqpacket=n=>{
return `<html><head><title>seqpacket</title></head><body>
<a href="/html/test.html">test html</a> | <a href="/html/videoBroadcast.html">viedoBroadcast.html</a>
<h2>Hello</h2>
<button onclick="janus_ping();">ping</button><button onclick="janus_info();">info</button>
<button onclick="ajax();">ajax</button><br><br>
<button onclick="janus_session_create();">session create</button><br><br>
<output id="out"></output><script>${get_script()}</script></body></html>`;
}
module.exports={seqpacket}
function get_script(){
return `
var ws=new WebSocket("ws://localhost:3000");
ws.onopen=function(){
out.innerHTML+="<b>websock is opened!</b><br>";
};
ws.onerror=function(e){
out.innerHTML+="<b>error: </b>"+e+"<br>";
};
ws.onclose=function(){
out.innerHTML+="<b>ws closed!</b><br>";
}
ws.onmessage=function(ev){
out.innerHTML+="<b>message: </b>"+ev.data+"<br>";
let a;
try{a=JSON.parse(a);}catch(e){return;}
if(a.type=="a"){}
}
function janus_ping(){
let d={};
d.transaction="ping"
d.janus="ping";
wsend(d);
}
function janus_info(){
let d={};
d.transaction="info"
d.janus="info";
wsend(d);
}
function janus_session_create(){
let d={};
d.transaction="create";
d.janus="create";
wsend(d);
}

function wsend(ob){
let a;
try{a=JSON.stringify(ob);}catch(e){retrun;}	
if(ws && ws.readyState==1)ws.send(a);
}
function ajax(){
let xhr=new XMLHttpRequest();
xhr.open("post","/testEvent");
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
`;
}
