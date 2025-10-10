const net = require('net');
const _ = require('lodash');

const cipher = (txt, shift) => txt.replace(/[a-zA-Z]/g, c => 
    String.fromCharCode((c.charCodeAt(0) - (c < 'a' ? 65 : 97) + shift) % 26 + (c < 'a' ? 65 : 97)));

let clients = [], keys = [];

net.createServer(s => {
    let id = clients.push(s) - 1;
    console.log(`Client${id + 1} connected`);
    s.write('Enter your key:');
    
    s.on('data', d => {
        let msg = d.toString().trim();
        if (!keys[id]) return keys[id] = +msg, console.log(`Client${id + 1} key=${keys[id]}`);
        if (msg === 'Exit') return clients[1-id]?.write('Exit'), console.log('Chat ended');
        
        let decrypted = cipher(msg, -keys[id]);
        console.log(`From Client${id + 1}:`, decrypted);
        clients[1-id]?.write(cipher(decrypted, keys[1-id]));
    });
}).listen(8080, () => console.log('Server ready...'));