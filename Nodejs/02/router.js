function route(handle, path, req, res) {
    if(typeof handle[path] === 'function'){
        handle[path](req, res);
    }else{
        res.writeHead(404, {'Context-Type' : 'text/html'});
        res.write('404 not found');
        res.end();
    }
}

module.exports.route = route;