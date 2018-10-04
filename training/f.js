function suka(){
return Promise.resolve()	
}

function foo(){
return Promise.resolve().then(function(){console.log('1')}).then(function(){console.log('11')}).then(function(){console.log('22')})	
}
function boo(){
	return foo().then(function(){console.log(2)}).then(function(){console.log("r")}).catch(function(e){console.log(e)})
}
boo().then(function(f){console.log('boo: ', f)}).catch(function(e){console.log(e)})
function doo(){
return Promise.resolve()
.then(function(){console.log('erst in promise')})
.then(function(){
	let promises=[];
	for(var i=0;i<3;i++){
		let p=suka()
		.then(function(){console.log('bla 1')})
		.then(function(){console.log('bla2')})
		.catch(function(e){console.log(e)})
		promises.push(p)
	}
	return Promise.all(promises) 
	})	
}
function createOffer(){
	return doo()
	.then(function(){return Promise.resolve('Alice')})
	.catch(function(e){console.log(e)})
	}
	
	createOffer().then(function(d){console.log("any data? : ",d)}).catch(function(e){console.log(e)})
