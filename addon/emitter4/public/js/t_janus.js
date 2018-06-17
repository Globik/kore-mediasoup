var socket = null;
var transaction="user_77f";
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
try{var m=JSON.parse(msg);}catch(e){/*mout.innerHTML+="<b>parse err: </b>"+e+"<br><b>not json: </b>"+msg+"<br>";*/
									//return;
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
if(m.janus){
	if(m.janus=="success"){
	console.log(m.janus);
	transaction=m.transaction;
	session_id=m.data.id;
	spansessid.textContent=session_id;
	spantransact.textContent=transaction;
		
	
	}
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
ob.type="detach";
ob.session_id=session_id;
ob.handle_id=handle_id;
ob.transaction=transaction;
if(socket)socket.send(JSON.stringify(ob));
}
function go_destroy(){
		var ob={};
			ob.type="destroy";
			ob.session_id=session_id;
			ob.handle_id=handle_id;
			ob.transaction=transaction;
			if(socket)socket.send(JSON.stringify(ob));
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
var d={};
	d.janus="ping";
	d.transaction=transaction;
	if(socket)socket.send(JSON.stringify(d));
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
ob.type="trickle";
ob.candidate=e.candidate;
ob.session_id=session_id;
ob.handle_id=handle_id;
ob.transaction=transaction;
	try{
	var obi=JSON.stringify(ob);
	if(socket) socket.send(obi); else msg("socket is down.");
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
msg("<b>OFFER SDP:</b> "+offer.sdp);
var data={};
data.type="janus";
data.jsep=offer;
data.session_id=session_id;
data.handle_id=handle_id;
data.transaction=transaction;
data.body={what:"some_body_must_be"};
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
