const seqpacket=n=>{
return `<html><head><title>seqpacket</title></head><body><h2>Hello</h2>
<button onclick="sendi();">ping</button><br><br>
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
}
function sendi(){
ws.send("ping");
}
`;
}