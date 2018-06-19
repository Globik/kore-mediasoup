var ws=null;
var address="ws://localhost:3000";

function connect_websocket(){
ws=new WebSocket(address);
ws.onopen=on_open;
ws.onerror=on_error;
ws.onmessage=on_message;
ws.onclose=on_close;
}
function send_message(){
var msg=put.value;
if(!msg)return;
out.innerHTML+="<b>you wrote: </b>"+msg+"<br>";
if(ws)ws.send(msg);
}
function on_open(){
stat.textContent="Websocket opened!"
}
function on_error(ev){
out.innerHTML+="<b>error: </b>"+ev+"<br>";
}
function on_close(){
ws=null;
stat.textContent="Websocket closed!";
}
function on_message(ev){
print(ev.data);
put.value="";
}
function print(str){
out.innerHTML+="<b>msg from node.js addon: </b>"+str+"<br>";
}