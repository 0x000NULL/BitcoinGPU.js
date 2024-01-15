const express = require('express');
const { addTask } = require('./producer');
const { processTask } = require('./consumer');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

app.post('/tasks', async (req, res) => {
  const task = req.body;
  await addTask(task);
  res.status(201).send('Task added');
});

app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
  processTask();
});