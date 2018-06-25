// 모듈 추출.
var fs = require('fs');

// 기본 경로 요청 처리 함수.
function start(req, res) {
    fs.readFile('./postReq.html', function(error, html) {
        res.send(html.toString());
    });
}

function upload(req, res) {
    // connect-mulrtiparty 미들웨어 사용해서 업로드 이미지 파싱 처리.
    // 업로드된 파일 이름 변경.
    fs.rename(req.files.image.path, './image/show.png', function(error){
        res.send('<img src="/show" />');
    });
}

function show(req, res) {
    fs.readFile('./image/show.png', function(error, image) {
        if (error) res.send(error + '\n');
        else res.send(image);
    });
}

// 모듈 내보내기.
module.exports = {
    'start' : start,
    'upload' : upload,
    'show' : show
};