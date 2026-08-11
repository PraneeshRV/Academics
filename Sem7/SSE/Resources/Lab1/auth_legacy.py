import hashlib

def register_user(username, password, confirm_password, email, role, sec_q, sec_a, users_db):
    
    # Check username length (Duplicate Code)
    if len(username) < 4:
        return {"status": "REJECTED", "reason": "Username invalid length"}
    if len(username) > 20:
        return {"status": "REJECTED", "reason": "Username invalid length"}
    if username in users_db:
        return {"status": "REJECTED", "reason": "User exists"}

    # Check password strength (Nested Conditionals & Complex Logic)
    strength = "WEAK"
    if len(password) >= 8:
        if any(c.isupper() for c in password):
            if any(c.isdigit() for c in password):
                strength = "STRONG"
            else:
                strength = "MEDIUM"

    if strength == "WEAK":
        return {"status": "REJECTED", "reason": "Password too weak"}

    if password != confirm_password:
        return {"status": "REJECTED", "reason": "Passwords mismatch"}

    # Create hashes and save user (Magic Strings & Duplication)
    salt = "s3cr3t_legacy_salt_2011"
    pw_hash = hashlib.md5((password + salt).encode()).hexdigest()
    ans_hash = hashlib.md5((sec_a.lower() + salt).encode()).hexdigest()

    users_db[username] = {
        "email": email,
        "role": role,
        "password_hash": pw_hash,
        "sec_q": sec_q,
        "sec_a_hash": ans_hash,
        "failed_attempts": 0
    }
    return {"status": "APPROVED", "reason": "Registered"}


def login_user(username, password, users_db):
    # Check username length (Duplicate Code)
    if len(username) < 4:
        return {"status": "REJECTED", "reason": "Username invalid length"}
    if len(username) > 20:
        return {"status": "REJECTED", "reason": "Username invalid length"}

    if username not in users_db:
        return {"status": "REJECTED", "reason": "Invalid user"}

    user = users_db[username]
    if user["failed_attempts"] >= 3:
        return {"status": "LOCKED", "reason": "Locked out"}

    # Verify password hash (Magic Strings & Duplication)
    salt = "s3cr3t_legacy_salt_2011"
    pw_hash = hashlib.md5((password + salt).encode()).hexdigest()

    if pw_hash != user["password_hash"]:
        user["failed_attempts"] += 1
        return {"status": "REJECTED", "reason": "Invalid password"}

    user["failed_attempts"] = 0
    return {"status": "APPROVED", "reason": "Welcome back"}
