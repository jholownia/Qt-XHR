var onReply = function() {
	Document.findElementById("lbl").setAttribute("hidden", "false");
}

var sendRequest = function() {
	var xhr = new XMLHttpRequest;
		
	xhr.open("POST", "test.php");
	xhr.responseType = "json";
    xhr.setRequestHeader("Test-Header", "42");
	
	xhr.addEventListener("load", onReply);	
}


