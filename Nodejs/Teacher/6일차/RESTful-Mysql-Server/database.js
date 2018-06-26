// 모듈 추출.
var mysql = require('mysql');

// 연결 정보 설정.
var client = mysql.createConnection({
    user : 'root',
    password : 'qweasd123',
    database : 'restdb'
});

// 데이터베이스 연결.
client.connect();

// 데이터 베이스 객체 구현.
var mysqlDB = (function() {

    // 변수 선언.
    var mysqlDB = { };

    // 정보 요청 함수.
    mysqlDB.get = function(res, id) {
        console.log('DB Get Requested');

        if (id) {

            // 변수 가공.
            id = (typeof id === 'string') ? Number(id) : id;

            // 쿼리문.
            var query = 'select * from userinfo where id=?';

            // 쿼리 실행.
            client.query(query , id, function(error, result, fields){
                if (error) {
                    console.log('쿼리 실패 select * from userinfo where id=' + id);
                    res.send('쿼리 실패 select * from userinfo where id=' + id);
                } else {
                    console.log('결과: ' + JSON.stringify(result));
                    res.send(result);
                }
            });

        } else {

            // 쿼리문 작성.
            var query = 'select * from userinfo';

            // 쿼리 실행.
            client.query(query, function(error, result, fields){
                if (error) {
                    console.log('쿼리 실패 select * from userinfo');
                    res.send('쿼리 실패 select * from userinfo');
                } else {
                    console.log('결과: ' + result);
                    res.send(result);
                }
            });
        }
    };

    // 데이터 추가.
    mysqlDB.insert = function(res, data) {
        // 채워보세요.
    }
})();

// 모듈 내보내기.
module.exports = mysqlDB;