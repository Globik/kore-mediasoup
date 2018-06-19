const addon=require("./build/Release/binding.node");
const str="Hali hallo!";
const http=require('http');
const b=Buffer.from(str);
function m(){
addon.p_create(function(d,m){
console.log("[s.js]: Here the message from addon on thread created: ", d);
});
}
m();
//setInterval(function(){console.log("bar")},1000)
//addon.on_msg(function(d){
//console.log('[s.js]: from addon on_msg (d): ',d)			
//})
//addon.p_send(b,function(err,data){console.log('[s.js]: from addon p_send: ',err,data);})
//setTimeout(function(){console.log('[s.js]: TIMEOUT. STOPING RIGHT NOW');
addon.p_close(function(d){console.log('[s.js]: from addon p_close: ',d)})
					 //},0)
