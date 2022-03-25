const { execSync } = require('child_process');
const { plot, Plot } = require('nodeplotlib');
let time = 0;
let data = [];
let detailedData = [];

const test = (pages, tries) => {
  for (let p = 1; p < pages; p++) {
    let singleData = {
      page: p,
      accessTimes: [],
    };
    detailedData.push(singleData);
    for (let t = 1; t < tries; t++) {
      const output = execSync(`./p1 ${p} ${t}`, { encoding: 'utf-8' });
      let timeUsed = parseFloat(output);
      singleData.accessTimes.push(timeUsed);
      time += timeUsed;
    }
    data.push({
      pages: p,
      averageTime: time / tries,
    });
    time = 0;
    console.log(`DONE calculating for ${p} page(s)`);
  }

  console.log('Pages\t\tTime(ns)');
  console.log('----------------------------');
  data.forEach((stats) => {
    console.log(`${stats.pages}\t\t${stats.averageTime}`);
  });

  console.log(detailedData);
};

test(1024, 10);

plot([
  {
    x: data.map((d) => d.pages),
    y: data.map((d) => d.averageTime),
    type: 'bar',
  },
]);

/*test(30, 20);

plot([
  {
    x: data.map((d) => d.pages),
    y: data.map((d) => d.averageTime),
    type: 'bar',
  },
]);

test(30, 30);

plot([
  {
    x: data.map((d) => d.pages),
    y: data.map((d) => d.averageTime),
    type: 'bar',
  },
]);

test(30, 10);
*/

plot([
  {
    x: data.map((d) => d.pages),
    y: data.map((d) => d.averageTime),
    type: 'bar',
  },
]);
