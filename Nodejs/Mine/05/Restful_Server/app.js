var http = require('http');
var express = require('express');
var bodyParse = require('body-parser');
var fs = require('fs');
var db = require('./database');

// 데이터 베이스.
var database = db.dummyDB;

var app = express();

app.use(bodyParse.urlencoded({
    extended : false
}));

// 리디렉션.
app.get('/', function(req,res){
    res.redirect('/user');
})

// 전체 사용자 정보 조회.
app.get('/user', function(req,res){
    res.send(database.get());
});

app.get('/user/:id', function(req,res){
    var id = req.params.id;

    res.send(database.get(id));
});

app.post('/user',function(req,res){
    var data = {
        name : req.body.name,
        region : req.body.region
    };

    if(data.name && data.region){
        res.send(database.insert(data));
    }else{
        throw new Error('error');
    }
});

app.put('/user/:id',function(req,res){
    var id = req.params.id;
    var name = req.body.name;
    var region = req.body.region;

    var item = database.get(id);
    item.name = name || item.name;
    item.region = region || item.region;

    res.send(item);
});

app.delete('/user/:id',function(req,res){
    var id = req.params.id;
    res.send(database.remove(id));
});

http.createServer(app).listen(8000);
console.log('서버 실행중');