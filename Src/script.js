//Variables declaration///////////////////////////

//Global variables
let bpm = 145;
const sequence = sequenceControl();

//BPM variables
const bpmSlider = document.getElementById('bpm-slider');
const bpmInput = document.getElementById('bpm-input');
const bpmValue = document.getElementById('bpm-value');
const resetBpmButton = document.getElementById('reset-bpm-button');
const buttonIds = ['show-bpm1', 'show-bpm2', 'show-bpm3', 'show-bpm4'];
const blinkers = buttonIds.map((buttonId, index) => bpmBlinker(buttonId, index));

//COLOR variables
const red_slider = document.getElementById('red-slider');
const green_slider = document.getElementById('green-slider');
const blue_slider = document.getElementById('blue-slider');
const redValue = document.getElementById('red-value');
const greenValue = document.getElementById('green-value');
const blueValue = document.getElementById('blue-value');
const colorPicker = document.getElementById('html5colorpicker');
const colorButtons = document.querySelectorAll('.color-shortcut-button');
/////////////////////////////////////////////////

//Events/////////////////////////////////////////

//Global events
document.addEventListener('keyup', (event) => {
    console.log(event.key);
    if (event.key === 'r') {
        resetBpmButton.style.backgroundColor = "";
    }
}, false);
document.addEventListener('keydown', (event) => {
    console.log(event.key);
    if (event.key === 'r') {
        sequence.restart();
        resetBpmButton.style.backgroundColor = "red";
    }
}, false);

//BPM events
bpmSlider.addEventListener('input', () => {
    update_bpm(bpmSlider.value);
});
bpmInput.addEventListener('focusout', () => {
    update_bpm(bpmInput.value);
});
resetBpmButton.addEventListener('click', sequence.restart);

//COLOR events
red_slider.addEventListener('input', change_mixed_color);
green_slider.addEventListener('input', change_mixed_color);
blue_slider.addEventListener('input', change_mixed_color);
colorPicker.addEventListener('input', update_color);
colorButtons.forEach((button) => {
    button.addEventListener('click', () => {
        if (button.textContent === "RANDOM") {
            const randomColor = HSVtoRGB(Math.random(), 1, 1);
            button.style.backgroundColor = 'rgb(' + randomColor.r + ',' + randomColor.g + ',' + randomColor.b + ')';
            button.style.color = "white";
            colorPicker.value = "#" + randomColor.rHex + randomColor.gHex + randomColor.bHex;
        } else {
            colorPicker.value = colorNameToHex(button.innerText);
        }
        update_color();
    });
});
/////////////////////////////////////////////////

//Functions//////////////////////////////////////

//BPM functions
function update_bpm(newBpm) {
    window.bpm = newBpm;
    //logThis("BPM set to : " + bpm);
    //update slider position
    bpmSlider.value = Number(newBpm);
    //update number input
    bpmInput.value = `${Number(newBpm).toFixed(1)}`;
    clearInterval(newBpm);
    sequence.start(newBpm);
}

function bpmBlinker(buttonId) {

    const button = document.getElementById(buttonId);
    let bpm = window.bpm;
    let isVisible = true;
    let intervalId;


    function toggleVisibility() {// Function to toggle the button's visibility
        isVisible = !isVisible;
        button.style.visibility = isVisible ? 'visible' : 'hidden';
    }

    function setVisible() {// Function to toggle the button's visibility
        isVisible = !isVisible;
        button.style.visibility = 'visible';
    }

    function setInvisible() {// Function to toggle the button's visibility
        button.style.visibility = 'hidden';
    }

    function updateInterval() {// Function to update the blinking interval based on subdivision
        clearInterval(intervalId);
        const interval = (60 / bpm) * 1000;
        intervalId = setInterval(toggleVisibility, interval);
    }

    function setBPM(newBpm) {// Function to change the BPM dynamically
        bpm = newBpm;
        updateInterval();
    }

    return {setBPM, toggleVisibility, setVisible, setInvisible};// Expose functions
}

