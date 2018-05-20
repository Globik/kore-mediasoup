// see excelent article on https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function
/*function makefunction(code){
return new Function('"use strict";return '+code)();
}
var add=makefunction(""+function(a,b){return a+b});
*/
//console.log("add : ",add(4,5));
var module=require('./myModule.js');

console.log("mod: ",module(5,5));// those 5 and 5 can be values from other modules