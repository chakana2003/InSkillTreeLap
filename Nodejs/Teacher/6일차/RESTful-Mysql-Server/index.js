// 모듈 추출.
var server = require('./server');
var requestHandler = require('./requestHandler');
var database = require('./database');

// 핸들러 생성자.
function HandleCreator(method, path, callback) {
    this.method = method;
    this.path = path;
    this.callback = callback;
};

// 핸들 객체 설정.
var handle = [
    new HandleCreator('get', '/', requestHandler.start),
    new HandleCreator('get', '/user', requestHandler.showTotalUser),
    new HandleCreator('get', '/user/:id', requestHandler.showUser),
    new HandleCreator('post', '/user', requestHandler.insertUser),
    new HandleCreator('put', '/user/:id', requestHandler.updateUser),
    new HandleCreator('delete', '/user/:id', requestHandler.removeUser),
];

// 데이터베이스 연결.
requestHandler.connectDB(database);

// 서버 시작.
server.serverStart(handle);