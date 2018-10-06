var EventEmitter=require('events').EventEmitter;
class Server extends EventEmitter{
	constructor(){
		super();
		}
		close(){
			this.emit('close',"on_closing");
			}
	}
	
	var server=new Server();
	
	
	server.on("close",function(d){
		console.log("on close: ",d);
		})
	
server.close();
