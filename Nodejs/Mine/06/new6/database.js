var mysql = require('mysql');

var client = mysql.createConnection({
    user : 'root',
    password : 'q1w2e3r4',
    database : 'userdb'
});

client.connect(function(error){
    if(error){
        console.log('DB 연결 오류: '+error);
    }
});

var mysqlDB = (function(){
    var mysqlDB = {};

    mysqlDB.login = function(res,data){
        var query = 'select * from userinfo where id=? and pw=?';
        client.query(query,[data.userid, data.password],function(error,result){
            if(error){
                console.log("쿼리 검색 실패 : "+error);
                res.send("쿼리 검색 실패 : "+error);
            }else{
                if(result.length > 0){
                    console.log('로그인 성공');
                    res.send('로그인 성공');
                }else{
                    console.log('로그인 실패');
                    res.send('로그인 실패');
                }
                
            }
        });
    };

    mysqlDB.insert = function(res,data){
        var query = 'select * from userinfo where id = ?';
        client.query(query,[data.userid, data.password],function(error,result){
            if(result.length === 0){
                query = 'insert into userinfo set ?';
                client.query(query, data, function(error){
                    if(error){
                        console.log('사용자 추가 실패: '+error);
                        res.send('사용자 추가 실패 : '+error);
                    }else{
                        console.log('사용자 '+data.userid + ' 등록 완료');
                        res.send('사용자 '+data.userid+' 등록 완료');
                    }
                });
            }else{
                console.log('입력한 ID 가 이미 있습니다.');
                res.send('입력한 ID 가 이미 있습니다.');
            }
        })
    };

    return mysqlDB;
})();

module.exports = mysqlDB;