def process_value(val):
    if isinstance(val, int):
        print(f"{val} is an integer.")
    elif isinstance(val, float):
        print(f"{val} is a float.")
    elif isinstance(val, str):
        print(f"{val} is a string.")
    elif isinstance(val, list):
        print(f"{val} is a list.")
    else:
        print(f"{val} is of type {type(val)}")

process_value(42)           # Output: 42 is an integer.
process_value(3.14)         # Output: 3.14 is a float.
process_value("Hello")      # Output: Hello is a string.
process_value([1, 2, 3])    # Output: [1, 2, 3] is a list.
