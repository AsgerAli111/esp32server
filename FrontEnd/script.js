const ESP32_IP = 'http://<ESP32-IP-ADDRESS>';  // Replace with your ESP32 IP address

function togglePin(pin, state) {
    const url = `${ESP32_IP}/pin/${pin}/${state}`;
    fetch(url)
    .then(response => response.text())
    .then(data => {
        alert(`Pin ${pin} is now: ${state.toUpperCase()}`);
    })
    .catch(error => {
        console.error('Error:', error);
    });
}

function toggleAll(state) {
    const pins = [13, 14, 18, 21, 22, 23, 25, 19];
    pins.forEach(pin => {
        togglePin(pin, state);
    });
}
