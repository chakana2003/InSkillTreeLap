// 라우트 처리 함수. path : /, /start, /show, /favicon.ico.
function route(handle, path, req, res) {
    
    // handle 객체 안에 처리 함수가 있는 확인하고 실행.
    if (typeof handle[path] === 'function') {
        handle[path](req, res);
    } else {
        // 404 페이지 찾을 수 없음 오류.
        res.writeHead(404, { 'Content-Type' : 'text/html'} );
        res.write('404 Not Found');
        res.end();
    }
}

// 모듈 내보내기.
module.exports.route = route;

//exports.route = route;
// module.exports = {
//     "route" : route
// }