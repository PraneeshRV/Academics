function isPalindrome(str) {
  let reversed = str.split('').reverse().join('');
  return str === reversed;
}

let userInput = prompt("Enter a word to check if it's a palindrome:");
console.log(isPalindrome(userInput));
