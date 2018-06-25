// 프로그램 종료 시 이벤트 발생.
process.on('exit',function(){
    console.log('escape, quickly!!');
});

// 오류 발생 시.
process.on('uncaughtExeption',function(error){
    console.log('error: '+error);
});

var count = 0;
function test(){
    count++;
    if(count > 3){ return; }

    // 강제로 예외 발생.
    setTimeout(test,2000);
    //error.error.error();
    process.emit('uncaughtExeption');
};

setTimeout(test,2000);

