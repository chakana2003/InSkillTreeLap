var fs = require('fs');

function start(req,res){
    fs.readFile('./postReq.html',function(error,html){
        res.send(html);
    });
}

function upload(req,res){
    fs.rename(req.files.image.path, './image/show/png',function(error){
        res.send('<img src="/show" />');
    })
}

function show(req,res){
    fs.readFile('./image/show.png', function(error,image){
        if(error) res.send(error + '\n');
        else res.send(image);
    })
}

module.exports = {
    'start' : start,
    'upload' : upload,
    'show' : show
}