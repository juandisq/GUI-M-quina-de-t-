const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const port = 3000;
const { SerialPort, ReadlineParser } = require('serialport');

app.use(bodyParser.json());

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/prueba.html');
});

// Endpoint to send data to Arduino
app.post('/send-to-arduino', (req, res) => {
    const command = req.body.command;
    console.log('Command received:', command);
    const responseFromArduino = simulateArduinoResponse(command); 
    res.send(responseFromArduino);
});

function simulateArduinoResponse(command) {
    return `Arduino executed: ${command}`;
}

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
