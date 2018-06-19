const frontend = function(n){
return `<html><head><title>${n.title}</title></head><body>
<h3>Hallo, ${n.username}!</h3>
<h4>Wanna talk with echotest plugin? Here you go:</h4>
<h4>Websocket<h4>
<button onclick="connect_websocket();">connect websocket</button><br>
<h5>Status:</h5>
<span id="stat">no connection</span><hr>
<h5>Input text folder:</h5>
<input id="put" type="text" style="" placeholder="your message"/> | <button onclick="send_message();">send message</button>
<h4>Output:</h4>
<output id="out"></output>
<script src="/globi.js"></script>
</body></html>`;
}
module.exports={frontend}