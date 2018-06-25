var http = require('http');

var server = http.createServer(function(request,response){
    response.writeHead(200,{'Content-Type' : 'text/html'});
    response.write('Hello NodeJS Server');

    response.end();
});

server.listen(8000);

console.log('서버 실행중');