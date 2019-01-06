const net = require('net')

const clients = []

const server = net.createServer()

server.on('connection', client) =>
{
    client.log('CONNECTED: ' + client.remoteAddress + ':' + client.remotePort);
    clients.push(client);

    client.on('data', data 
    {
    
    });
});

server.listen(8080, '0.0.0.0', () =>
{
  console.log(`tcp server is UP on ${port}`)
})
