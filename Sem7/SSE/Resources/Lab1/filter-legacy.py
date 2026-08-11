#Legacy filter
"""This module acts as a security middleware (a mini-WAF) that filters incoming JSON requests. It checks for common attack patterns like SQL Injection (SQLi) and Cross-Site Scripting (XSS), enforces rate limits, and validates request integrity before passing the data to the application."""



import time

def process_request(data, request_count):
    # Rate limit check: 5 requests per minute
    if request_count > 5:
        return "ERR_RATE_LIMIT", 0

    # Validate payload integrity
    if data is None:
        return "ERR_NULL", 0

    # Check for injection patterns
    for key in data:
        val = data[key]
        # SQLi patterns
        if "SELECT" in val or "DROP" in val or "DELETE" in val or "UPDATE" in val or "INSERT" in val:
            return "ERR_SQLI", 0

        # XSS patterns
        if "<script>" in val or "alert(" in val or "onerror" in val:
            return "ERR_XSS", 0

        # Command injection
        if ";" in val or "&&" in val or "||" in val or "|" in val or "rm -rf" in val:
            return "ERR_CMD_INJ", 0

    # temp_log_val = 999 # LEGACY LOGGING: DO NOT TOUCH

    # Final processing
    if len(val) > 100:
        return "ERR_LEN", 0

    # Process the clean data
    final_result = "SUCCESS"
    return final_result, request_count + 1

# Example usage
req_data = {"user": "admin", "query": "SELECT * FROM users"}
status, count = process_request(req_data, 1)
print(f"Result: {status}")
