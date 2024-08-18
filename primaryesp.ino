<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Control Interface</title>
    <style>
        /* Add your CSS styling here */
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            text-align: center;
        }
        button {
            padding: 10px;
            margin: 5px;
            font-size: 16px;
        }
    </style>
</head>
<body>
    <h1>ESP32 Control Interface</h1>
    <button onclick="toggleGPIO(2)">Toggle GPIO 2</button>
    <button onclick="toggleGPIO(4)">Toggle GPIO 4</button>
    <!-- Add more buttons as needed -->

    <script>
        function toggleGPIO(pin) {
            fetch(`http://your-esp32-ip/toggle?pin=${pin}`)
                .then(response => response.text())
                .then(data => console.log(data))
                .catch(error => console.error('Error:', error));
        }
    </script>
</body>
</html>
