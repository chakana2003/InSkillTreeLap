// 모듈.
function addNumber(num1, num2){
    return num1 + num2;
}

function substract(num1, num2){
    return num1 - num2;
}

module.exports.addNumber = addNumber;
module.exports.substract = substract;

module.exports = {
    "addNumber" : addNumber,
    "substract" : substract
}

