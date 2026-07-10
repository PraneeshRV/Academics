"""Regression / characterization suite for Task 2.

Loads the original `filter-legacy.py` (hyphenated -> loaded by path) and the
`filter_refactored` module, and asserts they return IDENTICAL results for every
case, including the two legacy quirks:
  * the length check only inspects the LAST field's value, and
  * an empty `data` dict raises NameError.
"""
import importlib.util
import os

import pytest

import filter_refactored as new

_HERE = os.path.dirname(__file__)
_spec = importlib.util.spec_from_file_location(
    "filter_legacy", os.path.join(_HERE, "filter-legacy.py"))
legacy = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(legacy)  # runs the module's top-level demo (prints once)

MODULES = [legacy, new]

CASES = [
    ("rate_limit",   {"a": "x"},                        6, ("ERR_RATE_LIMIT", 0)),
    ("null_payload", None,                              1, ("ERR_NULL", 0)),
    ("sqli",         {"q": "SELECT * FROM t"},          1, ("ERR_SQLI", 0)),
    ("xss",          {"q": "<script>evil</script>"},    1, ("ERR_XSS", 0)),
    ("cmd_inj",      {"q": "a; ls"},                     1, ("ERR_CMD_INJ", 0)),
    ("clean_short",  {"q": "hello world"},              1, ("SUCCESS", 2)),
    ("clean_len",    {"q": "a" * 101},                  1, ("ERR_LEN", 0)),
    # ordering: rate limit is evaluated before payload content
    ("rate_beats_sqli", {"q": "SELECT"},                6, ("ERR_RATE_LIMIT", 0)),
]


@pytest.mark.parametrize("mod", MODULES)
@pytest.mark.parametrize("name,data,count,expected", CASES)
def test_behavior_matches(mod, name, data, count, expected):
    assert mod.process_request(data, count) == expected


@pytest.mark.parametrize("mod", MODULES)
def test_empty_dict_raises_nameerror(mod):
    # Legacy quirk: `val` is only defined inside the loop, so an empty dict crashes.
    with pytest.raises(NameError):
        mod.process_request({}, 1)
