// 모듈 추출.
var http = require('http');

function startServer(route, handle){
    // 요청 처리 함수
    function onRequest(req,res){
        route(handle,req.url, req, res);
    }

    // 서버 객체 생성
    http.createServer(onRequest).listen(8000);
}