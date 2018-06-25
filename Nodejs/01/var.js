console.log("Hello World");

function text(number, number2, string1){
    console.log(number);
}

text(10);

function text1(text2){
    text2(30);
}

text1(text);

var num1 = 3;
var num2 = 3.4;
var num3 = num1 + num2;

console.log("num1: " + num1 + " num2: " + num2 + " num3: "+num3);

num1 = 0.1;
num2 = 0.2;
var boolA = (num1+num2==0.3);

console.log(boolA);

var boolB = ((num1*10+num2*10)/10 == 0.3);

console.log(boolB);