const f=n=>{
	return `
<html><head><title>Echo datachannel</title></head><body>
	<div id="divtransact"><b>TRANSACTION:</b>&nbsp;<span id="spantransact">0</span></div>
	<div id="divsessid"><b>SESSION_ID:</b>&nbsp;<span id="spansessid">0</span></div>
	<div><b>HANDLE_ID:&nbsp;</b><span id="spanhanleid">0</span></div>
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
	<hr>
	<br>
	<button onclick="create_channel();">create datachannel</button>
<h4>output:</h4>
<output id="mout"></output>
<span id="outputtext"></span>
<hr>
<textarea id="inputtext" style="width:100%" onkeypress="onUserKeyPressEvent(event)"></textarea> 

<script src="/js/t_janus.js"></script></body></html>`;}
module.exports={f}