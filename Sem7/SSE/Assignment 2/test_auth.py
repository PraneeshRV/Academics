"""Regression / characterization suite for Task 1.

Golden Rule of Agile Refactoring: external behavior must not change.
Every case runs against BOTH auth_legacy and auth_refactored and asserts
identical output. If refactoring changed behavior, these turn RED.
"""
import copy
import hashlib
import pytest

import auth_legacy
import auth_refactored

MODULES = [auth_legacy, auth_refactored]


def _legacy_hash(value):
    # Independent reference for the salt+md5 contract (locks salt & algorithm).
    return hashlib.md5((value + "s3cr3t_legacy_salt_2011").encode()).hexdigest()


def base_db():
    # A pre-existing user with a known STRONG password "Password1".
    return {
        "existing": {
            "email": "e@x.com", "role": "user",
            "password_hash": _legacy_hash("Password1"),
            "sec_q": "q", "sec_a_hash": _legacy_hash("blue"),
            "failed_attempts": 0,
        }
    }


REGISTER_CASES = [
    # username length guards (checked before everything else)
    ("bob", "Password1", "Password1", "REJECTED", "Username invalid length"),
    ("x" * 21, "Password1", "Password1", "REJECTED", "Username invalid length"),
    # existing user
    ("existing", "Password1", "Password1", "REJECTED", "User exists"),
    # weak password: too short
    ("alice", "Pw1", "Pw1", "REJECTED", "Password too weak"),
    # weak password: long but no uppercase -> stays WEAK
    ("alice", "password1", "password1", "REJECTED", "Password too weak"),
    # MEDIUM password (upper, no digit) still passes the WEAK gate -> mismatch reached
    ("alice", "Password", "NOPE", "REJECTED", "Passwords mismatch"),
    # STRONG password, mismatch
    ("alice", "Password1", "NOPE", "REJECTED", "Passwords mismatch"),
    # MEDIUM password, matching -> APPROVED
    ("alice", "Password", "Password", "APPROVED", "Registered"),
    # STRONG password, matching -> APPROVED
    ("alice", "Password1", "Password1", "APPROVED", "Registered"),
    # ordering: bad username + weak password -> username wins
    ("bob", "weak", "weak", "REJECTED", "Username invalid length"),
]


@pytest.mark.parametrize("mod", MODULES)
@pytest.mark.parametrize("uname,pw,cpw,status,reason", REGISTER_CASES)
def test_register_behavior(mod, uname, pw, cpw, status, reason):
    db = base_db()
    res = mod.register_user(uname, pw, cpw, "n@x.com", "user", "pet?", "Rex", db)
    assert res == {"status": status, "reason": reason}


@pytest.mark.parametrize("mod", MODULES)
def test_register_stores_correct_record(mod):
    db = base_db()
    res = mod.register_user("alice", "Password1", "Password1",
                            "a@x.com", "admin", "pet?", "REX", db)
    assert res["status"] == "APPROVED"
    rec = db["alice"]
    assert rec["email"] == "a@x.com"
    assert rec["role"] == "admin"
    assert rec["sec_q"] == "pet?"
    assert rec["failed_attempts"] == 0
    assert rec["password_hash"] == _legacy_hash("Password1")
    # security answer is lowercased before hashing
    assert rec["sec_a_hash"] == _legacy_hash("rex")


@pytest.mark.parametrize("mod", MODULES)
def test_login_username_guard(mod):
    db = base_db()
    assert mod.login_user("bob", "x", db)["reason"] == "Username invalid length"
    assert mod.login_user("x" * 21, "x", db)["reason"] == "Username invalid length"


@pytest.mark.parametrize("mod", MODULES)
def test_login_unknown_user(mod):
    db = base_db()
    assert mod.login_user("ghost", "Password1", db) == {
        "status": "REJECTED", "reason": "Invalid user"}


@pytest.mark.parametrize("mod", MODULES)
def test_login_lockout(mod):
    db = base_db()
    db["existing"]["failed_attempts"] = 3
    assert mod.login_user("existing", "Password1", db) == {
        "status": "LOCKED", "reason": "Locked out"}


@pytest.mark.parametrize("mod", MODULES)
def test_login_wrong_password_increments(mod):
    db = base_db()
    res = mod.login_user("existing", "WrongPass1", db)
    assert res == {"status": "REJECTED", "reason": "Invalid password"}
    assert db["existing"]["failed_attempts"] == 1


@pytest.mark.parametrize("mod", MODULES)
def test_login_success_resets_attempts(mod):
    db = base_db()
    db["existing"]["failed_attempts"] = 2
    res = mod.login_user("existing", "Password1", db)
    assert res == {"status": "APPROVED", "reason": "Welcome back"}
    assert db["existing"]["failed_attempts"] == 0
