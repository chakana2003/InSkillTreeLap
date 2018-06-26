// DB 변수.
var mysqlDB;

// DB 연결 함수.
function connectDB(db) {
    mysqlDB = db;
};

// 요청 처리 함수.
function start(req, res) { }
function showTotalUser(req, res) { }
function showUser(req, res) { }
function insertUser(req, res) { }
function updateUser(req, res) { }
function removeUser(req, res) { }

// 모듈 내보내기.
module.exports = {
    connectDB : connectDB,
    start : start,
    showTotalUser : showTotalUser,
    showUser : showUser,
    insertUser : insertUser,
    updateUser : updateUser,
    removeUser : removeUser
};