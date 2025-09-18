const readline = require("readline-sync");

let users = {
    "luffy":"gear5",
    "zoro":"enma",
    "praneesh":"Conqueror101",
    "sayanthan":"IronHeart",
    "sahil":"b2Bomber"
}
let maxAttempts = 3;
let attempts = 0;
let auth = false;

while(attempts<maxAttempts && !auth){
    let inputUser = readline.question("Enter Username: ");
    let inputPass = readline.question("Enter Password: ");

    if (users[inputUser] == inputPass){
        console.log("Authentication successful");
        auth = true;
    } 
    else {
        attempts ++;
        if (attempts < maxAttempts){
            console.error("Authentication failed. Please try again.");
            
        }
    }

}

if (!auth && attempts >= maxAttempts){
    console.error("Limit Exceeded");
}