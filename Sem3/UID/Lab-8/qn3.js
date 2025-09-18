  function convertToDigitArray(number) {
      return Array.from(String(number), Number);
  }

  let userInput = prompt("Enter a number to convert to an array of digits:");

  let number = Number(userInput);

  if (isNaN(number)) {
      console.log("Invalid input. Please enter a valid number.");
  } else {
      let digitArray = convertToDigitArray(number);
    
      console.log("Number:", number);
      console.log("Array of digits:", digitArray);
  }
