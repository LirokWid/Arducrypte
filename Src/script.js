const bpmSlider = document.getElementById('bpm-slider');
const bpmInput = document.getElementById('bpm-input');
const bpmValue = document.getElementById('bpm-value');
const buttonGrid = document.getElementById('button-grid');

const resetBpmButton = document.getElementById('reset-bpm-button');

//global vars
let bpm = 140;

const red_slider = document.getElementById('red-slider');
const green_slider = document.getElementById('green-slider');
const blue_slider = document.getElementById('blue-slider');

const color_box = document.getElementById('color_mixed');

const data = {
    bpm: 145,
    animation: 'Hello, World!',
    getValue1: function () {
        return this.bpm;
    },
    getValue2: function () {
        return this.animation;
    },
};


red_slider.addEventListener('input', change_mixed_color);
green_slider.addEventListener('input', change_mixed_color);
blue_slider.addEventListener('input', change_mixed_color);


function change_mixed_color() {
    const box = document.getElementById('color_mixed');


    let red = red_slider.value;
    let green = green_slider.value;
    let blue = blue_slider.value;

    document.getElementById('red-value').textContent = red;
    document.getElementById('green-value').textContent = green;
    document.getElementById('blue-value').textContent = blue;


    box.style.backgroundColor = `rgb(${red},${green},${blue})`;
}


bpmSlider.addEventListener('input', () => {
    update_bpm(bpmSlider.value);
});
bpmInput.addEventListener('focusout', () => {
    update_bpm(bpmInput.value);
});


function update_bpm(newBpm) {
    window.bpm = newBpm;
    //console.log("BPM set to : " + bpm);
    //update slider position
    bpmSlider.value = Number(newBpm);
    //update number input
    bpmInput.value = `${Number(newBpm).toFixed(1)}`;
    clearInterval(newBpm);
    sequence = setInterval(nextSequence, ((60 / newBpm) * 1000));
}


function bpmBlinker(buttonId, index) {

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

const buttonIds = ['show-bpm1', 'show-bpm2', 'show-bpm3', 'show-bpm4'];
const blinkers = buttonIds.map((buttonId, index) => bpmBlinker(buttonId, index));

for (let i = 0; i < blinkers.length; i++) {
    blinkers[i].toggleVisibility();
}

let index = 0;
resetBpmButton.addEventListener('click', resetSequence);

document.addEventListener('keydown', (event) => {
    console.log(event.key);
    if (event.key === 'r') {
        resetSequence();
    }
}, false);


function resetSequence() {
    console.log("sequence reset with bpm" + window.bpm);
    index = 0;
    nextSequence();
    clearInterval(sequence);
    sequence = setInterval(nextSequence, ((60 / window.bpm) * 1000));
}

function tapBpm() {
    const timeout = 5000;
    let timeoutHandle;
    let pressCount = 0;
    const tryNumber = 4;
    let spaceBarPressTimestamps = [];
    let intervalSum = 0;

    const tapBpmButton = document.getElementById("tap-bpm-button");

    function handleTapBpmPress() {    // Function to handle spacebar press
        const currentTime = Date.now();

        if (pressCount < tryNumber) {
            if (pressCount === 0) {//start reset timout
                timeoutHandle = setTimeout(resetTapBpm, timeout);
            }

            if (pressCount > 0) {
                const interval = currentTime - spaceBarPressTimestamps[pressCount - 1];
                intervalSum += interval;
            }
            console.log("Press " + (pressCount + 1));
            spaceBarPressTimestamps.push(currentTime);
            pressCount++;

            if (pressCount === tryNumber) {
                const averageInterval = intervalSum / (tryNumber - 1); // Calculate average of three intervals
                console.log(`Average time between presses: ${averageInterval} milliseconds`);
                let foundBpm = 60000 / (averageInterval);
                console.log(`Bpm : ${foundBpm}`);
                update_bpm(Math.round(foundBpm));
                clearTimeout(timeoutHandle);
                tapBpm();
            }
        }
    }

    function resetTapBpm() {
        console.log("timeout reset");
        pressCount = 0;
        spaceBarPressTimestamps = [];
        intervalSum = 0;
    }

    document.addEventListener('keydown', (event) => {
        if (event.key === ' ' && pressCount < tryNumber) {
            handleTapBpmPress();
            document.activeElement.blur();
        }
    });

    tapBpmButton.addEventListener('click', (event) => {
        handleTapBpmPress();
    });
}

// Call the function to start listening for spacebar presses
tapBpm();


function nextSequence() {
    updateBlinkersVisibility(index);
    index = (index + 1) % blinkers.length;
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

// Call nextSequence() at regular intervals
let sequence = setInterval(nextSequence, ((60 / bpm) * 1000));
