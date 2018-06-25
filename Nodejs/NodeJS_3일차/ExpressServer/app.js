// 모듈 추출.
var http = require('http');
var express = require('express');

// express 객체 생성.
var app = express();

app.use(function(req,res,next){
    console.log('first');
    next();
})

app.use(function(req,res,next){
    console.log('second');
    next();
});

app.use(function(req,res,next){
    console.log('third');
    
    res.send('Express Server');
});

// 요청 처리.
// app.use(function(req, res){

//     // Get 요청에서 전달받은 정보 읽기.
//     var id = req.query['id'];
//     var pw = req.query['pw'];

//     // 전달받은 정보를 이용해서 객체 만들기.
//     var data = {
//         'id' : id,
//         'pw' : pw
//     }

//     // 객체 전달.
//     res.send(data);
// });

// Get 요청처리.
//app.post();
app.get('/', function(req, res){

    // User-Agent 속성 출력.
    console.log(req.header('User-Agent'));

    var agent = req.header('User-Agent');
    if(agent.toLowerCase().match(/chrome/)){
        res.send('Hello Chrome');
    }else if(agent.toLowerCase().match(/firefox/)){
        res.send('Hello Firefox');
    }else{
        res.send('Hello Edge');
    }

    // Get 요청에서 전달받은 정보 읽기.
    var id = req.query['id'];
    var pw = req.query['pw'];

    // 전달받은 정보를 이용해서 객체 만들기.
    var data = {
        'id' : id,
        'pw' : pw
    }

    // 객체 전달.
    res.send(data);
});

// 8000번 포트에서 요청 대기.
app.listen(8000);

// 서버 생성.
http.createServer(app);
console.log('Express 서버 실행중');