// http 모듈 임포트.
var http = require('http'); // http 모듈.
var fs = require('fs');     // 파일 시스템 모듈.
var path = require('path'); // path 모듈.
var url = require('url');   // url 모듈.
var router = require('./router');   //router 모듈.

// 응답시 호출할 함수 선언.
function onRequest(request, response) {

    console.log('클라이언트 요청 발생: ' + request.url);
    console.log(url.parse(request.url));

    // 라우팅.
    if (request.url == '/') {
        // HTML 파일을 읽어와서 전달하기.
        var htmlPath = path.join(__dirname, "baseHtml.html");
        // fs.readFile(__dirname + '/baseHtml.html', function(error, html){
        fs.readFile(htmlPath, function(error, html){
            // 클라이언트 요청 응답.
            // 헤더 및 데이터 설정.
            response.writeHead(200, {'Content-Type' : 'text/html'});
            response.write(html);
            // 응답 종료.
            response.end();
        });
       
    } else if(request.url == '/favicon.ico') {

        // 파비콘 아이콘을 불러와서 전달하기.
        fs.readFile('./favicon_ronniej.png', function(error, data){
            response.writeHead(200, {'Content-Type' : 'image/png'});
            response.write(data);
            // 응답 종료.
            response.end();
        });
    }
}

// 서버 객체 생성.
var server = http.createServer(onRequest);

// 8000번 포트 사용.
server.listen(8000);

console.log('서버 실행중');