function tapBpm() {
    const timeout = 5000;
    let timeoutHandle = null;
    let pressCount = 0;
    const tryNumber = 4;
    let spaceBarPressTimestamps = [];
    let intervalSum = 0;

    const tapBpmButton = document.getElementById("tap-bpm-button");

    function handleTapBpmPress() {
        // Function to handle space bar press and calculate BPM
        const currentTime = Date.now();

        if (pressCount < tryNumber) {
            if (pressCount === 0) {
                timeoutHandle = setTimeout(resetTapBpm, timeout);
            }
            if (pressCount > 0) {
                const interval = currentTime - spaceBarPressTimestamps[pressCount - 1];
                intervalSum += interval;
            }
            logThis("Press " + (pressCount + 1));
            spaceBarPressTimestamps.push(currentTime);
            pressCount++;
            tapBpmButton.style.backgroundColor = "red";
            tapBpmButton.innerText = "Tap " + (pressCount) + "/" + tryNumber + " BPM";

            if (pressCount === tryNumber) {
                const averageInterval = intervalSum / (tryNumber - 1); // Calculate average of three intervals
                logThis(`Average time between presses: ${averageInterval} milliseconds`);
                let foundBpm = 60000 / (averageInterval);
                logThis(`Bpm : ${foundBpm}`);
                update_bpm(Math.round(foundBpm));
                clearTimeout(timeoutHandle);
                tapBpmButton.style.backgroundColor = "";
                tapBpmButton.innerText = "Tap BPM";
                tapBpm();
            }
        }
    }

    function resetTapBpm() {
        logThis("timeout reset");
        pressCount = 0;
        spaceBarPressTimestamps = [];
        intervalSum = 0;
        tapBpmButton.style.backgroundColor = "";
        tapBpmButton.innerText = "Tap BPM";
    }

    document.addEventListener('keydown', (event) => {
        if (event.key === ' ' && pressCount < tryNumber) {
            handleTapBpmPress();
            document.activeElement.blur();
        }
    });
    tapBpmButton.addEventListener('click', handleTapBpmPress);
}

function sequenceControl() {
    let index = 0;
    let intervalHandle = null;
    let bpm = window.bpm;

    function start(startBpm) {
        bpm = startBpm;
        if (intervalHandle !== null) {
            clearInterval(intervalHandle);
        }
        intervalHandle = setInterval(next, ((60 / bpm) * 1000));
    }

    function stop() {
        clearInterval(intervalHandle);
    }

    function next() {
        updateBlinkersVisibility(index);
        index = (index + 1) % blinkers.length;
    }

    function restart() {
        logThis("sequence reset with bpm" + bpm);
        index = 0;
        next();
        start(bpm);
    }

    function updateBlinkersVisibility(currentIndex) {
        for (let i = 0; i < blinkers.length; i++) {
            if (i === currentIndex) {
                blinkers[i].setInvisible();
            } else {
                blinkers[i].setVisible();
            }
        }
    }

    return {start, restart, stop};
}


//COLOR functions
function change_mixed_color() {
    const box = document.getElementById('color_mixed');

    let red = red_slider.value;
    let green = green_slider.value;
    let blue = blue_slider.value;

    redValue.textContent = red.toString();
    greenValue.textContent = green.toString();
    blueValue.textContent = blue.toString();

    box.style.backgroundColor = `rgb(${red},${green},${blue})`;
}

function update_color() {
    const color = colorPicker.value;
    const box = document.getElementById('color_mixed');
    box.style.backgroundColor = color;

    red_slider.value = parseInt(color.substring(1, 3), 16);
    green_slider.value = parseInt(color.substring(3, 5), 16);
    blue_slider.value = parseInt(color.substring(5, 7), 16);
    redValue.textContent = parseInt(color.substring(1, 3), 16);
    greenValue.textContent = parseInt(color.substring(3, 5), 16);
    blueValue.textContent = parseInt(color.substring(5, 7), 16);
    logThis(color);
}

function initColorButtons() {
    for (let i = 0; i < colorButtons.length; i++) {//change buttons color based on their names
        const button = colorButtons[i];
        const hex = colorNameToHex(button.innerText);
        button.style.backgroundColor = hex;
        const r = parseInt(hex.toString().substring(1, 3), 16);
        const g = parseInt(hex.toString().substring(3, 5), 16);
        const b = parseInt(hex.toString().substring(5, 7), 16);
        const yiq = ((r * 299) + (g * 587) + (b * 114)) / 1000;
        button.style.color = (yiq > 125) ? 'black' : 'white';
    }
}

