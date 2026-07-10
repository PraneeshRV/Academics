# Task 2 — Refactoring Analysis of `filter-legacy.py`

**Course:** Secure Software Engineering – 20CYS401 · Lab Exercise 1
**Module under review:** `filter-legacy.py` (a mini-WAF security middleware)

**Golden Rule applied:** every refactoring below preserves external behaviour. This is
proved by `test_filter.py`, which runs the original module and `filter_refactored.py`
through the same inputs and asserts identical output (**passes** — see `pytest` run).
The code base is intentionally left vulnerable; fixing the security bugs is **out of
scope**, so smells are removed *without* changing what the code does.

---

## Summary of smells found

| # | Code Smell | Location | Refactoring Technique |
|---|------------|----------|-----------------------|
| 1 | Magic Numbers | `request_count > 5`, `len(val) > 100` | Replace Magic Number with Symbolic Constant |
| 2 | Duplicated / scattered string literals | the three injection `if` blocks | Introduce data table + `any()` |
| 3 | Long Method | whole `process_request` | Extract Method (`scan_value`) |
| 4 | Repeated conditional structure | SQLi / XSS / CMD blocks | Consolidate Conditional / rule table |
| 5 | Dead (commented-out) code | `# temp_log_val = 999 ...` | Remove Dead Code |
| 6 | Unused import | `import time` | Remove Dead Code |
| 7 | Scope leak — loop variable used after loop | `if len(val) > 100` | Explain via comment (behaviour-preserving) |
| 8 | Script side-effects at import time | trailing `# Example usage` block | Extract to `__main__` guard |

---

## Smell 1 — Magic Numbers

**Snippet**
```python
if request_count > 5:          # 5 = ?
    return "ERR_RATE_LIMIT", 0
...
if len(val) > 100:             # 100 = ?
    return "ERR_LEN", 0
```
**Why it's a smell:** the literals `5` and `100` carry business meaning (rate limit,
max field length) but no name. A reader must guess intent, and if the limit changes it
must be hunted down by value — error-prone.

**Technique:** *Replace Magic Number with Symbolic Constant.*
**Why it applies:** the values are policy constants used as thresholds — the classic
target for this refactoring.
**How:**
```python
RATE_LIMIT = 5
MAX_VALUE_LENGTH = 100
...
if request_count > RATE_LIMIT: ...
if len(val) > MAX_VALUE_LENGTH: ...
```

---

## Smell 2 & 4 — Scattered literals + duplicated conditional structure

**Snippet**
```python
if "SELECT" in val or "DROP" in val or "DELETE" in val or "UPDATE" in val or "INSERT" in val:
    return "ERR_SQLI", 0
if "<script>" in val or "alert(" in val or "onerror" in val:
    return "ERR_XSS", 0
if ";" in val or "&&" in val or "||" in val or "|" in val or "rm -rf" in val:
    return "ERR_CMD_INJ", 0
```
**Why it's a smell:** three blocks share the identical shape — *"if any of these
patterns is a substring of `val`, return this error code."* The pattern strings are
buried inside boolean expressions, and `... in val` is repeated 13 times. Adding a new
attack signature means editing a long `or`-chain; it's hard to read and easy to break.

**Technique:** *Introduce a data table + `any()` / Consolidate Conditional Expression.*
**Why it applies:** the logic is uniform across categories, so the *data* (patterns and
error codes) can be separated from the *control flow* (scan for a match).
**How:**
```python
SQLI_PATTERNS    = ["SELECT", "DROP", "DELETE", "UPDATE", "INSERT"]
XSS_PATTERNS     = ["<script>", "alert(", "onerror"]
CMD_INJ_PATTERNS = [";", "&&", "||", "|", "rm -rf"]

# same evaluation order as the original: SQLi -> XSS -> command injection
INJECTION_RULES = [
    (SQLI_PATTERNS, "ERR_SQLI"),
    (XSS_PATTERNS, "ERR_XSS"),
    (CMD_INJ_PATTERNS, "ERR_CMD_INJ"),
]

for patterns, error_code in INJECTION_RULES:
    if any(pattern in val for pattern in patterns):
        return error_code, 0
```
> Order is kept identical so a value matching two categories still returns the same
> code the legacy code would (SQLi wins over XSS wins over CMD). Behaviour preserved.

---

