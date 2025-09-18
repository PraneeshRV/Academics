const now = new Date();

const daysOfWeek = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];

const currentDay = daysOfWeek[now.getDay()];

const hours = now.getHours().toString().padStart(2, '0');
const minutes = now.getMinutes().toString().padStart(2, '0');
const seconds = now.getSeconds().toString().padStart(2, '0');
const currentTime = `${hours}:${minutes}:${seconds}`;

console.log(`Today is: ${currentDay}`);
console.log(`Current time is: ${currentTime}`);