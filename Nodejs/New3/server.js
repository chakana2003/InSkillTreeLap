var http = require('http');
var express = require('express');

var app = express();

app.get('/', function(req,res){
    var id = req.query['id'];
    var pw = req.query['pw'];

    var data = {
        'id' : id,
        'pw' : pw
    }

    res.send(data);
});

app.use(function(req, res){
    // var data = {
    //     name : 'Jack',
    //     region : 'YangPeong'
    // }

    // var jsonString = JSON.stringify(data);

    // res.writeHead(200, {'Content-Type' : 'text/html'}),
    // res.write(jsonString);
    // res.end();

    // get 요청
    // var id = req.query['id'];
    // var pw = req.query['pw'];

    // var data = {
    //     'id' : id,
    //     'pw' : pw
    // }

    // res.send(data);
});

app.listen(8000);

http.createServer(app);
console.log('Express 서버 실행 중..');