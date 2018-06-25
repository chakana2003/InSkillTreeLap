// 함수선언.
function sayHello(){
    console.log('Gello');
    //return; 생략됨.
}

sayHello();

console.log(sayHello());

var sayHello2 = sayHello;
// 밑과 전부 같은말.
//var sayHello2 = function(){
//     console.log('hello');
// }
// var sayHello2 = =>{
//     console.log('hello');
// }

sayHello2();