## Smell 3 — Long Method

**Snippet:** `process_request` does rate limiting, null check, three injection scans,
a length check, and result construction — several responsibilities in one function.

**Why it's a smell:** low cohesion; the per-field scanning is the most complex part and
is inlined inside the request loop, making the top-level flow hard to follow and hard to
unit-test in isolation.

**Technique:** *Extract Method.*
**Why it applies:** the injection scan is a self-contained sub-task with a clear input
(a field value) and output (an error code or `None`).
**How:**
```python
def scan_value(val):
    """Return the matching error code for a field value, or None if clean."""
    for patterns, error_code in INJECTION_RULES:
        if any(pattern in val for pattern in patterns):
            return error_code
    return None

# process_request loop becomes:
for key in data:
    error = scan_value(data[key])
    if error:
        return error, 0
```

---

## Smell 5 — Dead / commented-out code

**Snippet**
```python
# temp_log_val = 999 # LEGACY LOGGING: DO NOT TOUCH
```
**Why it's a smell:** commented-out code is noise. It never runs, the "DO NOT TOUCH"
note is intimidating but meaningless, and version control already preserves history.

**Technique:** *Remove Dead Code.*
**Why it applies:** the line has no effect on behaviour, so deleting it is safe and
purely reduces clutter.
**How:** delete the line. (Regression tests stay green.)

---

## Smell 6 — Unused import

**Snippet**
```python
import time   # never used anywhere in the module
```
**Why it's a smell:** misleads the reader into thinking timing/rate logic uses the
clock, when the "rate limit" is really just a passed-in counter.

**Technique:** *Remove Dead Code (unused import).*
**How:** delete the `import time` line.

---

## Smell 7 — Scope leak: loop variable used after the loop

**Snippet**
```python
for key in data:
    val = data[key]
    ...
# (loop ends)
if len(val) > 100:      # <-- val is the LAST field's value
    return "ERR_LEN", 0
```
**Why it's a smell:** `val` is defined inside the `for` loop but read after it. This
means the length check only ever validates the **last** field, and if `data` is an empty
dict `val` is undefined and the function raises `NameError`. This is a latent bug hiding
behind a legitimate-looking check.

**Technique / handling:** This is the interesting case for the Golden Rule.
- The *behaviour-preserving* move (what `filter_refactored.py` does) is to keep the
  check as-is and add a comment making the "last value only" intent explicit, so a
  future reader isn't fooled. No behaviour change.
- The *correct* fix would move `if len(val) > MAX_VALUE_LENGTH` **inside** the loop so
  every field is length-checked, and guard the empty-dict case. **But that changes
  external behaviour** (previously-passing oversized non-last fields would now be
  rejected), so per the lab it is flagged, not applied. It should be raised as a bug
  ticket separate from this refactoring.

**How (behaviour-preserving):**
```python
# NOTE: `val` here is the LAST field's value; empty `data` raises NameError.
# Preserved intentionally -- changing it is a behaviour change (out of scope).
if len(val) > MAX_VALUE_LENGTH:
    return "ERR_LEN", 0
```

---

## Smell 8 — Script side-effects run at import time

**Snippet**
```python
# Example usage
req_data = {"user": "admin", "query": "SELECT * FROM users"}
status, count = process_request(req_data, 1)
print(f"Result: {status}")
```
**Why it's a smell:** this top-level code runs the moment the module is imported —
printing to stdout and executing a request. That makes the module unusable as a reusable
library and pollutes any importer's output (and breaks clean unit testing).

**Technique:** *Guard Clause / Extract to `__main__` block.*
**Why it applies:** the block is a demo, not module behaviour; it belongs behind the
standard entry-point guard.
**How:**
```python
if __name__ == "__main__":
    req_data = {"user": "admin", "query": "SELECT * FROM users"}
    status, count = process_request(req_data, 1)
    print(f"Result: {status}")
```

---

## Verification

```
$ python3 -m pytest -q
50 passed
```
`test_filter.py` runs both the original `filter-legacy.py` and `filter_refactored.py`
through the same inputs (rate limit, null, SQLi, XSS, command injection, clean-short,
oversized-last-value, ordering, empty-dict) and asserts identical results — confirming
the refactoring changed structure only, not behaviour. Tests stayed **green**, so per
the Golden Rule, nothing was broken.
