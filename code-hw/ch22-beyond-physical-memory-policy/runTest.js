let { PythonShell } = require('python-shell');
let { plotChart } = require('./generateChart');

/*
Steps:
1. Run paging-policy scripts for each paging policy FIFO, LRU, OPT, RAND, CLOCK 
for a cache size in range of 1 to 10.
2. Collect data and plot in a graph
*/

// command format
// ./paging-policy.py -f vpn.txt -N -p LRU -C 10 -c
// output format
// FINALSTATS hits 514779   misses 70161   hitrate 88.01
const pagingPolicies = ['FIFO', 'LRU', 'OPT', 'RAND', 'CLOCK'];

// const scriptFile = 'paging-policy.py -f vpn.txt -N -p LRU -C 10 -c';
//=========Configuration options====================
const scriptFile = 'paging-policy.py';
const addressFile = 'vpn.txt';
const maxCacheSize = 10;
const imageFile = 'ls.png';
//====================================================

const runScript = (policy, cacheSize) => {
  return new Promise((resolve, reject) => {
    PythonShell.run(
      scriptFile,
      {
        mode: 'text',
        args: ['-f', addressFile, '-c', '-N', '-p', `${policy}`, '-C', `${cacheSize}`],
      },
      function (err, data) {
        if (err) {
          console.log(err);
          reject(err);
        }
        resolve(data[data.length - 1]);
      }
    );
  });
};

const getResult = async () => {
  let response = {};
  /*
  Structure of response object
  {
    FIFO: [12,13,14,....],
    LRU: [23, 34, 12, .....],
    .........
  }
  */

  for (policy of pagingPolicies) {
    response[policy] = [];
    for (let i = 1; i <= maxCacheSize; i++) {
      const result = await runScript(policy, i);
      const tokens = result.split(' ');
      response[policy].push(tokens[tokens.length - 1]);
    }
  }

  // plot a chart
  plotChart(response, 'ls trace', imageFile);
};

getResult();
