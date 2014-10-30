function onXHRLoad(event) {
    var repHeader = event.target.getResponseHeader("Test-Header");
    alert("Response Test-Header: " + repHeader );

    var json = JSON.parse(event.target.response);

    var lbl = document.getElementById("lbl")
    lbl.removeAttribute("hidden");
    lbl.innerHTML = "Primes found: "
    for (p in json.primes)
    {
      lbl.innerHTML += json.primes[p] + " ";
    }

    // lbl.innerHTML = "Primes: " + json.primes;
}

function onXHRError(event) {
    alert("error");
}

function sendRequest(){
    var xhr = new XMLHttpRequest();

	xhr.open("POST", "test.php");
	xhr.responseType = "json";

    var limit = document.getElementById("limit").value;
    xhr.setRequestHeader("Test-Header", limit);

    alert("Request Test-Header: " + limit);

    xhr.onload = onXHRLoad;
    xhr.onerror = onXHRError;

    xhr.send();
}


