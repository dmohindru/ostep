const QuickChart = require('quickchart-js');

const chartColors = {
  FIFO: {
    borderColor: 'blue',
    backgroundColor: 'rgba(255,255,255,0)',
  },
  LRU: {
    borderColor: 'green',
    backgroundColor: 'rgba(255,255,255,0)',
  },
  OPT: {
    borderColor: 'red',
    backgroundColor: 'rgba(255,255,255,0)',
  },
  RAND: {
    borderColor: 'black',
    backgroundColor: 'rgba(255,255,255,0)',
  },
  CLOCK: {
    borderColor: 'orange',
    backgroundColor: 'rgba(255,255,255,0)',
  },
};

const plotChart = (data, title, fileName) => {
  const datasetContent = {
    labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
    datasets: [],
  };
  for (const [key, value] of Object.entries(data)) {
    datasetContent.datasets.push({
      label: key,
      borderColor: chartColors[key].borderColor,
      backgroundColor: chartColors[key].backgroundColor,
      data: value,
    });
  }

  const config = {
    type: 'line',
    data: datasetContent,
    options: {
      responsive: true,
      plugins: {
        title: {
          display: true,
          text: 'Min and Max Settings',
        },
      },
      scales: {
        y: {
          min: 0,
          max: 100,
        },
      },
    },
  };

  const myChart = new QuickChart();
  myChart.setConfig(config).setWidth(1024).setHeight(768);
  myChart.toFile(fileName);
};

module.exports = { plotChart };
