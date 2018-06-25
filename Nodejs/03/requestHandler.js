var fs = require('fs');

function start(){
    fa.readFile('./postReq.html',function(error,html){
        res.writeHead(200, {'Content-Type' : 'text/html'});
        res.write(html);
        res.end();
    })
}

function upload(){
    res.end();
}

function notFound(){

}

function favicon(res){
    fs.redFile('./images/SUM_M.png', function(error, favicon){
        res.writeHead(200, {'Content-Type' : 'image/png'});
        res.write(favicon);
        res.end();
    });
}

function show(res){
    fs.readFile('./image/test.png',function(error,image){
        res.writeHead(200, {'Content-Type' : 'image/png'});
        res.write(favicon);
        res.end();
    })
}

module.exports = {
    'start' : start,
    'upload' : upload,
    'notFound' : notFound,
    'favicon':favicon,
    'show' : show
}