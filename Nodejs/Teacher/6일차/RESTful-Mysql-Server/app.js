// 모듈 추출.
var mysql = require('mysql');

// DB 설정.
var client = mysql.createConnection({
    user : 'root',
    password : 'qweasd123',
    database : 'restdb'
});

// DB 연결.
client.connect();

// 데이터 확인.
client.query('SELECT * FROM UserInfo', function(error, result, fields) {
    if (error) {
        console.log('Error: ' + error);
    } else {
        console.log(result);
    }
});