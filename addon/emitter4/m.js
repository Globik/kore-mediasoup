const addon=require("./build/Release/binding.node");
const str="pupkin";//6 
const b=Buffer.from(str);
addon.p_init(function(d){console.log('FROM ADDON: ',d);});
addon.p_close(function(d){console.log('FROM ADDON_2: ',d);})
addon.p_send_ev_fd(b, function(err,d){console.log('FROM ADDON_3: ',err, d);})
process.on("SIGINT",function(){process.exit(0);});