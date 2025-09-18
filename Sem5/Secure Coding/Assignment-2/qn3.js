
const fs = require('fs');
const filePath = __dirname + '/file.txt';
let arr = [];
let i = 0;
while(i < 10000) {
    arr[i] = 0;
    i++;
}
let data = fs.readFileSync(filePath, 'utf-8');
let words = data.split(' ');

for(let k = 0; k < words.length; k++) {
    let word = words[k];

