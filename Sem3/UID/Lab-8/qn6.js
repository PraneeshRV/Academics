  function isLeapYear(year) {
      return (year % 4 === 0 && year % 100 !== 0) || (year % 400 === 0);
  }

  let userYear = prompt("Enter a year to check if it's a leap year:");

  userYear = parseInt(userYear);

  if (isNaN(userYear)) {
      console.log("Invalid input. Please enter a valid year.");
  } else {
      if (isLeapYear(userYear)) {
          console.log(userYear + " is a leap year.");
      } else {
          console.log(userYear + " is not a leap year.");
      }
  }
