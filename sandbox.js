var currentPosition_main = 0;
var currentPosition_left = 0;
var currentPosition_right = 0;
CARASEL_SPEED = 0.5;
MOVE_STEPS = 3;

// The names are ones that are not already in the carasel
var imageNamesNotPresent = ["stock6.png", "stock7.png"];
var titles = 
["<p>Enviromental Simulation Using CUDA Framework</p>", 
"<p>Database Creation, Ingest, and Management</p>",
"<p>UML For C++ Chess Implementation</p>",
"<p>Agile Development: Requirement Aquisiton</p>", 
"<p>Web Ajax Querys: Stock Data</p>",
"<p>Java Threaded Web Crawler</p>", 
"<p>Cisco Packet Tracer</p>"];


var description = 
["<p>This project used the CUDA Nvidia GPU framework in order to simulate the classic Predator-Prey problem. This program demonstrates how optimizations can be made, and how specialized hardware can increase the amount of parallelization possible.</p>", 
"<p>This project outlined the process of working as a team to manage a postgres database. This project demonstrates the difficulty in dealing with unreliable data, and crafting optimized, challenging queries.</p>",
"<p> This C++ project used an Object Oriented design in order to implement a full chess game. Some of the challenges were determining all possible legal moves, determining future move in advance, determining the best possible move, and implementing optimized starting positions.</p>",
"<p>This project involved working as a team to develop software in an agile like environment. This included stand-ups, sprints, requirement gathering, and reflection</p>", 
"<p>This project makes API calls to various hosts, in order to aggregate and visualize dataset. This project demonstrates data acquisition in the web domain</p>", 
"<p> This project used parallelization to crawl webpages, gathering the URLs. This project was restricted to certain domains, to be used only as an self auditing tool</p>", 
"<p> This project used the CISICO packet tracer program in order to setup a local network. This involved having a limited address space, utilizing NAT, DHCP, Switches, Routers and various hosts.</p>"];

var links = ["file:///Users/bennettlopez/Desktop/Portfolio_Project/CUDA/",
"file:///Users/bennettlopez/Desktop/Portfolio_Project/Database/",
"file:///Users/bennettlopez/Desktop/Portfolio_Project/Chess/",
"file:///Users/bennettlopez/Desktop/Portfolio_Project/Agile/",
"https://bennettlopez0101.github.io",
"file:///Users/bennettlopez/Desktop/Portfolio_Project/webCrawler/",
"file:///Users/bennettlopez/Desktop/Portfolio_Project/Packet_Traser/Final_Vid.mp4",];
var numberStrings = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"];

function main() {
    var rightArrow = document.getElementById('Right_Arrow');
    var leftArrow = document.getElementById('Left_Arrow');
    rightArrow.style.opacity = 0.6;
    leftArrow.style.opacity = 0.6;
    currentPosition_left = positionPreviewImages("right", "Left_Image", "Left-Preview");
}

function positionPreviewImages(position, imageID, containerID) {
    var image = document.getElementById(imageID);
    var container = document.getElementById(containerID);
    var width_image = image.clientWidth;
    var width_container = container.offsetWidth;
    // The size of the container minus the width
    var translation = width_image - width_container;
    
    if (position == "right") {
        image.style.right = translation + "px";
    }
    else {
        image.style.left = translation + "px";
    }
    
    return translation;
}

function movePaneLeft() {
    disableButtons(true);
    var currentCoverPosition = 650; 
    mainImage = document.getElementById('Main_Image');
    rightImage = document.getElementById('Right_Image');
    leftImage = document.getElementById('Left_Image');
    right_cover_image = document.getElementById('Right_Cover_Image');
    left_cover_image = document.getElementById('Left_Cover_Image');
    
    var centerContainer = document.getElementById("Center-Main");
    var leftContainer = document.getElementById("Left-Preview");
    var rightContainer = document.getElementById("Right-Preview");
    
    var centerContainerWidth = centerContainer.offsetWidth;
    var leftContainerWidth = leftContainer.offsetWidth;
    var rightContainerWidth = leftContainer.offsetWidth;
    
    
    var centerImageWidth = mainImage.clientWidth;
    var rightImageWidth = rightImage.clientWidth;
    var right_cover_ImageWidth = rightImage.clientWidth;
    
    var centerPaneLimit = ((centerContainerWidth - centerImageWidth) / 2) + centerImageWidth;
    var rightPaneLimit = (centerContainerWidth / 2) + (rightImageWidth / 2);
    var leftPaneLimit = currentPosition_left + 600;
    /* 500 is the default offset in #Right_cover_image*/
    var right_cover_limit = -1 * rightContainerWidth;
    var secondaryInterval = 10;
    var id = setInterval(frame, CARASEL_SPEED);

    function frame() {
        if (currentPosition_main > centerPaneLimit && currentPosition_left > leftPaneLimit && currentPosition_right > rightPaneLimit && currentCoverPosition < right_cover_limit) {
            clearInterval(id);
            unScrambleLetters("left");
            resetCarasel("left");
        } 
        else {
            if (currentPosition_main <= centerPaneLimit) {
                currentPosition_main = currentPosition_main + MOVE_STEPS;
                mainImage.style.right = currentPosition_main + "px";
            }
            if (currentPosition_left <= leftPaneLimit) {
                currentPosition_left = currentPosition_left + MOVE_STEPS;
                leftImage.style.right = currentPosition_left + "px";
            }
            if (currentPosition_right <= rightPaneLimit) {
                currentPosition_right = currentPosition_right + MOVE_STEPS;
                rightImage.style.right = currentPosition_right + "px";
            }
            if (currentCoverPosition >= right_cover_limit) {
                currentCoverPosition = currentCoverPosition - MOVE_STEPS;
                right_cover_image.style.left = currentCoverPosition + "px";
            }
            if (secondaryInterval === 0) {
                //scrambleLetters(20);
                secondaryInterval = 10;
            }
            else {
                secondaryInterval--;
            }
        }
    }
}

