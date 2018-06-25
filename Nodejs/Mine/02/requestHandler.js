var fs = require('fs');

function start(req, res){
    fs.readFile('./baseHtml.html',function(error, html){
        // 응답 ( 상태코드 : 전달할 데이터 유형(MIME 타입)).
        res.writeHead(200, {'Content-Type' : 'text/html'});
        res.write(html);
        res.end();
    });
}

function favicon(req, res){
    // 이미지 파일 읽어서 요청 처리.
    fs.readFile('./1.png',function(error, image){
        res.writeHead(200, {'Content-Type' : 'image/png'});
        res.write(image);
        res.end();
    })
}

module.exports = {
    start : start,
    favicon : favicon
}