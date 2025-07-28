const fs = require("fs");
const crypto = require("crypto");
const readline = require("readline-sync");

const filePath = __dirname + "/hashed_password.txt";

function hashPwd(password) {
  return crypto.createHash("sha256").update(password).digest("hex");
}

let data = fs.readFileSync(filePath).toString().trim().split("\n");
let users = {};

for (let i = 0; i < data.length; i++) {
  let parts = data[i].split(" ");
  let username = parts[0];
  let hash = parts[1];
  users[username] = hash;
}

let maxAttempts = 3;
let attempts = 0;
let auth = false;

while(attempts<maxAttempts && !auth){
    let inputUser = readline.question("Enter Username: ");
    let inputPass = readline.question("Enter Password: ");

    let inputHash = hashPwd(inputPass);


  if (users[inputUser] === inputHash) {
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