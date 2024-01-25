const express = require('express');
let taskNum = "0"; //number of set to give out next
let taskString;
const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

app.get('/tasks', async (req, res) => {
    console.log("request from ", "machine Name Variable", " recieved. Giving out task set", taskNum, ".");
    taskString = taskNum.toString(); 
    res.send(taskString);
    taskNum++;
    console.log("Next task set is set:", taskNum);
});



app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});