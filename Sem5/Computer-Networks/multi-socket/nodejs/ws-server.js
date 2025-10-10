const WebSocket = require('ws');
const wss = new WebSocket.Server({ port: 8080 });

const cipher = (txt, shift) => txt.replace(/[a-zA-Z]/g, c => 
    String.fromCharCode((c.charCodeAt(0) - (c < 'a' ? 65 : 97) + shift) % 26 + (c < 'a' ? 65 : 97)));

let clients = [], keys = [];

wss.on('connection', ws => {
    let id = clients.push(ws) - 1;
    ws.send('Enter your key:');
    
    ws.on('message', msg => {
        msg = msg.toString().trim();
        if (!keys[id]) return keys[id] = +msg;
        if (msg === 'Exit') return clients[1-id]?.send('Exit');
        clients[1-id]?.send(cipher(cipher(msg, -keys[id]), keys[1-id]));
    });
});

console.log('WebSocket server ready on port 8080');