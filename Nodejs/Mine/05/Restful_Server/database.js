var dummyDB = (function(){

    var dummyDB = {};
    var storage = [
        //{id : 1, name : 'yes', region : 'good'}
    ];
    var count = 1;

    dummyDB.get = function(id){

        if(id){
            id=(typeof id === 'string') ? Number(id) : id;

            for(var ix in storage){
                if(storage[ix].id == id){
                    return storage[ix];
                }
            }
        }else{
            return storage;
        }
    };

    dummyDB.insert = function(data){
        data.id = count++;
        storage.push(data);
        return data;
    };

    dummyDB.remove = function(id){
        id = (typeof id === 'string')?Number(id) : id;

        for(var ix in storage){
            if(stroage[ix].id === id){
                storage.splice(ix,1);

                return true;
            }
        }

        return false;
    };

    return dummyDB;

})();

module.exports = {
    dummyDB : dummyDB
};