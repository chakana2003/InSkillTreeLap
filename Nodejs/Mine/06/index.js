var server = require('./server');
var requestHandler = require('./requestHandler');
var database = require('./database');

function HandleCreater(method, path, callback){
    this.method = method;
    this.path = path;
    this.callback = callback;
};

var handle = [
  new HandleCreater('get','/',requestHandler.start),
  new HandleCreater('get','/user',requestHandler.showTotalUser),
  new HandleCreater('get','/user/:id',requestHandler.showUser),
  new HandleCreater('post','/user',requestHandler.insertUser),
  new HandleCreater('put','/user/:id',requestHandler.updateUser),
  new HandleCreater('delete','/user/:id',requestHandler.removeUser)  
];

server.serverStart(handle);