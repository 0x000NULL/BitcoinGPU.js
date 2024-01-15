const taskQueue = require('./queue');

function addTask(data) {
  return taskQueue.add(data);
}

module.exports = { addTask };