// 모듈 추출.
var http = require('http');
var express = require('express');

// express 객체 생성.
var app = express();

app.use(function(req, res, next) {
    console.log('first');
    next();
});

app.use(function(req, res, next){
    console.log('second');
    next();
});

app.use(function(req, res, next){
    console.log('third');
    
    res.send('Express Server');
});

// 8000번 포트에서 요청 대기.
app.listen(8000);

// 서버 생성.
http.createServer(app);
console.log('Express 서버 실행중');