//promise chain
const suka="suka";
var sent=new Map();
function request(){
	
	return new Promise(function(bresolve,reject){
		let d={
		resolve:(data)=>{bresolve(data)}
		}
		sent.set("buka",d);
		//bresolve("vata_");
		
		})
		//me("buka")
	}
function me(str){
	let d=sent.get(str);
	d.resolve("SUKA");
	}
function create_room2(){
	//from channel
	return request().then(function(data){console.log('room3: ',data);return data+'_assa';})
	}

function create_room(){
	//from worker
	return create_room2().then(function(room2){console.log('room2: ',room2);return room2;})
	}

create_room().then(function(room){
	console.log('room1: ', room)
	})
	
//callbacks nested
var fuck=new Map();
function request2(cb){
	let du={mi:function(data){
		return cb(cb(cb(data)));
		}}
		fuck.set("mama",du);
	return cb("data_");
	}
function create2(cb){
return cb(request2(function(data){console.log('b_room3: ',data);return data+'_saka';}));
}
function create(cb){
return cb(create2(function(data){console.log('b_room2: ',data);return data;}));
}

create(function(data){
console.log('b_room1: ', data)
})

// C style
function request3(cb){return cb("data_");}
function room2(cb){return cb(request3(bu3))}
function room(cb){return cb(room2(bu2))}
room(bu);

function bu(d){console.log('c_room1: ',d)}
function bu2(d){console.log('c_room2: ',d);return d;}
function bu3(d){console.log('c_room3: ',d);return d+'_makaka';}

// фишка в том, что
//.. в риквесте ловится приходящая инфа для создания комнаты
//потом создается она самая, добавляется в колекцию, навешивают ивент на закрытие оной, передается ее сущность вверх по цепочке
//классу сервера
//в сервере генерируют событие о создании новой комнаты и дальше комнаты сущность идет к юзеру. Всё - финиш
//как это на Си организовать - я хуй его знает

var _pendingSent=new Map();

function bu7(d){console.log('d_room1: ',d)}
function bu6(d){console.log('d_room2: ',d);return d;}
function bu5(d){console.log('d_room3: ',d);return d+'_Bob';}
function request4(cb){
	
let s={
	resolv: (da)=>{
		//if(!_pendingSent.delete(suka)){return;}
		return cb(da);
		//cb(cb(cb(d)));
		}
	};
	
	_pendingSent.set(suka,s);

	
	
return cb("alice_");
}

function room5(cb){return cb(request4(bu5))}
function room6(cb){return cb(room5(bu6))}
room6(bu7);




function go_ahead(str){
	let s=_pendingSent.get(str);
	 s.resolv("*** MIAU_")
	 let d=fuck.get("mama");
	 d.mi("BBBBBBBBB");
}

setTimeout(function(){go_ahead(suka);me("buka")},1000)
