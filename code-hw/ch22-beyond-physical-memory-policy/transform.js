const fs = require('fs');
const readline = require('readline');
/*
1. Read file ls-trace.txt line by line
2. Filter out all the line starting with '=' character
3. For each line read character from column 4 to 11
4. convert all the character from hex string to a number
5. clear lower 12 bit with a bit mask of 0xfffff000
6. shift number by 12 bits to left
7. write that number to a file address.txt
*/

// Read file ls-trace.txt line by line
const file = 'ls-trace-test.txt';
const rl = readline.createInterface({
  input: fs.createReadStream(file),
  output: process.stdout,
  terminal: false,
});

rl.on('line', function (line) {
  // Filter out all the line starting with '=' character
  if (line.charAt(0) !== '=') {
    // For each line read character from column 4 to 11
    const hexString = line.substring(4, 11);
    // convert all the character from hex string to a number
    const intVal = parseInt(hexString, 16);

    // shift number by 12 bits to left to get page frame number
    const pfNumber = intVal >> 12;

    // console.log(`${hexString} -  ${intVal} - ${pfNumber}`);
    fs.appendFileSync('vpn-test.txt', pfNumber + '\n');
  }
});
