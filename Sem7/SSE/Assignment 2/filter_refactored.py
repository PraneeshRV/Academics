"""Security middleware (mini-WAF): filters incoming JSON requests for SQLi / XSS /
command-injection patterns, enforces a rate limit, and validates payload integrity.

Refactored for maintainability. Golden Rule honoured: external behaviour is
UNCHANGED (proved in test_filter.py) -- including the legacy quirk that the
payload-length check only ever inspects the LAST field's value, and that an empty
`data` dict raises NameError exactly like the original. Fixing those is a behaviour
change and therefore out of this lab's scope.
"""

# Refactoring 1: Replace Magic Numbers with Symbolic Constants
RATE_LIMIT = 5
MAX_VALUE_LENGTH = 100

# Refactoring 2: Replace repeated string literals with named, data-driven tables
SQLI_PATTERNS = ["SELECT", "DROP", "DELETE", "UPDATE", "INSERT"]
XSS_PATTERNS = ["<script>", "alert(", "onerror"]
CMD_INJ_PATTERNS = [";", "&&", "||", "|", "rm -rf"]

# Checked in the SAME order as the legacy code (SQLi -> XSS -> command injection).
INJECTION_RULES = [
    (SQLI_PATTERNS, "ERR_SQLI"),
    (XSS_PATTERNS, "ERR_XSS"),
    (CMD_INJ_PATTERNS, "ERR_CMD_INJ"),
]


# Refactoring 3: Extract Method -- pull the injection scan out of process_request
def scan_value(val):
    """Return the matching error code for a single field value, or None if clean."""
    for patterns, error_code in INJECTION_RULES:
        if any(pattern in val for pattern in patterns):
            return error_code
    return None


def process_request(data, request_count):
    if request_count > RATE_LIMIT:
        return "ERR_RATE_LIMIT", 0

    if data is None:
        return "ERR_NULL", 0

    for key in data:
        val = data[key]
        error = scan_value(val)
        if error:
            return error, 0

    # NOTE (behaviour preserved): `val` is the LAST field's value here, and an
    # empty `data` dict raises NameError -- identical to the legacy module.
    if len(val) > MAX_VALUE_LENGTH:
        return "ERR_LEN", 0

    return "SUCCESS", request_count + 1


# Refactoring 4: Move script side-effects behind a main guard so the module is importable
if __name__ == "__main__":
    req_data = {"user": "admin", "query": "SELECT * FROM users"}
    status, count = process_request(req_data, 1)
    print(f"Result: {status}")
