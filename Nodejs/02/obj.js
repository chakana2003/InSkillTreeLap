var obj = {
    name : 'jack',
    showName : function(){
        console.log(this.name);
    }
}

obj.showName();
obj['showName']();


for(var key in obj){
    console.log(typeof key);
    console.log(typeof(key));
    console.log(typeof obj[key]);
}

console.log(false == 0);
console.log(false == '0');
console.log(false == undefined);
console.log(false == null);
console.log(false == '');

console.log(false === 0);
console.log(false === '0');
console.log(false === undefined);
console.log(false === null);
console.log(false === '');

function start(){
    console.log('start call');

}
function show(){
    console.log('show call');
}
var handler = {
    '/' : start,
    '/start' : start,
    '/show' : show
}

function router(path, handler){
    handler[path]();
}

router('/',handler);
router('/start',handler);
router('/show',handler);