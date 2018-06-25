var server = require('./server');
var requestHandler = require('./requestHandler');

var handle = {
    '/' : requestHandler.start,
    '/start' : requestHandler.start,
    '/upload' : requestHandler.upload,
    '/show' : requestHandler.show
};