//Server functions
function serverCom() {
    const gateway = `ws://${window.location.hostname}/ws`;
    const serverStatusText = document.getElementById('server-status-text');
    let websocket = null;
    window.addEventListener('load', onload);

    function onload(event) {
        initWebSocket();
    }

    function initWebSocket() {
        logThis('Trying to open a WebSocket connection…');
        websocket = new WebSocket(gateway);
        websocket.onopen = onOpen;
        websocket.onclose = onClose;
        websocket.onmessage = onMessage;
    }

    function onOpen(event) {
        logThis('Connection opened');
        serverStatusText.textContent = "Connected";
        getValues();
    }

    function onClose(event) {
        logThis('Connection closed');
        serverStatusText.textContent = "Disconnected";
        setTimeout(initWebSocket, 2000);
    }

    function getValues() {
        websocket.send("getValues");
    }

    /*
    function updateSliderPWM(element) {
        var sliderNumber = element.id.charAt(element.id.length - 1);
        var sliderValue = document.getElementById(element.id).value;
        document.getElementById("sliderValue" + sliderNumber).innerHTML = sliderValue;
        logThis(sliderValue);
        websocket.send(sliderNumber + "s" + sliderValue.toString());
    }
    */

    function onMessage(event) {
        logThis(event.data);
        let myObj = JSON.parse(event.data);
        let keys = Object.keys(myObj);
        //for (let i = 0; i < keys.length; i++) {
        //    let key = keys[i];
        //    document.getElementById(key).innerHTML = myObj[key];
        //    document.getElementById("slider" + (i + 1).toString()).value = myObj[key];
        //}
    }
}


//TOOLS functions
function colorNameToHex(colour) {
    var colours = {
        "aliceblue": "#f0f8ff",
        "antiquewhite": "#faebd7",
        "aqua": "#00ffff",
        "aquamarine": "#7fffd4",
        "azure": "#f0ffff",
        "beige": "#f5f5dc",
        "bisque": "#ffe4c4",
        "black": "#000000",
        "blanchedalmond": "#ffebcd",
        "blue": "#0000ff",
        "blueviolet": "#8a2be2",
        "brown": "#a52a2a",
        "burlywood": "#deb887",
        "cadetblue": "#5f9ea0",
        "chartreuse": "#7fff00",
        "chocolate": "#d2691e",
        "coral": "#ff7f50",
        "cornflowerblue": "#6495ed",
        "cornsilk": "#fff8dc",
        "crimson": "#dc143c",
        "cyan": "#00ffff",
        "darkblue": "#00008b",
        "darkcyan": "#008b8b",
        "darkgoldenrod": "#b8860b",
        "darkgray": "#a9a9a9",
        "darkgreen": "#006400",
        "darkkhaki": "#bdb76b",
        "darkmagenta": "#8b008b",
        "darkolivegreen": "#556b2f",
        "darkorange": "#ff8c00",
        "darkorchid": "#9932cc",
        "darkred": "#8b0000",
        "darksalmon": "#e9967a",
        "darkseagreen": "#8fbc8f",
        "darkslateblue": "#483d8b",
        "darkslategray": "#2f4f4f",
        "darkturquoise": "#00ced1",
        "darkviolet": "#9400d3",
        "deeppink": "#ff1493",
        "deepskyblue": "#00bfff",
        "dimgray": "#696969",
        "dodgerblue": "#1e90ff",
        "firebrick": "#b22222",
        "floralwhite": "#fffaf0",
        "forestgreen": "#228b22",
        "fuchsia": "#ff00ff",
        "gainsboro": "#dcdcdc",
        "ghostwhite": "#f8f8ff",
        "gold": "#ffd700",
        "goldenrod": "#daa520",
        "gray": "#808080",
        "green": "#008000",
        "greenyellow": "#adff2f",
        "honeydew": "#f0fff0",
        "hotpink": "#ff69b4",
        "indianred ": "#cd5c5c",
        "indigo": "#4b0082",
        "ivory": "#fffff0",
        "khaki": "#f0e68c",
        "lavender": "#e6e6fa",
        "lavenderblush": "#fff0f5",
        "lawngreen": "#7cfc00",
        "lemonchiffon": "#fffacd",
        "lightblue": "#add8e6",
        "lightcoral": "#f08080",
        "lightcyan": "#e0ffff",
        "lightgoldenrodyellow": "#fafad2",
        "lightgrey": "#d3d3d3",
        "lightgreen": "#90ee90",
        "lightpink": "#ffb6c1",
        "lightsalmon": "#ffa07a",
        "lightseagreen": "#20b2aa",
        "lightskyblue": "#87cefa",
        "lightslategray": "#778899",
        "lightsteelblue": "#b0c4de",
        "lightyellow": "#ffffe0",
        "lime": "#00ff00",
        "limegreen": "#32cd32",
        "linen": "#faf0e6",
        "magenta": "#ff00ff",
        "maroon": "#800000",
        "mediumaquamarine": "#66cdaa",
        "mediumblue": "#0000cd",
        "mediumorchid": "#ba55d3",
        "mediumpurple": "#9370d8",
        "mediumseagreen": "#3cb371",
        "mediumslateblue": "#7b68ee",
        "mediumspringgreen": "#00fa9a",
        "mediumturquoise": "#48d1cc",
        "mediumvioletred": "#c71585",
        "midnightblue": "#191970",
        "mintcream": "#f5fffa",
        "mistyrose": "#ffe4e1",
        "moccasin": "#ffe4b5",
        "navajowhite": "#ffdead",
        "navy": "#000080",
        "oldlace": "#fdf5e6",
        "olive": "#808000",
        "olivedrab": "#6b8e23",
        "orange": "#ffa500",
        "orangered": "#ff4500",
        "orchid": "#da70d6",
        "palegoldenrod": "#eee8aa",
        "palegreen": "#98fb98",
        "paleturquoise": "#afeeee",
        "palevioletred": "#d87093",
        "papayawhip": "#ffefd5",
        "peachpuff": "#ffdab9",
        "peru": "#cd853f",
        "pink": "#ffc0cb",
        "plum": "#dda0dd",
        "powderblue": "#b0e0e6",
        "purple": "#800080",
        "rebeccapurple": "#663399",
        "red": "#ff0000",
        "rosybrown": "#bc8f8f",
        "royalblue": "#4169e1",
        "saddlebrown": "#8b4513",
        "salmon": "#fa8072",
        "sandybrown": "#f4a460",
        "seagreen": "#2e8b57",
        "seashell": "#fff5ee",
        "sienna": "#a0522d",
        "silver": "#c0c0c0",
        "skyblue": "#87ceeb",
        "slateblue": "#6a5acd",
        "slategray": "#708090",
        "snow": "#fffafa",
        "springgreen": "#00ff7f",
        "steelblue": "#4682b4",
        "tan": "#d2b48c",
        "teal": "#008080",
        "thistle": "#d8bfd8",
        "tomato": "#ff6347",
        "turquoise": "#40e0d0",
        "violet": "#ee82ee",
        "wheat": "#f5deb3",
        "white": "#ffffff",
        "whitesmoke": "#f5f5f5",
        "yellow": "#ffff00",
        "yellowgreen": "#9acd32"
    };
    if (typeof colours[colour.toLowerCase()] != 'undefined')
        return colours[colour.toLowerCase()];
    return false;
}

