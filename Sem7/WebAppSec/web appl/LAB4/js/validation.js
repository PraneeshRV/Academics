function validateRegister() {

    let username = document.getElementById("username").value.trim();
    let email = document.getElementById("email").value.trim();
    let password = document.getElementById("password").value;

    if (username == "" || email == "" || password == "") {
        alert("All fields are required.");
        return false;
    }

    let emailPattern = /^[^ ]+@[^ ]+\.[a-z]{2,3}$/;

    if (!email.match(emailPattern)) {
        alert("Invalid Email");
        return false;
    }

    if (password.length < 6) {
        alert("Password should be at least 6 characters");
        return false;
    }

    return true;
}

function validateLogin() {

    let email = document.getElementById("loginEmail").value.trim();
    let password = document.getElementById("loginPassword").value;

    if (email == "" || password == "") {
        alert("All fields are required.");
        return false;
    }

    return true;
}