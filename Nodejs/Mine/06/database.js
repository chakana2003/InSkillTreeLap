var mysql = require('mysql');

var client = mysql.createConnection({
    user : 'root',
    password : 'q1w2e3r4',
    database : 'restdb'
});

client.connect();

var mysqlDB = (function(){
    var mysqlDB = {      };

    mysqlDB.get = function(res,id){
        console.log('DB Get Requested');

        if(id){
            id = (typeof id === 'string') ? Number(id) : id;

            var query = 'select * from userinfo where id=?';

            client.query(query, id, function(error, result, fields){
                if(error){
                    console.log('쿼리 실패, 실패 id : ' +  id);
                    res.send('쿼리 실패, 실패 id : ' + id);
                }else{
                    console.log('결과 : ' + JSON.stringify(result));
                    res.send(result);
                }
            })
        }else{
            var query = 'select * from userinfo';
            client.query(query, function(error,result,fields){
                if(error){
                    console.log('쿼리 실패, 실패 id : ' +  id);
                    res.send('쿼리 실패, 실패 id : ' + id);
                }else{
                    console.log('결과 : ' + result);
                    res.send(result);
                }
            });
        }
    }

    mysqlDB.insert = function(res,data){
        console.log('DB Insert Requested');

        // INSERT INTO 테이블명 (컬럼명1, 컬럼명3, ...) VALUES (값1, 값3, ...);
        var query = 'insert into userinfo (name, region) values(?,?)';

        client.query(query, [data.name, data.region],function(error,result,fields){
            if(error){
                console.log('DB 추가 오류 : '+error);
                res.send('DB 추가 오류 : '+error);
            }else{
                console.log('DB 추가 완료');
                console.log(result);
                res.send('DB 추가 완료 : '+result);
                }
            }
        )

        // var query = 'insert into userinfo (name, region) values set ?';
        // client.query(query,data,function(error,result,fields){
        //     if(error){
        //         console.log('DB 추가 오류 : '+error);
        //         res.send('DB 추가 오류 : '+error);
        //     }else{
        //         console.log('DB 추가 완료');
        //         console.log(result);
        //         res.send('DB 추가 완료 : '+result);
        //     }
        // })
    }

    mysqlDB.remove = function(res,id){
        if(id){
            console.log('DB Delete Requested');

            id = (typeof id === 'string')? Number(id) : id;
            var query = 'delete from userinfo where id=' + id;
            client.query(query,function(error,result){
                if(error){
                    console.log('DB 삭제 오류: ' + error);
                    res.send('DB 삭제 오류 : '+error);
                }else{
                    console.log('DB 삭제 결과: '+result);
                    res.send('DB 삭제 결과 : '+result);
                }
            });
        }
    }

    return mysqlDB;
})();

module.exports = mysqlDB;