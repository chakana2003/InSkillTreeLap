// 모듈 추출.
var fs = require('fs');

// path:/, /start 처리.
function start(req, res) {
    
    // html 파일 읽어서 요청 처리.
    fs.readFile('./baseHtml.html', function(error, html){
        // 응답. (상태코드 : 전달할 데이터 유형(MIME 타입)).
        res.writeHead(200, { 'Content-Type' : 'text/html' } );
        res.write(html);
        res.end();
    });
}

// path: /favicon.ico
function favicon(req, res) {
    // 이미지 파일 읽어서 요청 처리.
    fs.readFile('./favicon_ronniej.png', function(error, image){
        // 응답. (상태코드 : 전달할 데이터 유형(MIME 타입)).
        res.writeHead(200, { 'Content-Type' : 'image/png' } );
        res.write(image);
        res.end();
    });
}

// 모듈 내보내기.
module.exports = {
    'start' : start,
    'favicon' : favicon
}