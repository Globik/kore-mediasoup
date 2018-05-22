// see excelent article on https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function
/*function makefunction(code){
return new Function('"use strict";return '+code)();
}
var add=makefunction(""+function(a,b){return a+b});
*/
//console.log("add : ",add(4,5));
//'use strict';
var m="mamad";
var crypto=require("crypto");
var module=require('./myModule.js');

var li="LILI";
var r="a";
function fu(func){
var code=`return(${func})()`;
try{var n=new Function(code);}catch(e){console.log("e2 : ",e)}
try{
return n();
}catch(e){console.log("e1: ",e)}
}

var f=fu(function(li){
//var li="lid";

var mui=`"${li}"`;
var cryp="`${require('./myModule.js')}`";
console.log("mua: ",mui);
console.log("cryp: ",cryp);
//return cryp;
return mui;
})
//var f=fu(`function(a){return a}`);
console.log('f: ',f);
//var q=fu(3,3);
//"use strict";
//require("crypto");
//var module=require('./myModule.js');

//console.log("mod: ", module(5,5));// those 5 and 5 can be values from other modules

function execute(func){
	console.log("mama: ",m);
	//return 
	func(require("crypto"));
}
/*
function funci(s){
require("crypto");
console.log("mama2: ",m);
console.log("ps: ",s);
}
*/
execute((s)=>{
require("crypto");
console.log("mama3: ",m);
//console.log("ss",s);
});