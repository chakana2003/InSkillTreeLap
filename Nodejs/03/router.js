var server = require('./server');
var router = require('./router');
var requestHandler = require('./requestHandler');

var handle = {
    '/' : requestHandler.start,
    '/start' : requestHandler.start,
    '/upload' : requestHandler.upload,
    '/notFound' : requestHandler.notFound
};

function start(res){
    res.writeHead(200, {'Content-Type':'text/html'});
    res.write('Hello NodeJS');
    res.end;
}

function route(handle, path, res){
    if (typeof handle[path] === 'function'){
        handle[path](res);
    }else{
        //오류
        handle['/notFound'](res);
    }
}

module.exports = {
    route : route
}