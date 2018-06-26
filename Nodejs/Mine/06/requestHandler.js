var mysqlDB = require('./database');

function ConnectDB(db){
    mysqlDB = db;
};

function start(req,res){
    res.redirect('/user');
};

function showTotalUser(req,res){
    mysqlDB.get(res);
};

function showUser(req,res){
    mysqlDB.get(res,req.params.id);
};

function insertUser(req,res){
    var data = {
        name : req.body.name,
        region : req.body.region
    }
    mysqlDB.insert(res,data);
};
function updateUser(req,res){};
function removeUser(req,res){};

module.exports = {
    ConnectDB : ConnectDB,
    start : start,
    showTotalUser : showTotalUser,
    showUser : showUser,
    insertUser : insertUser,
    updateUser : updateUser,
    removeUser : removeUser
}