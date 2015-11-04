window.onload = function() {

// Get references to elements on the page.
var form = document.getElementById('control-form');
//var messageField = document.getElementById('message');
//var messagesList = document.getElementById('messages');
var socketStatus = document.getElementById('status');
var closeBtn = document.getElementById('close');

// Create a new WebSocket.
var socket = new WebSocket('ws://192.168.43.7:8888/command');

// Handle any errors that occur.
socket.onerror = function(error) {
    console.log('WebSocket Error: ' + error);
  };

// Show a connected message when the WebSocket is opened.
  socket.onopen = function(event) {
    socketStatus.innerHTML = 'Connected to: ' + event.currentTarget.URL;
    socketStatus.className = 'open';
};

// Show a disconnected message when the WebSocket is closed.
  socket.onclose = function(event) {
    socketStatus.innerHTML = 'Disconnected from WebSocket.';
    socketStatus.className = 'closed';
  };
window.addEventListener('mousedown', function(event)
    {
        switch (event.target.name) {
                case "left":
                    socketStatus.innerHTML = event.target.name;
                    socket.send('37');
                break;
                case "right":
                    socket.send('39');
                    socketStatus.innerHTML = event.target.name;
                break;
                case "forward":
                    socket.send('38');
                    socketStatus.innerHTML = event.target.name;
                break;
                case "back":
                    socket.send('40');
                    socketStatus.innerHTML = event.target.name;
                break;
                case "stop":
                    socket.send('32');
                    socketStatus.innerHTML = event.target.name;
                break;
                case "cam_up":
                    socket.send('65');
                    socketStatus.innerHTML = event.target.name;
                break;
                case "cam_down":
                    socket.send('90');
                    socketStatus.innerHTML = event.target.name;
                break;
        }
    },
false);
window.addEventListener('keydown', function(event) {
  switch (event.keyCode) {
    case 37: // Left
	socket.send('37');
	socketStatus.innerHTML = 'Left Key Pressed';
    break;

    case 38: // Up
	socket.send('38');
	socketStatus.innerHTML = 'Up Key Pressed';
    break;

    case 39: // Right
	socket.send('39');
	socketStatus.innerHTML = 'Right Key Pressed';
    break;

    case 40: // Down
      	socket.send('40');
	socketStatus.innerHTML = 'Down Key Pressed';
    break;
    case 32: //Space
        socket.send('32');
        socketStatus.innerHTML = 'Space Key Pressed';
    break;
    case 65: //a
        socket.send('65');
        socketStatus.innerHTML = 'A Key Pressed';
    break;
    case 90: //z
        socket.send('90');
        socketStatus.innerHTML = 'Z Key Pressed';
    break;

  }
}, false);

  // Close the WebSocket connection when the close button is clicked.
  closeBtn.onclick = function(e) {
    e.preventDefault();

    // Close the WebSocket.
    socket.close();

    return false;
  };

};
