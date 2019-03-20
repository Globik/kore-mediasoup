var socket = null;
var transaction='';
var session_id=0,handle_id=0,pc=null;
var plugin="janus.plugin.echotest";
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
var interv;

function onmessage(msg) {
mout.innerHTML+="<b>msg: </b>"+msg+"<br>";
console.log('length: ',msg.length);
//return;
try{var m=JSON.parse(msg);}catch(e){
mout.innerHTML+="<b>parse err: </b>"+e+"<br><b>not json: </b>"+msg+"<br>";
									return;
  }
	/*
if(m.type=="user_id"){
usid=m.id;
yrid.textContent=m.id;
transaction=m.transaction;
session_id=m.session_id;
}else if(m.type=="message"){}else if(m.type=="on_attach"){
transaction=m.transaction;
handle_id=m.handle_id;
session_id=m.session_id	
}else if(m.type=="on_detach"){
	
}else if(m.type=="on_destroy"){
}else if(m.type=="janus_error"){
msg(msg);
}else if(m.type=="janus_success"){

}else if(m.type=="janus_ack"){

}else{
mout.innerHTML+="<b>unknown type: </b>"+m.type+"<br>";
}
if(m.janus && m.janus=="event"){
if(m.jsep && m.jsep.type=="answer"){
console.log("entering in answer object.");
var ax = new RTCSessionDescription({ type: "answer", sdp: m.jsep.sdp });
pc.setRemoteDescription(ax, onSetRemoteDescriptionDone, onError);
}
}
	*/
	//success_attach
if(m.type=="janus"){
if(m.janus=="success_attach"){
handle_id=m.data.id;
spanhandleid.textContent=handle_id;
//m.session_id,m.transaction
}else if(m.janus=="success"){

}else if(m.janus=="event"){
if(m.jsep && m.jsep.type=="answer"){
var ax = new RTCSessionDescription({ type: "answer", sdp: m.jsep.sdp });
pc.setRemoteDescription(ax, onSetRemoteDescriptionDone, onError);
}
}else{}
	
}else if(m.type=="hello_user"){
transaction=m.transaction;
session_id=m.session_id;
spansessid.textContent=session_id;
spantransact.textContent=transaction;
}else{

}
}

function connect() {
if(socket){mout.innerHTML+="<b>already in connection!</b><br>";return;}
socket = new WebSocket("ws://localhost:3000");
socket.onopen = function(evt) { mout.innerHTML+= "<b>websocket opened</b><br>";};
socket.onclose = function(evt) { 
if(interv)clearInterval(interv);
socket=null;
mout.innerHTML+="<b>websocket closed</b><br>"; 
};
socket.onmessage = function(evt) { onmessage(evt.data) };
socket.onerror = function(evt) { mout.innerHTML+="<b>onerror:</b>"+evt+"<br>"; };
}

function connect_janus(){
if(socket)socket.send(JSON.stringify({type:"connect"}))	
}
function send_message(){
if(!f.value)return;
var ob={};
ob.msg=f.value;
ob.type="message";
ob.session_id=session_id;
ob.handle_id=handle_id;
ob.transaction=transaction;
	
if(socket)socket.send(JSON.stringify(ob));
}
	
	function get_info(){
	var ob={};
		ob.janus="info";
		ob.transaction=transaction;
		if(socket)socket.send(JSON.stringify(ob));
	}
	
