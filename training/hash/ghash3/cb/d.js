var pendingSent=new Map();
var sisi="sisi";
create().then(function(d){console.log("data: ",d)}).catch(function(err){console.log("err: ",err);
	var lab2=pendingSent.delete(sisi);
	console.log("lab2: ",lab2);
	if(!lab2){console.log("no delete in pending: ");}else{console.log("delete  pending ok");}
	})
function create(){
	var id=sisi;
return new Promise(function(pres,prej){
	let sent={
		resolve:(data)=>{
			if(!pendingSent.delete(id)){console.log("no pending delete");return;}
			clearTimeout(sent.timer);
			pres(data);
			},
			timer: setTimeout(()=>{
				var lab=pendingSent.delete(id);
				console.log("lab: ",lab);
				if(!lab){console.log("no pending delete 2");return;}
				//here lab mast be true
				console.log("set timeout occured?");
				prej("timeout error");
				},1000)
		}
		pendingSent.set(id, sent);
	})	
}
