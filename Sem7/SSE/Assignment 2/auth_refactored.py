import hashlib

# --- Refactoring 1: Replace Magic Numbers / Strings with Symbolic Constants ---
MIN_USERNAME_LENGTH = 4
MAX_USERNAME_LENGTH = 20
MIN_PASSWORD_LENGTH = 8
MAX_FAILED_ATTEMPTS = 3
# NOTE: weak MD5 + hardcoded salt are intentional legacy vulns; fixing is out of lab scope.
LEGACY_SALT = "s3cr3t_legacy_salt_2011"


# --- Refactoring 4: Extract Method (kills the duplicated username-length check) ---
def is_valid_username(username):
    return MIN_USERNAME_LENGTH <= len(username) <= MAX_USERNAME_LENGTH


# --- Refactoring 5: Extract Method (kills the duplicated hashlib.md5 logic) ---
def generate_hash(value):
    return hashlib.md5((value + LEGACY_SALT).encode()).hexdigest()


# --- Refactoring 3 (+ Refactoring 2: explaining variables): Guard Clauses over nesting ---
def check_password_strength(password):
    if len(password) < MIN_PASSWORD_LENGTH:
        return "WEAK"

    has_upper = any(c.isupper() for c in password)
    if not has_upper:
        return "WEAK"

    has_digit = any(c.isdigit() for c in password)
    if not has_digit:
        return "MEDIUM"

    return "STRONG"


def register_user(username, password, confirm_password, email, role, sec_q, sec_a, users_db):
    if not is_valid_username(username):
        return {"status": "REJECTED", "reason": "Username invalid length"}
    if username in users_db:
        return {"status": "REJECTED", "reason": "User exists"}

    if check_password_strength(password) == "WEAK":
        return {"status": "REJECTED", "reason": "Password too weak"}

    if password != confirm_password:
        return {"status": "REJECTED", "reason": "Passwords mismatch"}

    users_db[username] = {
        "email": email,
        "role": role,
        "password_hash": generate_hash(password),
        "sec_q": sec_q,
        "sec_a_hash": generate_hash(sec_a.lower()),
        "failed_attempts": 0,
    }
    return {"status": "APPROVED", "reason": "Registered"}


def login_user(username, password, users_db):
    if not is_valid_username(username):
        return {"status": "REJECTED", "reason": "Username invalid length"}

    if username not in users_db:
        return {"status": "REJECTED", "reason": "Invalid user"}

    user = users_db[username]
    if user["failed_attempts"] >= MAX_FAILED_ATTEMPTS:
        return {"status": "LOCKED", "reason": "Locked out"}

    if generate_hash(password) != user["password_hash"]:
        user["failed_attempts"] += 1
        return {"status": "REJECTED", "reason": "Invalid password"}

    user["failed_attempts"] = 0
    return {"status": "APPROVED", "reason": "Welcome back"}