function disconnect(){
if(!socket){mout.innerHTML+="<b>already disconnected!</b><br>";return;}
socket.close();
socket=null;
}
function go_attach(){
var ob={};
ob.janus="attach";
ob.plugin=plugin;
ob.session_id=session_id;
//ob.handle_id=handle_id;
ob.transaction=transaction;
if(socket)socket.send(JSON.stringify(ob));
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
function go_destroy(){
	/*
		var ob={};
			ob.type="destroy";
			ob.session_id=session_id;
			ob.handle_id=handle_id;
			ob.transaction=transaction;
			if(socket)socket.send(JSON.stringify(ob));
			*/
		}
function create_session(){
var d={};
d.janus="create";
d.transaction=transaction;
if(socket)socket.send(JSON.stringify(d));
//{ "janus": "success", "transaction": "transaction_string", "data": { "id": 777363624503552 } }
//janus:ev,sender:plug.handleid,plugindata:plugin:name,data:echotest:ev,result:ok
}
function ping(){
let d={};
	d.janus="ping";
	d.transaction="ping";
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
dc.onmessage = function (event) { msg("Remote: " + event.data); };
dc.onopen = function () { msg("Web RTC Connected."); };
pc.ondatachannel = onNewDataChannel;
pc.onicecandidate = onIceCandidate;
pc.createOffer(onOfferDone, onError, { mandatory: { OfferToReceiveAudio: false, OfferToReceiveVideo: false } });
pc.oniceconnectionstatechange = function (){
	
if(pc.iceConnectionState == 'disconnected'){msg('DISCONNECTED');}
}
}
	
function handle_cand(c){
	var ca=new RTCIceCandidate(c.candidate);
		try{
		pc.addIceCandidate(ca);
		}catch(e){msg(e);}
	
	}
	
function onIceCandidate(e){
	
if (e.candidate) {
var ob={};

ob.type="janus";
ob.janus="trickle";

ob.candidate=e.candidate;
ob.session_id=session_id;
ob.handle_id=handle_id;

ob.transaction=transaction;
	try{
	var obi=JSON.stringify(ob);
	if(socket) socket.send(obi);
	}catch(e){msg(e);}
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
debug('onCandidateAdded: ' + e);
//alert(e); 
}

function onOfferDone(offer){
msg("ON OFFER DONE");
// debug(offer.sdp);
msg("currentoffer: "+currentoffer);
currentoffer = offer;
msg("<b>currentoffer_2: </b>"+JSON.stringify(currentoffer));
//msg("<b>OFFER SDP:</b> "+offer.sdp);
var data={};
data.type="janus";
data.janus="message";
	//offer.trickle=false;
data.jsep={};
	data.jsep.sdp=offer.sdp;
	data.jsep.type=offer.type;
//data.jsep.trickle=false;
data.session_id=session_id;
data.handle_id=handle_id;
data.transaction=transaction;
data.body={audio:false,video:false,data:true,trickle:false};

try{
var bjson=JSON.stringify(data);
msg(bjson);
if(socket) socket.send(bjson);else msg("you did not connected to websocket.");
}catch(e){msg(e);}
pc.setLocalDescription(offer, onSetLocalDescriptionDone, onError);
sdp = currentoffer.sdp;
msg("<b>On Offer Done sdp:</b> "+sdp);
}
		
function onSetLocalDescriptionDone(){msg("on_set_local_descr done!"); }
function initiatorErrorResponse() { msg('Could not contact server.'); }
function onSetRemoteDescriptionDone() { debug('setRemoteDescription() completed'); }
function stop() { pc.close(); }
function onNewDataChannel(e){
msg("Channel [" + e.channel.label + "] created");
dc = e.channel;
dc.onmessage = function (event) { msg("Remote: " + event.data); }
}

function onError(e) { if(e.message){ alert("onError: " + e.message);} else{ alert(e);}}
function debug(m) {  console.log(m);  }
function msg(m) { outputtextbox.innerHTML += (m + "<br />"); }
/*
"janus": "event",
   "session_id": 3339039474184731,
   "sender": 4249572172194807,
   "transaction": "trans_act_str",
   "plugindata": {
      "plugin": "janus.plugin.echotest",
      "data": {
         "echotest": "event",
         "result": "ok"
      }
   },
   "jsep": {
      "type": "answer",
      "sdp": "v=0\r\no=- 1438594046166573988 2 IN IP4 127.0.0.1\r\ns=-\r\nt=0 0\r\na=group:BUNDLE data\r\na=msid-semantic: WMS janus\r\nm=application 9 DTLS/SCTP 5000\r\nc=IN IP4 127.0.0.1\r\na=sendrecv\r\na=sctpmap:5000 webrtc-datachannel 16\r\na=mid:data\r\na=ice-ufrag:Otcv\r\na=ice-pwd:FCe5HvLHoq+1/c+mqJa3yn\r\na=ice-options:trickle\r\na=fingerprint:sha-256 D2:B9:31:8F:DF:24:D8:0E:ED:D2:EF:25:9E:AF:6F:B8:34:AE:53:9C:E6:F3:8F:F2:64:15:FA:E8:7F:53:2D:38\r\na=setup:active\r\na=end-of-candidates\r\n"
   }
}
*/
