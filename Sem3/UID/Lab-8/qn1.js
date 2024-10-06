  const number = parseInt(prompt("Enter a positive integer to calculate its factorial:"));

  function factorial(n) {
      if (n === 0 || n === 1) {
          return 1;
      } else {
          return n * factorial(n - 1);
      }
  }

  if (number < 0) {
      console.log("Factorial is not defined for negative numbers.");
  } else {
      const result = factorial(number);
      console.log(`The factorial of ${number} is ${result}`);
  }