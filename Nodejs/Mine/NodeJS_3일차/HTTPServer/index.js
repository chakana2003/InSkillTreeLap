// 모듈 추출.
var server = require('./server');
var router = require('./router');
var requestHandler = require('./requestHandler');

//라우팅할 때 사용할 객체.
var handle = {
    '/' : requestHandler.start,
    '/start' : requestHandler.start,
    '/upload' : requestHandler.upload,
    '/notFound' : requestHandler.notFound,
    '/favicon.ico' : requestHandler.favicon,
    '/show' : requestHandler.show
};

server.serverStart(handle, router.route);