function movePaneRight() {
    disableButtons(true);
    var currentCoverPosition = 650;
    mainImage = document.getElementById('Main_Image');
    rightImage = document.getElementById('Right_Image');
    leftImage = document.getElementById('Left_Image');
    right_cover_image = document.getElementById('Right_Cover_Image');
    left_cover_image = document.getElementById('Left_Cover_Image');
    
    var left_cover_container = document.getElementById('Left-Cover');
    var centerContainer = document.getElementById("Center-Main");
    var leftContainer = document.getElementById("Left-Preview");
    var rightContainer = document.getElementById("Right-Preview");
    
    var centerContainerWidth = centerContainer.offsetWidth;
    var leftContainerWidth = leftContainer.offsetWidth;
    var rightContainerWidth = leftContainer.offsetWidth;
    var leftCoverContainerWidth = left_cover_container.offsetWidth;
    
    var centerImageWidth = mainImage.clientWidth;
    var rightImageWidth = rightImage.clientWidth;
    var right_cover_ImageWidth = rightImage.clientWidth;
    var leftImageWidth = leftImage.clientWidth;
    var left_cover_ImageWidth = left_cover_image.clientWidth;
    
    var centerPaneLimit = ((centerContainerWidth - centerImageWidth) / 2) + centerImageWidth;
    var leftPaneLimit = (centerContainerWidth / 2) + (leftImageWidth / 2);
    var rightPaneLimit = currentPosition_right + 600;
    /* 500 is the default offset in #Right_cover_image*/
    var left_cover_limit = currentCoverPosition - left_cover_ImageWidth + leftContainerWidth + leftCoverContainerWidth;
    var change = 0;
    var change2 = 0;
    var secondaryInterval = 10;
    
    var id = setInterval(frame2, CARASEL_SPEED);

    function frame2() {
        if (currentPosition_main > centerPaneLimit && change > leftPaneLimit && currentPosition_right > rightPaneLimit && left_cover_limit < change2) { //opacityDone && opacity <= 0) {
            clearInterval(id);
            unScrambleLetters("right");
            resetCarasel("right");
        } 
        else {
            if (currentPosition_main <= centerPaneLimit) {
                currentPosition_main = currentPosition_main + MOVE_STEPS;
                mainImage.style.left = currentPosition_main + "px";
            }
            if (change <= leftPaneLimit) {
                currentPosition_left = currentPosition_left - MOVE_STEPS;
                leftImage.style.right = currentPosition_left + "px";
                change = change + MOVE_STEPS;
            }
            if (currentPosition_right <= rightPaneLimit) {
                currentPosition_right = currentPosition_right + MOVE_STEPS;
                rightImage.style.left = currentPosition_right + "px";
            }
            if (left_cover_limit >= change2) {
                currentCoverPosition = currentCoverPosition - MOVE_STEPS;
                left_cover_image.style.right = currentCoverPosition + "px";
                change2 = change2 + MOVE_STEPS;
            }
            if (secondaryInterval === 0) {
                //scrambleLetters(20);
                secondaryInterval = 10;
            }
            else {
                secondaryInterval--;
            }
        }
    }
}

