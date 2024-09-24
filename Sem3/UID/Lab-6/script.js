/*let a = prompt("Enter your department");
if (a === "cys"){
    alert("its my department");
}
    else{
        alert("its not my department");
    }*/
    document.querySelector("html").addEventListener("click", function() {
        document.getElementById("h11").innerHTML = "BooHoo";
        document.getElementById("h11").style.color = "red";
    });
    document.querySelector("html").addEventListener("pointermove", function() {
        document.getElementById("h11").innerHTML = "WooHoo";
        document.getElementById("h11").style.color = "blue";
    });
    let a = prompt("Enter your department");
    if (a === "cys"){
        alert("its my department");
    }
        else{
            alert("get out");
        }