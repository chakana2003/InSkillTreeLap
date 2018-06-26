var http = require('http');
var express = require('express');
var bodyparser = require('body-parser');
var mysql = require('mysql');
var fs = require('fs');

var client = mysql.createConnection({
    user:'root',
    password:'q1w2e3r4',
    database:'restdb'
});

client.connect();

client.query('Insert into userinfo (name, region) values (?, ?)',['chakan','Apart'],function(){
    console.log('Insert DONE!!');
})

client.query('select * from userinfo',function(error,result,fields){
    if(error){
        console.log('error: '+ error);
    }else{
        console.log(result);
    }
});

var app = express();

app.use(bodyparser.urlencoded({extended : false}));

http.createServer(app).listen(8000);
console.log('서버 실행 중');