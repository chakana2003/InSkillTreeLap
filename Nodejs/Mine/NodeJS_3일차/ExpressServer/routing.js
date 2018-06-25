var express = require('express');
var http = require('http');
var bodyParser = require('body-parser')

var app = express();

var routerA = express.Router();
var routerB = express.Router();

routerA.get('/index',function(req,res){
    res.send('Index Page A');
});

routerA.post('/login',function(req,res){
    var name = req.body.name;
    var region = req.body.region;

    var data = {
        'name' : name,
        'region' : region
    };

    res.send(data);
});

routerB.get('/index',function(req,res){
    res.send('Index Page B');
});

app.use(bodyParser.urlencoded({extended : false}));
app.use('/a', routerA);
app.use('/b',routerB);
//app.use(bodyParser());


app.get('/q',function(req,res){
    res.send('<a href="/w">Go to W</a>');
});

app.get('/w',function(req,res){
    res.send('<a href="/q">Go to Q</a>');
});

app.get('/page/:id', function(req,res){
    var id = req.params.id;
    res.send(id);
});

http.createServer(app).listen(8000);
console.log('서버 실행 중');