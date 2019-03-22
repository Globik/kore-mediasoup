const f=n=>{
	return `
<html><head><title>Echo datachannel</title></head><body>
<button onclick="ajax();">test ajax</button><br><br>
	<div id="divtransact"><b>TRANSACTION:</b>&nbsp;<span id="spantransact">0</span></div>
	<div id="divsessid"><b>SESSION_ID:</b>&nbsp;<span id="spansessid">0</span></div>
	<div><b>HANDLE_ID:&nbsp;</b><span id="spanhandleid">0</span></div>
	<b>Connenct websocket.</b><br>
	<b>Do connect!: </b><button onclick="connect();">connect</button> | <button onclick="disconnect();">disconnect</button> |
	 <button onclick="ping();">ping janus</button><br>
	<b>your id: </b><span id="yrid"></span><br>
	<b>Send a message</b><br>
	<input type="text" id="f" value="your_message"/>| <button onclick="send_message();">send message</button> | 
	| <button onclick="create_session();">create_session</button> |
| <button onclick="get_info();">janus_info</button> |	
		<button onclick="go_attach();">attach</button>
	| <button onclick="go_detach();">detach</button>
	| <button onclick="go_destroy();">destroy</button>
	
<button onclick="keep_alive();">keep alive</button><br>
<div id="chout" style="border:1px solid pink;">Here must be DataChannel messages</div><br>
<button onclick="create_channel();">create datachannel</button>
<div style="background:green;"><b>data</b><br>
<textarea id="inputtext" style="width:70%;border:1px solid red;" onkeypress="onUserKeyPressEvent(event)"></textarea> 
</div>
<b>output:</b><br>

<span id="outputtext"></span>
 <hr>
<output id="mout"></output> 
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
</script>	
<script>

var socket = null;
var transaction='';
var session_id=0,handle_id=0,pc=null;
var j_timer=null;
//"spantransact""spansessid""spanhandleid">0</s


var plugin_art="janus.plugin.echotest";
var usid=0;
yrid.textContent=usid;
mout.innerHTML="";
var dc = null;
var cf = { "iceServers": [] };
var currentoffer = null;
var requester;
var sdp = "";
var outputtextbox = document.getElementById("outputtext");
var inputtextbox = document.getElementById("inputtext");
function gid(i){return document.getElementById(i);}
var f=gid("f");
//var interv;

function onmessage(msg) {
mout.innerHTML+="<b>msg: </b>"+msg+"<br>";
console.log('length: ',msg.length);
try{var m=JSON.parse(msg);}catch(e){
mout.innerHTML+="<b>parse err: </b>"+e+"<br><b>not json: </b>"+msg+"<br>";
return;
}
if(m.type=="janus"){
if(m.janus=="success"){
if(m.transaction=="create_session"){
session_id=m.data.id;
spansessid.textContent=session_id;
spantransact.textContent=m.transaction;
set_keep_alive();
}else if(m.transaction=="attach_plugin"){
	//alert('attach');
console.warn("attach plugin");	
handle_id=m.data.id;
spanhandleid.textContent=handle_id;
spantransact.textContent=m.transaction;
}else{}
}else if(m.janus=="event"){
if(m.jsep && m.jsep.type=="answer"){
console.warn("TYPE ANSWER IN WS!");
var ax = new RTCSessionDescription({ type: "answer", sdp: m.jsep.sdp });
pc.setRemoteDescription(ax, onSetRemoteDescriptionDone, onError);
}
}else{}
	
}else if(m.type=="hello_user"){

}else{}
}

function connect() {
if(socket){mout.innerHTML+="<b>already in connection!</b><br>";return;}
socket = new WebSocket("ws://localhost:3000");
socket.onopen = function(evt) { mout.innerHTML+= "<b>websocket opened</b><br>";};
socket.onclose = function(evt) { 
socket=null;
mout.innerHTML+="<b>websocket closed</b><br>"; 
clear_keep_alive();
}
socket.onmessage = function(evt) { onmessage(evt.data) };
socket.onerror = function(evt) { mout.innerHTML+="<b>onerror:</b>"+evt+"<br>"; };
}

//function connect_janus(){if(socket)socket.send(JSON.stringify({type:"connect"}))}
function send_message(){
if(!f.value)return;
var ob={};
ob.msg=f.value;
ob.type="message";
ob.session_id=session_id;
ob.handle_id=handle_id;
ob.transaction=transaction;
wsend(ob);
}
	
function get_info(){
var ob={};
ob.janus="info";
ob.transaction="info";
if(socket)socket.send(JSON.stringify(ob));
}

function ping(){
let d={};
d.janus="ping";
d.transaction="ping";
wsend(d);	
}

function disconnect(){
if(!socket){mout.innerHTML+="<b>already disconnected!</b><br>";return;}
socket.close();
socket=null;
}
function go_attach(){
let d={};
d.transaction="attach_plugin";
d.session_id=session_id;
d.janus="attach";
d.plugin=plugin_art;
d.opaque_id="fucker";
wsend(d)
}
function go_detach(){
var ob={};
ob.janus="detach";
ob.type="janus";
ob.session_id=session_id;
ob.handle_id=handle_id;
ob.transaction=transaction;
if(socket)socket.send(JSON.stringify(ob));
}
function go_destroy(){}

function create_session(){
	//alert("create_session");
var d={};
d.janus="create";
d.transaction="create_session";
if(socket)socket.send(JSON.stringify(d));
}
function ping(){
let d={};
d.janus="ping";
d.transaction="ping";
wsend(d);
}

function set_keep_alive(){
console.warn("on handle_id(on attach)");
if(j_timer !=null){console.warn("why j_timer is not null?");}
j_timer=setTimeout(function tick(){	
  keep_alive();
j_timer=setTimeout(tick, 10000);//50 sec
}, 10000);
}	

function clear_keep_alive(){
console.log("clear_keep_alive");
if(j_timer==null){console.warn("Why j_timer is null??");}
clearTimeout(j_timer);
j_timer=null;	
}

function keep_alive(){
if(session_id==0){console.warn("no sess id?");return;}
let d={};
d.janus="keepalive";
d.session_id=session_id;
d.transaction="keep_alive";
wsend(d);
}

function wsend(obj){
let ml;
try{ml=JSON.stringify(obj);}catch(e){console.error(e);return;}
if(socket && socket.readyState==1)socket.send(ml);	
}
function create_channel(){
pc=new RTCPeerConnection(cf);
dc = pc.createDataChannel("JanusDataChannel", { });
dc.onmessage = function (event) {
chout.innerHTML="<b>Remote DataChannel: </b>"+event.data;
msg;("<b>Remote DataChannel: </b>" + event.data); 
 };
dc.onopen = function () { msg("<b>DataChannel opened!</b>"); };
pc.onicecandidate = onIceCandidate;
pc.oniceconnectionstatechange = function (){
console.log("Ice connection state change: ", pc.iceConnectionState);
if(pc.iceConnectionState == 'disconnected'){msg('DISCONNECTED');}
}

pc.onicegatheringstatechange = on_ice_gathering_state_change;
pc.onicecandidaterror = on_ice_candidate_error;
pc.onnegotiationneeded = on_negotiation_needed;
pc.signalingstatechange = signaling_state_change;
pc.createOffer(onOfferDone, onError, { mandatory: { OfferToReceiveAudio: false, OfferToReceiveVideo: false } });
}
	
function handle_cand(c){
console.warn("handle_cand()");
var ca=new RTCIceCandidate(c.candidate);
try{
console.warn("before add candidate");
pc.addIceCandidate(ca);
}catch(e){msg(e);}
}
	
function onIceCandidate(e){
console.log("ON ICE CANDIDATE");
if (e.candidate) {
var ob={};
console.log("Do trickle");
ob.type="janus";
ob.janus="trickle";
ob.candidate=e.candidate;
ob.session_id=session_id;
ob.handle_id=handle_id;
ob.transaction=transaction;
wsend(ob);
}

	
}
function onUserKeyPressEvent(event) {
if (event.keyCode == 13) {
if(dc) dc.send(inputtextbox.value);
msg("Local: " + inputtextbox.value);
inputtextbox.value = "";
return false;
}
}
function onCandidateAdded(e) { 
console.log('onCandidateAdded: ' + e);
//alert(e); 
}

function onOfferDone(offer){

pc.setLocalDescription(offer, function(){
console.warn("On set local description");
let data={};
data.type="janus";
data.janus="message";
data.jsep={};
data.jsep.sdp=offer.sdp;
data.jsep.type=offer.type;
data.session_id = session_id;
data.handle_id = handle_id;
data.transaction="send_offer";
data.body={audio:false,video:false,data:true};
wsend(data);
}, onError);
}
		
//function onSetLocalDescriptionDone(){msg("on_set_local_descr done!"); }

function onSetRemoteDescriptionDone() { debug('setRemoteDescription() completed'); }
function initiatorErrorResponse() { msg('Could not contact server.'); }
function stop() { pc.close(); }

function on_ice_gathering_state_change(){console.log("ice gathering: ",this.iceGatheringState);}
function on_ice_candidate_error(err){console.error('ice candidate err: ', err);};
function on_negotiation_needed(){console.log("ON NEGOTIATION NEEDED!");};
function signaling_state_change(){console.log('signaling state: ',this.signalingState);};
 


function onError(e) {
if(e.message){ 
console.error("onError: " + e.message);
} else{ console.error(e);
}}
function debug(m) {  console.log(m);  }
function msg(m) { outputtextbox.innerHTML += (m + "<br />");}
</script></body></html>`;}
module.exports={f}
