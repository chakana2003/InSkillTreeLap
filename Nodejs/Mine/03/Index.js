var server = require('./server');
var router = require('./router');
var requestHandler = require('./requestHandler')

var handle = {
    '/' : requestHandler.start,
    '/start' : requestHandler.start,
    '/upload' : requestHandler.upload,
    '/notFound' : requestHandler.notFound,
    '/favicon' : requestHandler.favicon,
    '/show' : requestHandler.show
};

server.serverStart();