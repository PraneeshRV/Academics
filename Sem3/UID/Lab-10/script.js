function validateForm() {
  let isValid = true;


  const userId = document.forms["registrationForm"]["userId"].value;
  if (userId.length < 5 || userId.length > 12) {
      displayError("userId", "User id must be of length 5 to 12.");
      isValid = false;
  } else {
      clearError("userId");
  }

  const password = document.forms["registrationForm"]["password"].value;
  if (password.length < 7 || password.length > 12) {
      displayError("password", "Password must be of length 7 to 12.");
      isValid = false;
  } else {
      clearError("password");
  }


  const name = document.forms["registrationForm"]["name"].value;
  if (name.trim() === "" || !/^[a-zA-Z]+$/.test(name)) {
      displayError("name", "Name is required and must contain alphabets only.");
      isValid = false;
  } else {
      clearError("name");
  }

 
  const country = document.forms["registrationForm"]["country"].value;
  if (country === "") {
      displayError("country", "Please select a country.");
      isValid = false;
  } else {
      clearError("country");
  }


  const zipCode = document.forms["registrationForm"]["zipCode"].value;
  if (zipCode.trim() === "" || !/^\d+$/.test(zipCode)) {
      displayError("zipCode", "ZIP Code is required and must be numeric only.");
      isValid = false;
  } else {
      clearError("zipCode");
  }

  const email = document.forms["registrationForm"]["email"].value;
  if (email.trim() === "" || !isValidEmail(email)) {
      displayError("email", "Please enter a valid email address.");
      isValid = false;
  } else {
      clearError("email");
  }

  const sex = document.querySelector('input[name="gender"]:checked');
  if (!sex) {
      displayError("gender", "Please select a gender.");
      isValid = false;
  } else {
      clearError("gender");
  }

  const language = document.querySelector('input[name="language"]:checked');
  if (!language) {
      displayError("language", "Please select a language.");
      isValid = false;
  } else {
      clearError("language");
  }

  return isValid;
}

function isValidEmail(email) {
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  return emailRegex.test(email);
}

function displayError(fieldId, errorMessage) {
  const errorElement = document.getElementById(fieldId + "Error");
  errorElement.textContent = errorMessage;
}

function clearError(fieldId) {
  const errorElement = document.getElementById(fieldId + "Error");
  errorElement.textContent = "";
}