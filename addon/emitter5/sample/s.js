const addon=require("./build/Release/binding.node");

addon.p_create(function(d,m){
console.log("[s.js]: Here the message from addon on thread created: ", d);
//setInterval(function(){console.log("bar")},1000)
})