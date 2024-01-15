//example; will move to miner

const taskQueue = require('./queue');

function processTask() {
  taskQueue.process(async (job) => {
    console.log('Processing job:', job.id);
    const result = await performTask(job.data);
    console.log('Job completed:', job.id);
    return result;
  });
}

async function performTask(data) {
  // Simulate a long-running task
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve('Task completed');
    }, 5000);
  });
}

module.exports = { processTask };
