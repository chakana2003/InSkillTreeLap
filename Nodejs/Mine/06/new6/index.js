var server = require('./server');
var requestHandler = require('./requestHandler');
var database = require('./database');

function HandleCreator(method, path, callback){
    this.method = method;
    this.path = path;
    this.callback = callback;
};

var handle = [
    new HandleCreator('get','/register', requestHandler.showRegisterFrom),
    new HandleCreator('get','/',requestHandler.start),
    new HandleCreator('get', '/login',requestHandler.showLoginForm),
    new HandleCreator('post','/register',requestHandler.register),
    new HandleCreator('post', '/login', requestHandler.login)
];

requestHandler.connectDB(database);

server.serverStart(handle);