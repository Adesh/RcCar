var connectionId = -1;

//var while_mouse_down = false;
var step = 1;

function setPosition(position) {
  var buffer = new ArrayBuffer(1);
  var uint8View = new Uint8Array(buffer);
  uint8View[0] = '0'.charCodeAt(0) + position;
  chrome.serial.send(connectionId, buffer, function() {});
}

function onReceive(receiveInfo) {
  if (receiveInfo.connectionId !== connectionId)
    return;
  //var uint8View = new Uint8Array(receiveInfo.data);
  //var value = uint8View[uint8View.length - 1] - '0'.charCodeAt(0);
  //var rotation = value * 18.0;
  //document.getElementById('image').style.webkitTransform = 'rotateZ(' + rotation + 'deg)';
}

function onError(errorInfo) {
  console.warn("Receive error on serial connection: " + errorInfo.error);
}

chrome.serial.onReceive.addListener(onReceive);
chrome.serial.onReceiveError.addListener(onError);

function onOpen(connectionInfo) {
  if (!connectionInfo) {
    setStatus('Could not open');
    return;
  }
  connectionId = connectionInfo.connectionId;
  setStatus('Connected');
  setPosition(0);
}

function setStatus(status) {
  document.getElementById('status').innerText = status;
}

function buildPortPicker(ports) {
  var eligiblePorts = ports.filter(function(port) {
    return !port.path.match(/[Bb]luetooth/);
  });

  var portPicker = document.getElementById('port-picker');
  eligiblePorts.forEach(function(port) {
    var portOption = document.createElement('option');
    portOption.value = portOption.innerText = port.path;
    portPicker.appendChild(portOption);
  });

  portPicker.onchange = function() {
    if (connectionId != -1) {
      chrome.serial.disconnect(connectionId, openSelectedPort);
      return;
    }
    openSelectedPort();
  };
}

function openSelectedPort() {
  var portPicker = document.getElementById('port-picker');
  var selectedPort = portPicker.options[portPicker.selectedIndex].value;
  chrome.serial.connect(selectedPort, onOpen);
}
/*
 w -> forward
 x -> reverse
 a -> left
 d -> right
 s -> stop
 1:9 -> speed
 */
	
function forward() {
  document.getElementById("f").style.backgroundColor = "#57fa78";
  //while_mouse_down = true;
  writeSerial("w");
  //if(while_mouse_down === true) forward();
}
function backward() {
  document.getElementById("b").style.backgroundColor = "#57fa78";
  //while_mouse_dowsn = true;
  writeSerial("x");
  //if(while_mouse_down === true) backward(); 
}
function left() {
  document.getElementById("l").style.backgroundColor = "#57fa78";
  //while_mouse_down = true;
   writeSerial("a");
  //if(while_mouse_down === true) left();
}
function right() {
  document.getElementById("r").style.backgroundColor = "#57fa78";
  //while_mouse_down = true;
  writeSerial("d"); 
}

function setSpeed() {
    var x = document.getElementById("speedometer").step;
    writeSerial("x");
}

function mouseUp() {
  //while_mouse_down = false;
  
  writeSerial("0");
  document.getElementById("l").style.backgroundColor = "#3498db";
  document.getElementById("r").style.backgroundColor = "#3498db";
  document.getElementById("f").style.backgroundColor = "#3498db";
  document.getElementById("b").style.backgroundColor = "#3498db";
}

//mouseUp()

function writeSerial(str) {
  chrome.serial.send(connectionId, convertStringToArrayBuffer(str), function(){});
  //chrome.serial.write(connectionId,  convertStringToArrayBuffer(str), function(){});
}
// Convert string to ArrayBuffer
function convertStringToArrayBuffer(str) {
  var buf=new ArrayBuffer(str.length);
  var bufView=new Uint8Array(buf);
  for (var i=0; i<str.length; i++) {
    bufView[i]=str.charCodeAt(i);
  }
  return buf;
}

window.onload = function() {
  //document.querySelector('#greeting').innerText ='Hello, World! It is ' + new Date();
  mouseUp();

  chrome.serial.getDevices(function(ports) {
    buildPortPicker(ports);
    openSelectedPort();
  });
  
  //document.getElementById("speedometer").step = "9";
  //setSpeed();
  
  document.getElementById("f").onmousedown=function(){forward();};
  document.getElementById("b").onmousedown=function(){backward();};
  document.getElementById("r").onmousedown=function(){right();};
  document.getElementById("l").onmousedown=function(){left();};
  
  document.getElementById("f").onmouseup=function(){mouseUp();};
  document.getElementById("b").onmouseup=function(){mouseUp();};
  document.getElementById("r").onmouseup=function(){mouseUp();};
  document.getElementById("l").onmouseup=function(){mouseUp();};
  
  document.onkeydown = function() {
    switch (window.event.keyCode) {
      case 37:
        //document.getElementById("l").style.color = "#57fa78";
        left(); 
        break;
      case 38:
       // document.getElementById("f").style.color = "#57fa78";
        forward();
        break;
      case 39:
        //document.getElementById("r").style.color = "#57fa78";
        right();
        break;
      case 40:
        //document.getElementById("b").style.color = "#57fa78";
        backward();
        break;
    }
  };
  
  document.onkeyup = function() {
    mouseUp();
  };
  
    
};
