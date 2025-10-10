const net = require('net');
const port = 1400;
const host = '127.0.0.1';
const SHIFT = Number.isFinite(parseInt(process.argv[2], 10)) ? parseInt(process.argv[2], 10) : 13;
function caesar(text, shift) {
  const s = ((shift % 26) + 26) % 26;
  return text
    .split('')
    .map((ch) => {
      const c = ch.charCodeAt(0);
      if (c >= 97 && c <= 122) return String.fromCharCode(((c - 97 + s) % 26) + 97);
      if (c >= 65 && c <= 90) return String.fromCharCode(((c - 65 + s) % 26) + 65);
      return ch;
    })
    .join('');
}
const server = net.createServer((socket) => {
  console.log('client connected');
  socket.on('data', (buf) => {
    const msg = buf.toString();
    console.log('received(encrypted):', msg);
    console.log('received(decrypted):', caesar(msg, -SHIFT));
    socket.write(caesar('connected', SHIFT));
  });
});
server.listen(port, host, () => console.log('server listening on', host, ':', port));
