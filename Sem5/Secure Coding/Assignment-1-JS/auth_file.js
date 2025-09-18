const fs = require("fs");
const readline = require("readline-sync");
const filePath = __dirname + '/password.txt';


let data = fs.readFileSync(filePath).toString().trim().split("\n");
let users = {};

for (let i=0; i<data.length; i++){
    let parts = data[i].split(" ");
    users[parts[0]]= parts[i];
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