// /home/globik/kore-mediasoup/addon/build/Release/binding.node
const addon=require("./build/Release/binding.node");
addon.runcallback(function(msg){
console.log("msg ",msg);
});
addon.runcallback(function(msg){console.log('msg2: ',msg);});
addon.runcallbacks(function(msg){console.log('msg3: ',msg);});