function resetCarasel(position) {
    mainImage = document.getElementById('Main_Image');
    rightImage = document.getElementById('Right_Image');
    leftImage = document.getElementById('Left_Image');
    right_cover_image = document.getElementById('Right_Cover_Image');
    left_cover_image = document.getElementById('Left_Cover_Image');
    
    var replacementImage = imageNamesNotPresent[0];
    imageNamesNotPresent.splice(0, 1);
    
    if (position == "left") {
        imageNamesNotPresent.push(left_cover_image.src);
        left_cover_image.src = leftImage.src;
        leftImage.src = mainImage.src;
        mainImage.src = rightImage.src;
        rightImage.src = right_cover_image.src;
        right_cover_image.src = replacementImage;
        
        
        currentPosition_main = 0;
        mainImage.style.removeProperty('right');
        currentPosition_left = positionPreviewImages("right", "Left_Image", "Left-Preview")
        currentPosition_right = 0;
        rightImage.style.removeProperty('right');
        right_cover_image.style.left = "2000px";
        left_cover_image.style.right = "2000px";
    }
    else {
        imageNamesNotPresent.push(right_cover_image.src);
        right_cover_image.src = rightImage.src;
        rightImage.src = mainImage.src;
        mainImage.src = leftImage.src;
        leftImage.src = left_cover_image.src;
        left_cover_image.src = replacementImage;
        
        currentPosition_main = 0;
        mainImage.style.removeProperty('left');
        currentPosition_left = positionPreviewImages("right", "Left_Image", "Left-Preview")
        currentPosition_right = 0;
        rightImage.style.removeProperty('left');
        right_cover_image.style.left = "2000px";
        left_cover_image.style.right = "2000px";
        
    }
    disableButtons(false);
}

function disableButtons(disable) {
    var rightBtn = document.getElementById('Right_Button').disabled = disable;
    var leftBtn = document.getElementById('Left_Button').disabled = disable;
    
}


// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/random
function getRandomInt(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min) + min);
}

function scrambleLetters(numLetters) {
    text_title = document.getElementById('Bottom_Title').innerHTML;
    text_description = document.getElementById('Bottom_Description').innerHTML;
    text_link = document.getElementById('Bottom_Link').innerHTML;
    
    var i;
    for (i = 0; i < numLetters; i++) {
        // Replace Title
        var ScrambledIndex = getRandomInt(0, text_title.length);
        var replacementCharacter = String.fromCharCode(getRandomInt(48, 126));
        document.getElementById('Bottom_Title').innerHTML = replaceCharacter(ScrambledIndex, replacementCharacter, text_title);
        
        ScrambledIndex = getRandomInt(0, text_description.length);
        replacementCharacter = String.fromCharCode(getRandomInt(48, 126));
        document.getElementById('Bottom_Description').innerHTML = replaceCharacter(ScrambledIndex, replacementCharacter, text_description);
        
        ScrambledIndex = getRandomInt(0, text_link.length);
        replacementCharacter = String.fromCharCode(getRandomInt(48, 126));
        document.getElementById('Bottom_Link').innerHTML = replaceCharacter(ScrambledIndex, replacementCharacter, text_link);
        
    }
    
}

function unScrambleLetters(direction) {
    var current;
    
    if (direction == "left")  {
        current = document.getElementById('Right_Image').src;
    }
    else {
        current = document.getElementById('Left_Image').src;
    }
    
    var inedxOfNext = findTheInteger(current) - 1;
    var nextTitle = titles[inedxOfNext];
    var nextDescription = description[inedxOfNext];
    var nextLink = links[inedxOfNext];
    var tmpTitle;
    
    var titleIndex = 0;
    var descriptionIndex = 0;
    var linkIndex = 0;
    
    document.getElementById('Bottom_Title').innerHTML = nextTitle;
    document.getElementById('Bottom_Description').innerHTML = nextDescription;
    document.getElementById('Bottom_Link').href = nextLink;
}


function replaceCharacter(index, replaceChar, origString) {
    let firstPart = origString.substr(0, index);
    let lastPart = origString.substr(index + 1);
    let newString = firstPart + replaceChar + lastPart;
    return newString;
}


function findTheInteger(originalString) {
    var theInteger;
    for (var i = 0; i < originalString.length; i++) {
        if (numberStrings.includes(originalString.charAt(i))) {
            theInteger = originalString.charAt(i);
            break;
        }
    }
    return theInteger;
}


function buttonHover(isOver) {
    var rightArrow = document.getElementById('Right_Arrow');
    var leftArrow = document.getElementById('Left_Arrow');
    console.log(rightArrow.style.opacity);
    var id = setInterval(frame, 10);
    var currentSteps;
    if (isOver) {
        currentSteps = 0;
    }
    else {
        currentSteps = 50;
    }
    function frame() {
        if ((currentSteps <= 0 && !isOver) || (currentSteps >= 50 && isOver)) {
            clearInterval(id);
            console.log("DONE");
        } 
        else {
            if (isOver) {
                currentSteps = currentSteps + 1;
                rightArrow.style.opacity = Number(rightArrow.style.opacity) + .01;
                leftArrow.style.opacity = Number(leftArrow.style.opacity) + .01;
                console.log("GROWING: " + rightArrow.style.opacity);
            }
            else {
                currentSteps = currentSteps - 1;
                rightArrow.style.opacity -= .01;
                leftArrow.style.opacity -= .01;
                console.log("SHINKING: " + rightArrow.style.opacity);
            }
        }
    }
}










