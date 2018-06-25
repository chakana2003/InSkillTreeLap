var http = require('http');     // http 모듈
var fs = require('fs');         // 파일 시스템 모듈.
var url = require('url');       // url 모듈.
var router = require('router');

function OnRequest(request,response){
    console.log('클라이언트 요청 발생');
    console.log(url.parse(request.url));

    // 라우팅.
    if(request.url == '/'){
        fs.readFile(__dirname + '/baseHtml.html',function(error,html){
        // 클리아언트 요청 응답.
        // 헤더 및 데이터 설정.
        response.writeHead(200,{'Content-Type' : 'text/html'});
        response.write(html);
        // 응답 종료.
        response.end();
        });
    }else if(request.url == '/favicon.ico'){
        // 파비콘 아이콘 불러와 전달.
        fs.readFile('./1.png', function(error, data){
            response.writeHead(200,{'Content-Type' : 'image/png'});
            response.write(data);
        
            response.end();
        });
    }
}

// 서버 객체 생성.
var server = http.createServer(OnRequest);

// 8000번 포트 사용.
server.listen(8000);

console.log('서버 실행중');