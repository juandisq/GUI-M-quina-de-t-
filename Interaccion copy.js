const express = require('express'); // Ensure Express is imported
const bodyParser = require('body-parser'); // For parsing JSON bodies
const { SerialPort, ReadlineParser } = require('serialport'); // For Arduino communication

const app = express();
const port = 3000;
const baudRate = 9600;

// Middleware
app.use(bodyParser.json());
app.use(express.static(__dirname)); // Serve static files (like HTML)

// Set the correct COM port for your Arduino
const portName = 'COM5';
let arduinoPort;
let parser;

try {
    arduinoPort = new SerialPort({ path: portName, baudRate: baudRate });

    // Handle successful port opening
    arduinoPort.on('open', () => {
        console.log(`Connected to Arduino on port ${portName}`);
        // Initialize parser only after port opens
        parser = arduinoPort.pipe(new ReadlineParser({ delimiter: '\r\n' }));
    });

    // Handle serial port errors
    arduinoPort.on('error', (err) => {
        console.error(`Serial Port Error: ${err.message}`);
    });
} catch (err) {
    console.error(`Failed to initialize SerialPort: ${err.message}`);
}

// Serve the HTML file
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/prueba copy.html'); // Ensure the HTML file exists
});

// Endpoint to send commands to Arduino
app.post('/send-to-arduino', (req, res) => {
    const command = req.body.command;
    console.log('Command received:', command);

    if (!arduinoPort || !arduinoPort.isOpen) {
        console.error('Arduino not connected.');
        return res.status(500).send('Arduino not connected.');
    }

    arduinoPort.write(command + '\n', (err) => {
        if (err) {
            console.error('Error writing to Arduino:', err.message);
            return res.status(500).send('Failed to send command to Arduino.');
        }

        console.log('Command sent to Arduino:', command);

        // Wait for Arduino response
        if (parser) {
            parser.once('data', (response) => {
                console.log('Response from Arduino:', response);
                res.send(response); // Send the response back to the client
            });
        } else {
            console.error('Parser not initialized.');
            res.status(500).send('Failed to read Arduino response.');
        }
    });
});

// Start the server
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
