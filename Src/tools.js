function blinkButtonWithDynamicBPM(buttonId, initialBpm) {
    const button = document.getElementById(buttonId);

    // Initialize variables
    let bpm = initialBpm;
    let isVisible = true;
    let intervalId;

    // Function to toggle the button's visibility
    function toggleVisibility() {
        isVisible = !isVisible;
        button.style.visibility = isVisible ? 'visible' : 'hidden';
    }

    // Function to update the blinking interval
    function updateInterval() {
        clearInterval(intervalId);

        // Calculate the interval in milliseconds based on the current BPM
        const interval = ((60 / bpm) * 1000) / 2;

        // Restart the blinking interval
        intervalId = setInterval(toggleVisibility, interval);
    }

    // Initial interval setup
    updateInterval();

    // Function to change the BPM dynamically
    function setBPM(newBpm) {
        bpm = newBpm;
        updateInterval();
    }

    // Expose the setBPM function
    return {setBPM};
}


function sequence(blinkers){
    let index;
    function nextSeq{
        blinkers[i].
    }
    return {nextSeq}
}
//const blinker = blinkButtonWithDynamicBPM('tap-bpm-button', bpm); // Replace 'blinkButton' with your button's ID and set the initial BPM

