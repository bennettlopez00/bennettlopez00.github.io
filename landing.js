function onLoad() {
    windowResize();
    main();
}


function windowResize() {
    var size = "px 5px 325px 2px 325px 5px ";

    
    
    var sizeOfEdWindow = 662;
    var width = window.innerWidth;
    if (width < 1016) {
        size = "px 5px 230px 2px 230px 5px ";
        sizeOfEdWindow = 462;
    }
    var currentSize = ((width - sizeOfEdWindow) + 1) / 2;
    if (currentSize < 0) {
        currentSize = 0;
    }
    // console.log("Height: " + height);
    document.getElementById('bottomSection').style.gridTemplateColumns = currentSize + size + currentSize + "px";
    document.getElementById('Header').style.gridTemplateColumns = "100px " + ((width / 2) - 100) + "px " + ((width / 2) - 100) + "px";
}





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




window.onresize = windowResize;