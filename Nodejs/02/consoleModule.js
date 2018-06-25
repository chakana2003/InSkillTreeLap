// 타이머 시작.
console.time('test');

var output = 0;
for(var ix = 0; ix < 100; ++ix){
    output += ix*10;
}

console.log('결과 : ' + output);
// 타이머 종료.
console.timeEnd('test');

console.log(__dirname);
console.log(__filename);
