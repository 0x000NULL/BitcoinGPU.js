"use strict";

process.title = "Bitcoin GPU.js";

const readline = require('readline');
const { spawn } = require('child_process');


function credit(){
  console.log("=================================================================");
  console.log("Bitcoin GPU.js");
  console.log("=================================================================");
};


console.clear();
  credit();

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

console.log();
rl.question('Enter Number 1 to run Simplified view or Number 2 for Secondary view("May not work on some computers.") and press enter: ', (answer) => {
  rl.close();
  if (answer === '1') {
    spawn('node', ['./app1.js'], { stdio: 'inherit' });
  } else if (answer === '2') {
    spawn('node', ['./app2.js'], { stdio: 'inherit' });
  } else {
    console.log('Invalid input. Please enter either 1 or 2.');
  }
});
