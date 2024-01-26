const axios = require("axios");
let taskNum = 0; //starting tasknumber
var Mnemonic = require('bitcore-mnemonic'); //import for bitcoin mnemonic
const fs = require('fs'); //import for filesystem operations
let hexNum = 0;



function getNextTask() {// Make request for task
	axios
		.get("http://localhost:3000/tasks") //tobe replaced by server address
		.then((res) => let taskNum = res.data) //get the current task and assign it to "numTask"
        .catch((err) => console.log(err)) //error if need be
        export taskNum;
}

function getTaskFile() {//get the task start and stop
	if (taskNum = 0) {
		let NumStart = "0"
		let NumEnd = "10000"
	} else if(taskNum = 1) {
		let NumStart = "10001"
		let NumEnd = "20000";
	}//need to find a better way to do this

}

function addressesToArray() {
    var fs = require('fs');
    fs.readFile('addresses.txt', function (err, data) {
        if (err) throw err;
        var addressarray = data.toString().split("\n");
        export addressarray;
    });
}

//incrementing alphanumeric

const A = 65
const Z = 90
const ZERO = 48
const NINE = 57

const isDigit = (char) => char >= 48 && char <= 57

const codeToChar = (code) => String.fromCharCode(code)
const setChar = (index, char, str) => {
    const charArr = [...str]
    charArr.splice(index, 1, char)
    return charArr.join('')
}

const areAllNine = (str) => {
    return str.split("").filter((char) => char.charCodeAt(0) === NINE).length === str.split("").length;
};

const areAllNineAndZ = (str) => {
    return str.split("").filter((char) => isDigit(char.charCodeAt(0))).length === str.split("").filter((char) => char.charCodeAt(0) === NINE).length && str.split("").filter((char) => !isDigit(char.charCodeAt(0))).length === str.split("").filter((char) => char.charCodeAt(0) === Z).length;
};

const incDigit = (char) => char + 1 > NINE ? ZERO : char + 1
const incLetter = (char) => char + 1 > Z ? A : char + 1

const increment = (str, place = str.length - 1) => {
    if (place < 0) return str;

    if (areAllNine(str)) {
        return str.replace("9", "A").replace(/\9/gi, "0");
    }
    if (areAllNineAndZ(str)) {
        return str.replace("Z9", "ZA").replace(/\9/gi, "0");
    }

    const char = str.charCodeAt(place)

    const nextChar = isDigit(char) ? incDigit(char) : incLetter(char)

    const carry = nextChar - char !== 1;

    str = setChar(place, codeToChar(nextChar), str)

    if (carry)
        return increment(str, --place)
    else return str
}

export const incrementAlphanumeric = (str) => increment(str)

//end incrementing code. Call incrementAlphanumeric('999') > 'A00' --or-- incrementAlphanumeric('Z99') > 'AA0' --or-- incrementAlphanumeric('ZZ9') > 'ZZA' --or-- etc. for us itll be close to, depending on batch, incrementAplhanumeric('0000000000000000000000000000000000000000000000000000000000000000') > '11111111111111111111111111111111111111111111111111111111111111'





function matchKey() {//Will take generate priv key and generate the public key. If it matches a key from our list; will generate WIF and other info and save to file.
    var privateKey = PriveKeyString; //privkey export to function veriable
    var publicKey = privateKey.toPublicKey(); //convert privkey to public key
    var address = publicKey.toAddress(Networks.livenet); //req internet fyi; gets address
    
}

var publicKey = privateKey.toPublicKey();
var address = publicKey.toAddress(Networks.livenet);