var http = require('http');

function serverStart(handle, route) {
    function onRequest(req, res){

        // 요청 경로 추출.
        var path = req.url;

        // 라우팅 함수 실행.
        route(handle, path, res, req);
    }

    var server = http.createServer();
    server.on('request', onRequest);
    server.listen(8000);
    console.log('서버 실행중');
}

// 모듈 내보내기.
module.exports = {
    'serverStart' : serverStart
}