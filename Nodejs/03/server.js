// 모듈 추출.
var http = require('http');

function serverStart(route){
    function OnRequest(req, res){
        // 요청경로 추출.
        var path = req.url;
        // 라우팅 함수 실행.
        route(path,res);
    }
    
    var server = http.createServer(OnRequest);
    server.on('request', OnRequest);
    server.listen(8000);
    console.log('서버 실행중..');
}

module.exports = {
    'serverStart' : serverStart
}

