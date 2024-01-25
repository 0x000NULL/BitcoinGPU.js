const axios = require("axios");
let taskNum = 0; //starting tasknumber
var Mnemonic = require('bitcore-mnemonic'); //import for bitcoin mnemonic
const fs = require('fs'); //import for filesystem operations



function getNextTask() {// Make request for task
	axios
		.get("http://localhost:3000/tasks") //tobe replaced by server address
		.then((res) => let taskNum = res.data) //get the current task and assign it to "numTask"
		.catch((err) => console.log(err)); //error if need be
}

function getTaskFile() {//get the task start and stop
	if (taskNum = 0) {
		let NumStart = "0"
		let NumEnd = "10000"
	} else if(taskNum = 1) {
		let NumStart = "10001"
		let NumEnd = "20000";
	}



}
var publicKey = privateKey.toPublicKey();
var address = publicKey.toAddress(Networks.livenet);