function validateForm() {
    var form = document.forms["signup"];
    var isValid = true;
  
    // Reset error messages
    document.querySelectorAll('.error').forEach(el => el.textContent = '');
  
    // Validate First name
    var firstname = form["firstname"].value;
    if (firstname.length < 3 || firstname.length > 10) {
      document.getElementById('firstnameError').textContent = "First name must be between 3 and 10 characters.";
      isValid = false;
    }
  
    // Validate Last name
    var lastname = form["lastname"].value;
    if (lastname.length < 3 || lastname.length > 10) {
      document.getElementById('lastnameError').textContent = "Last name must be between 3 and 10 characters.";
      isValid = false;
    }
  
    // Validate Phone
    var phone = form["phone"].value;
    if (!/^[0-9]{10}$/.test(phone)) {
      document.getElementById('phoneError').textContent = "Phone number must be exactly 10 digits.";
      isValid = false;
    }
  
    // Validate Gender
    var gender = form["gender"].value;
    if (!gender) {
      document.getElementById('genderError').textContent = "Please select a gender.";
      isValid = false;
    }
  
    // Validate Age
    var age = form["age"].value;
    if (age < 18 || age > 21) {
      document.getElementById('ageError').textContent = "Age must be between 18 and 21.";
      isValid = false;
    }
  
    // Validate Address
    var address = form["address"].value;
    if (address.length > 30) {
      document.getElementById('addressError').textContent = "Address must not exceed 30 characters.";
      isValid = false;
    }
  
    // Validate City
    var city = form["city"].value;
    if (!city) {
      document.getElementById('cityError').textContent = "Please select a city.";
      isValid = false;
    }
  
    // Validate Email
    var email = form["email"].value;
    if (!validateEmail(email)) {
      document.getElementById('emailError').textContent = "Please enter a valid email address.";
      isValid = false;
    }
  
    // Validate Username
    var username = form["username"].value;
    if (!/^[A-Za-z0-9]{5,8}$/.test(username)) {
      document.getElementById('usernameError').textContent = "Username must be 5-8 alphanumeric characters.";
      isValid = false;
    }
  
    // Validate Password
    var password = form["password"].value;
    if (!validatePassword(password)) {
      document.getElementById('passwordError').textContent = "Password must be 6-11 characters long, contain at least one uppercase letter, one number, and one special character (!@#$%^&*).";
      isValid = false;
    }
  
    if (isValid) {
      alert('Form submitted successfully!');
    }
  }
  
  function validateEmail(email) {
    var re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return re.test(String(email).toLowerCase());
  }
  
  function validatePassword(password) {
    var re = /^(?=.*\d)(?=.*[A-Z])(?=.*[!@#$%^&*]).{6,11}$/;
    return re.test(password);
  }
  