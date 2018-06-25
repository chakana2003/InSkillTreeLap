var server = require('./server');
var router = require('./router');
var requestHandler = require('./requestHandler');

var handle = {
    '/' : requestHandler.start,
    '/start' : requestHandler.start,
    '/favicon.ico' : requestHandler.favicon
};

server.