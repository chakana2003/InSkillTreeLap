// 객체를 클래스처럼 사용하기

function Person(name,job,age){
    this.name = name;
    this.job = job;
    this.age = age;
}

var Good = new Person('good','Beak',23);
var yes = new Person('ohye','Computer',65);

console.log(Good);
console.log(yes);

for(var ix = 0; ix < 10; ++ix){
    console.log(ix);
}

for(var key in Good){
    console.log(Good[key]);
}

Good.test = null;

console.log(Good.test);