// 모듈 추출.
var http = require('http');

// 서버.
function serverStart(route, handle) {
    
    // 요청 처리 함수.
    function onRequest(req, res) {
        route(handle, req.url, req, res);
    }

    // 서버 객체 생성.
    // var server = http.createServer(onRequest);
    // server.listen(8000);
    http.createServer(onRequest).listen(8000);
    console.log('서버 실행중.');
}

// 모듈 내보내기.
module.exports = {
    'serverStart' : serverStart
}