function HSVtoRGB(h, s, v) {
    let r, g, b, i, f, p, q, t;
    i = Math.floor(h * 6);
    f = h * 6 - i;
    p = v * (1 - s);
    q = v * (1 - f * s);
    t = v * (1 - (1 - f) * s);
    switch (i % 6) {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        case 5:
            r = v;
            g = p;
            b = q;
            break;
    }
    return {
        r: Math.round(r * 255),
        //force to 2 digits
        rHex: Math.round(r * 255).toString(16).padStart(2, '0'),
        g: Math.round(g * 255),
        gHex: Math.round(g * 255).toString(16).padStart(2, '0'),
        b: Math.round(b * 255),
        bHex: Math.round(b * 255).toString(16).padStart(2, '0'),
    };
}

function logThis(message) {
    // if we pass an Error object, message.stack will have all the details, otherwise give us a string
    if (typeof message === 'object') {
        message = message.stack || objToString(message);
    }

    console.log(message);

    // create the message line with current time
    const now = new Date();
    const date = now.getFullYear() + '-' + (now.getMonth() + 1) + '-' + now.getDate();
    const time = now.getHours() + ':' + now.getMinutes() + ':' + now.getSeconds();
    const dateTime = date + ' ' + time + ' ';

    const log = document.getElementById('logger');
    log.insertAdjacentHTML('afterbegin', "<p>" + dateTime + message + "<//p>");
    if (log.getElementsByTagName('p').length > 3) {    // Delete old logs
        log.removeChild(log.lastChild);
    }
}

function objToString(obj) {
    let str = 'Object: ';
    for (let p in obj) {
        if (obj.hasOwnProperty(p)) {
            str += p + '::' + obj[p] + ',\n';
        }
    }
    return str;
}

//Main///////////////////////////////////////////
initColorButtons();
sequence.start(bpm);
tapBpm();
const server = serverCom();
logThis("Script loaded");
