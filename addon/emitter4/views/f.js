const f=n=>{
	return `
<html><head><title>Echo datachannel</title></head><body>
<button onclick="ajax();">test ajax</button><br><br>
	<div id="divtransact"><b>TRANSACTION:</b>&nbsp;<span id="spantransact">0</span></div>
	<div id="divsessid"><b>SESSION_ID:</b>&nbsp;<span id="spansessid">0</span></div>
	<div><b>HANDLE_ID:&nbsp;</b><span id="spanhandleid">0</span></div>
	<h4>Connenct websocket.</h4>
	<b>Do connect!: </b><button onclick="connect();">connect</button> | <button onclick="disconnect();">disconnect</button><br>
	<b>your id: </b><span id="yrid"></span><br>
	<h4>Send a message</h4>
	<input type="text" id="f" value="your_message"/>| <button onclick="send_message();">send message</button> | 
	| <button onclick="create_session();">create_session</button> |
| <button onclick="get_info();">janus_info</button> |	
		<button onclick="go_attach();">attach</button>
	| <button onclick="go_detach();">detach</button>
	| <button onclick="go_destroy();">destroy</button><br>
	<button onclick="connect_janus();">connect janus</button>
<button onclick="ping();">ping</button>
	<hr>
	<br>
	<button onclick="create_channel();">create datachannel</button>
<h4>output:</h4>
<output id="mout"></output>
<span id="outputtext"></span>
<hr>
<div style="background:green;"><h2>data</h2>
<textarea id="inputtext" style="width:100%" onkeypress="onUserKeyPressEvent(event)"></textarea> 
</div>
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
<script src="/js/t_janus.js"></script></body></html>`;}
module.exports={f}
