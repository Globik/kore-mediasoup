const addon=require("./build/Release/binding.node");
addon.p_init(function(d){console.log('FROM ADDON: ',d);});
addon.p_close(function(d){console.log('FROM ADDON_2: ',d);})
addon.p_send_ev_fd(function(d){console.log('FROM ADDON_3: ',d);})
process.on("SIGINT",function(){process.exit(0);});