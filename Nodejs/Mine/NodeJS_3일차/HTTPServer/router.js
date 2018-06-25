// 라우팅 처리 함수.
function route(handle, path, res, req) {
    // handle 객체에 저장된 값이 함수인지 확인.
    if (typeof handle[path] === 'function') {
        handle[path](res, req);
    } else {
        // 오류.
        handle['/notFound'](res);
    }
}

module.exports = {
    route : route
}