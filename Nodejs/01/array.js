// 배열 선언.
var arrayA = [1,2,3,4,5];

// 배열 순회.
for(var ix = 0; ix < arrayA.length; ++ix){
    console.log(arrayA[ix]);
}
console.log();

for(var ix in arrayA){
    console.log(arrayA[ix]);
}
console.log();

console.log(arrayA["1"]);

console.log();
var arrayB = {
    '0' : 1,
    '1' : 2,
    '2' : 3,
    '3' : 4,
    '4' : 5
}

for(var ix in arrayB){
    console.log(arrayB[ix]);
}
console.log("----------");
var length = arrayA.length;
arrayA[length] = length +1;

for(var ix=0; ix<arrayA.length; ++ix){
    console.log(arrayA[ix]);
}
console.log("----------");
arrayA[10] =101;    

for(var ix=0; ix<arrayA.length; ++ix){
    console.log(arrayA[ix]);
}
console.log("----------");
arrayA.push(59);
arrayA.length = 15;

for(var ix=0; ix<arrayA.length; ++ix){
    console.log(arrayA[ix]);
}

console.log("----------");
arrayA.splice(2,6);

for(var ix=0; ix<arrayA.length; ++ix){
    console.log(arrayA[ix]);
}