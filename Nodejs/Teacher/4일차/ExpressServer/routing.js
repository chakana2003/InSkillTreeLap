// 모듈 추출.
var express = require('express');
var http = require('http');
var bodyParser = require('body-parser');

// 서버 생성.
var app = express();

// 라우터 생성.
var routerA = express.Router();
var routerB = express.Router();

// 라우터 설정.
routerA.get('/index', function(req, res){
    res.send('Index Page A');
});

routerA.post('/login', function(req, res){
    // 이름과 지역 속성 파싱.
    var name = req.body.name;
    var region = req.body.region;

    var data = {
        name : name,
        region : region
    };

    var jsonString = "get value: " + JSON.stringify(data);

    //res.write(JSON.stringify(data));
    res.send(jsonString);
});

routerB.get('/index', function(req, res){
    res.send('Index Page B');
});

// 라우터 적용.
app.use(bodyParser.urlencoded({ extended : false }));
app.use('/a', routerA);
app.use('/b', routerB);
//app.use(bodyParser());


// 서버 실행.
http.createServer(app).listen(8000);
console.log('서버 실행중');