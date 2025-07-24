const fs = require('fs');
const filePath = __dirname + '/file.txt';

fs.readFile(filePath, function(err, data) {
    if (err) {
        console.error('error while reading file:', err);
        return;
    }
    const words = data.toString().split(' ');
    const freq = {};
    for (let i = 0; i < words.length; i++) {
        const word = words[i].toLowerCase();
        if (word !== '') {
            if (freq[word] === undefined) {
                freq[word] = 1;
            } else {
                freq[word] = freq[word] + 1;
            }
        }
    }
    console.log('unique words and frequencies:');
    for (let count in freq) {
        console.log(count + ' : ' + freq[count]);
    }
});