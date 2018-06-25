// 모듈 추출.
var fs = require('fs');
var formidable = require('formidable');

function start(res) {

    fs.readFile('./postReq.html', function(error, html){
        res.writeHead(200, {'Content-Type' : 'text/html'});
        //res.write('Hello NodeJS');
        res.write(html);
        res.end();
    });
}

// 이미지 업로드 함수.
function upload(res, req) {

    // formidable 모듈 초기화.
    var form = new formidable.IncomingForm();

    // 포스트 데이터 파싱(해석).
    form.parse(req, function(error, field, files){
        
        // 업로드된 이미지 파일 이름 바꾸기.
        fs.rename(files.image.path, './image/test.png', function(error){
            res.writeHead(200, {'Content-Type' : 'text/html'});
            res.write('<img src=/show />');
            res.end();
        });
    });
}

// 업로드된 이미지 보여주는 함수.
function show(res) {
    fs.readFile('./image/test.png', function(error, image){
        res.writeHead(200, { 'Content-Type' : 'image/png'} );
        res.write(image);
        res.end();
    });
}

function notFound(res) {
    res.writeHead(404, {'Content-Type' : 'text/html'});
    res.write('404 Page Not Found');
    res.end();
}

// 파비콘 전달 함수.
function favicon(res) {

    // 이미지 파일 읽기.
    fs.readFile('./image/favicon_ronniej.png', function(error, favicon){

        // 파비콘 이미지 전달.
        res.writeHead(200, { 'Content-Type' : 'image/png' });
        res.write(favicon);
        res.end();
    });
}

module.exports = {
    'start' : start,
    'upload' : upload,
    'notFound' : notFound,
    'favicon' : favicon,
    'show' : show
}