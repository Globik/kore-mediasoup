const ajax=function(n){
return `<html><body><button onclick="ajax();">ajax</button>
<script>
function ajax(){
let xhr=new XMLHttpRequest();
xhr.open("post","/testi");
xhr.setRequestHeader("Content-Type","application/json","utf-8");
xhr.onload=function(s){
if(xhr.status==200){
console.log(this.response);	
}else{console.log(this.response);}	
}
xhr.onerror=function(e){
console.error(e);	
}
let b={};
b.msg="hello";
xhr.send(JSON.stringify(b));	
}
</script></body></html>
`;
}
module.exports={ajax}
