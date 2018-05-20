function execute(code){
return new Function(`"use strict";return ${code}`)();
}
//var add=
	module.exports=execute(`function(a,b){return a+b}`);
//module.exports=add;