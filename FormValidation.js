document.getElementById('login').addEventListener('click', fValidate);
document.getElementById('reset').addEventListener('click', fReset);


function fValidate(){
	let user = document.getElementById('username');
	let valid = true; //creating valid as a variable so if this is false, we do not reload the page
	if (user.value.length < 8 || user.value.length > 20) { //must validate whether we reach our character limit or not
        usernameError.innerHTML = "Username must be between 8 and 20 characters";
        user.style.backgroundColor = "red";
        valid = false
    }else{
    	usernameError.innerHTML = "Validation messages";
        user.style.backgroundColor = "";
    }

    let pass = document.getElementById('password');
    if (pass.value.length < 8 || pass.value.length > 20) { //must validate whether we reach our character limit or not
        passwordError.innerHTML = "Password must be between 8 and 20 characters";
        pass.style.backgroundColor = "red";
        valid = false;
    }else{
    	passwordError.innerHTML = "Validation messages";
        pass.style.backgroundColor = "";
    }

    if(valid == false){ //will stop page and will prompt an alert
    	event.preventDefault();
        alert('Form validation failed');
    }
}

function fReset() { //this will reset all changed entries to their original state
    let user = document.getElementById('username');
    let pass = document.getElementById('password');

    user.value = '';
    usernameError.innerHTML = "Validation messages";
    user.style.backgroundColor = "";

    pass.value = '';
    passwordError.innerHTML = "Validation messages";
    pass.style.backgroundColor = "";
}

