const net = require('net');
const prompt = require('prompt-sync')();

const cipher = (txt, shift) => txt.replace(/[a-zA-Z]/g, c => 
    String.fromCharCode((c.charCodeAt(0) - (c < 'a' ? 65 : 97) + shift) % 26 + (c < 'a' ? 65 : 97)));

let key, s = net.createConnection(8080, '127.0.0.1');

s.on('data', d => {
    let msg = d.toString().trim();
    if (msg === 'Enter your key:') {
        key = +prompt('Enter your key: ');
        s.write(key + '');
        console.log('Connected! Type "Exit" to quit.\n');
        while (true) {
            let input = prompt('You: ');
            s.write(cipher(input, key));
            if (input === 'Exit') break;
        }
    } else if (msg === 'Exit') {
        console.log('\nChat ended.');
        process.exit(0);
    } else {
        console.log('Friend:', cipher(msg, -key));
    }
});