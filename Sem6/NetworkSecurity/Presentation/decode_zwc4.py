#!/usr/bin/env python3
"""Decode using 330k Unicode Steganography tool's encoding scheme.
Uses base-10 with groups of 5 zero-width characters, each char maps to a digit 0-9.
"""

text = "\u200B\u200B\u200B\u202D\u202D\u200B\u200B\u200B\u200D\u200E\u202C\u200B\u200B\u200B\u200C\u200D\u202C\u200B\u200B\u200B\u200C\u202C\u202C\u200B\u200B\u200B\u200C\u2063\u200B\u202D\u202D\u200B\u200B\u200B\u200C\u2062\uFEFF\u200B\u200B\u200B\u200C\u200D\u2062\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u202C\u200B\u200B\u200B\u200B\u200D\u202C\u2062BITSCTF\u200B\u200B\u200B\u200C\u200D\u202C\u200B\u200B\u200B\u200C\u202C\u202C\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u2062\uFEFF\u200B\u200B\u200B\u200C\u200D\u2062{\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u202C\u200B\u200B\u200B\u200B\u200D\u202C\u2062\u200B\u200B\u200B\u200D\u200C\u2062\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200C\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200C\u200B\u2062\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200B\uFEFF\uFEFFyour_\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200D\uFEFF\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200C\u200B\uFEFF\u200B\u200B\u200B\u200D\u200B\uFEFF\u200B\u200B\u200B\u200C\u200B\u200B\u200B\u200B\u200B\u200D\u200C\u2063\u200B\u200B\u200B\u200D\u200B\u2063\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u200B\u200Cflag\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200B\u2062\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200D\u200C\u202C\u200B\u200B\u200B\u200D\u200C\u202C\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200D\u202C\uFEFF_goes_here}"

invisible_set = {'\u200B', '\u200C', '\u200D', '\u200E', '\u202A', '\u202C', '\u202D', '\u2062', '\u2063', '\uFEFF'}
invisible_only = [c for c in text if c in invisible_set]

print(f"Total invisible chars: {len(invisible_only)}")
print(f"Unique chars: {sorted(set(f'U+{ord(c):04X}' for c in invisible_only))}")

# 330k tool mapping (all 10 chars selected):
# 0: U+200B, 1: U+200C, 2: U+200D, 3: U+200E, 4: U+202A, 5: U+202C, 6: U+202D, 7: U+2062, 8: U+2063, 9: U+FEFF
char_to_digit_330k = {
    '\u200B': 0, '\u200C': 1, '\u200D': 2, '\u200E': 3,
    '\u202A': 4, '\u202C': 5, '\u202D': 6,
    '\u2062': 7, '\u2063': 8, '\uFEFF': 9
}

# But we don't have U+202A in our data. Let me check again
print(f"\nChars present: {sorted(set(f'U+{ord(c):04X}' for c in invisible_only))}")
has_202A = any(c == '\u202A' for c in invisible_only)
print(f"Has U+202A: {has_202A}")

# If U+202A is NOT present, maybe the mapping skips it or uses a different tool variant
# Let's try two approaches:

# MAPPING 1: Standard 330k with 10 chars (even if 202A is missing, position 4 would just not appear)
print("\n=== MAPPING 1: 330k standard (base 10, groups of 5) ===")
digits = [char_to_digit_330k.get(c, -1) for c in invisible_only]
invalid = sum(1 for d in digits if d == -1)
print(f"  Invalid chars: {invalid}")

result1 = ''
for i in range(0, len(digits) - 4, 5):
    group = digits[i:i+5]
    if -1 in group:
        result1 += '?'
        continue
    val = group[0]*10000 + group[1]*1000 + group[2]*100 + group[3]*10 + group[4]
    try:
        result1 += chr(val)
    except:
        result1 += f'[{val}]'
print(f"  Result: {result1}")
print(f"  Repr: {repr(result1)}")

# MAPPING 2: Maybe the tool uses only the 9 chars we have as base-9
# 0: U+200B, 1: U+200C, 2: U+200D, 3: U+200E, 4: U+202C, 5: U+202D, 6: U+2062, 7: U+2063, 8: U+FEFF
print("\n=== MAPPING 2: 9 chars as base-9, groups of 5 (9^5=59049) ===")
char_to_digit_9 = {
    '\u200B': 0, '\u200C': 1, '\u200D': 2, '\u200E': 3,
    '\u202C': 4, '\u202D': 5, '\u2062': 6, '\u2063': 7, '\uFEFF': 8
}
digits9 = [char_to_digit_9.get(c, -1) for c in invisible_only]
result2 = ''
for i in range(0, len(digits9) - 4, 5):
    group = digits9[i:i+5]
    val = 0
    for d in group:
        val = val * 9 + d
    try:
        if val <= 0x10FFFF:
            result2 += chr(val)
        else:
            result2 += f'[{val}]'
    except:
        result2 += f'[{val}]'
print(f"  Result: {repr(result2)}")

# MAPPING 3: 330k with different char order (maybe custom selection)
# What if the order is different? Let me try: 
# Selected chars: 200B, 200C, 200D, 202C, 202D, 2062, 2063, FEFF (8 chars, base 8)
# ceil(log_8(65536)) = ceil(16/3) = 6 chars per group? No, ceil(5.33) = 6
print("\n=== MAPPING 3: 8 chars (no 200E, no 202A), base-8, groups of 6 ===")
# ceil(log_8(65536)) = ceil(5.33) = 6
char_to_digit_8 = {
    '\u200B': 0, '\u200C': 1, '\u200D': 2,
    '\u202C': 3, '\u202D': 4, '\u2062': 5, '\u2063': 6, '\uFEFF': 7
}
# But we have U+200E once... remove it
filtered = [c for c in invisible_only if c != '\u200E']
digits8 = [char_to_digit_8.get(c, -1) for c in filtered]
result3 = ''
for i in range(0, len(digits8) - 5, 6):
    group = digits8[i:i+6]
    val = 0
    for d in group:
        val = val * 8 + d
    try:
        result3 += chr(val) if val < 0x10FFFF else f'[{val}]'
    except:
        result3 += f'[{val}]'
print(f"  Chars: {len(filtered)}, Groups of 6: {len(filtered)//6}")
print(f"  Result: {repr(result3)}")

# MAPPING 4: Maybe only 8 chars selected but excluding 200E 
# Order: 200B(0), 200C(1), 200D(2), 202C(3), 202D(4), 2062(5), 2063(6), FEFF(7)
# Groups of 6 (since ceil(log_8(65536)) = 6)
# And including 200E as a digit 3 replacing 202C
print("\n=== MAPPING 4: With 200E mapped differently ===")
# What if we include 200E in the sequence at position 3?
# Full 10 chars but if 202A is not used, shift: 200E is 3, everything after shifts down
# 0:200B, 1:200C, 2:200D, 3:200E, 4:202C, 5:202D, 6:2062, 7:2063, 8:FEFF
# That's 9 chars! Groups of 5: ceil(log_9(65536)) = ceil(5.05) = 6? No wait, 9^5=59049, close but barely over 65536
# So groups of 5 works: 9^5 = 59049 < 65536
# Actually 9^5 = 59049 which is LESS than 65536, so we need 6 groups
# 9^6 = 531441 > 65536, so groups of 6 would work
# But 349 / 6 = 58.16... 349/5 = 69.8
# Let's try groups of 5 first since 349 is not divisible by 6

# Actually wait: 349 chars. 349/5 = 69.8, 349/6 = 58.16. Not clean.
# But what about if we remove the 1 occurrence of 200E? 348/6 = 58!
print(f"  After removing 200E: {len(filtered)} chars / 6 = {len(filtered)/6}")

# Or 349/7 = 49.8... nope

# MAPPING 5: Actually let me try the 330k decode with base 10 properly
# The page showed the available chars include U+202A. But in our text we have U+202C and U+202D.
# Maybe the user selected 9 chars (all except U+202A), making it base 9
# ceil(log_9(65536)) = ceil(5.05) = 6 groups? Wait:
# 9^5 = 59049 < 65536... need more than 5
# 9^6 = 531441 > 65536. So groups of 6.
# 348 / 6 = 58. That's perfect!

print("\n=== MAPPING 5: 9 chars (no 202A), base-9, groups of 6 ===")
char_to_digit_9v2 = {
    '\u200B': 0, '\u200C': 1, '\u200D': 2, '\u200E': 3,
    '\u202C': 4, '\u202D': 5, '\u2062': 6, '\u2063': 7, '\uFEFF': 8
}
# Use 'filtered' which has 200E removed... wait no, 200E is one of our 9 chars.
# Let's use all invisible chars directly with this mapping
# 349 total... 349/6 = 58.16. Off by 1.
# Maybe the 200E at position 9 is part of data, not extra
# 349/6 = 58 remainder 1. One extra char.
# Let's try ignoring the last char
result5 = ''
chars_for_decode = invisible_only
d5 = [char_to_digit_9v2[c] for c in chars_for_decode]
for i in range(0, len(d5) - 5, 6):
    group = d5[i:i+6]
    val = 0
    for d in group:
        val = val * 9 + d
    try:
        result5 += chr(val)
    except:
        result5 += f'[{val}]'
print(f"  Result ({len(result5)} chars): {repr(result5)}")
# Print printable ASCII
ascii_result5 = ''.join(c if c.isprintable() else f'[U+{ord(c):04X}]' for c in result5)
print(f"  Printable: {ascii_result5}")

# MAPPING 6: Try the original 10-char mapping where U+202A is NOT present but the 
# numbering is still 0-9 for the 10 original chars
# BUT since we don't have U+202A, digit 4 never appears
# Groups of 5 (ceil(log_10(65536)) = 5)
# 349/5 = 69.8 — not clean. Maybe the data between visible text boundaries counts differently?

# MAPPING 7: Let's try a different approach entirely.
# What if the user pasted the data from a tool that uses a different char set?
# Let's try the Holloway steg tool approach or zwsp-steg
# zwsp-steg typically uses: 200B=0, 200C=1 (binary), groups of 8 or 16

# MAPPING 8: Let me try the exact 330k decoding algorithm from its source code
# The JS source converts chars to radix, then back to UTF-16 code points
# With all 10 chars: radix=10, group size = ceil(log10(65536)) = 5
# With 9 chars: radix=9, group size = ceil(log9(65536)) = 6
# With 8 chars: radix=8, group size = ceil(log8(65536)) = 6
# With 4 chars (default): radix=4, group size = ceil(log4(65536)) = 8

# Let me check: what if some chars are used in both encoding and as word separators?
# In the 330k tool, the steg chars are interspersed between visible text "words"
# The decoding extracts ALL steg chars, ignoring visible chars, then groups them

# Let me try: just use the 10-char mapping with groups of 5
# 349 total invisible chars. 349/5 = 69.8. But maybe some are padding?
# The last group might be padded with leading zeros (200B)

# Try both trimming last 4 chars and keeping all
print("\n=== MAPPING 8: 10-char, base-10, groups of 5 (pad last group) ===")
d10 = [char_to_digit_330k.get(c, 0) for c in invisible_only]  # treat unknown as 0
remainder = len(d10) % 5
if remainder != 0:
    # Pad with 0s to fill last group
    d10.extend([0] * (5 - remainder))
result8 = ''
for i in range(0, len(d10), 5):
    group = d10[i:i+5]
    val = group[0]*10000 + group[1]*1000 + group[2]*100 + group[3]*10 + group[4]
    try:
        if val == 0:
            result8 += '[NUL]'
        else:
            result8 += chr(val)
    except:
        result8 += f'[{val}]'
print(f"  Result ({len(result8)} chars): {repr(result8)}")
ascii_result8 = ''.join(c if c.isprintable() else f'[U+{ord(c):04X}]' for c in result8)
print(f"  Printable: {ascii_result8}")

# MAPPING 9: Try dropping U+200E from the char set (since it only appears once, maybe it's a typo/noise)
# and use: 200B(0), 200C(1), 200D(2), 202C(3), 202D(4), 2062(5), 2063(6), FEFF(7)
# That's 8 chars (base 8), groups of ceil(log8(65536)) = 6
print("\n=== MAPPING 9: 8 chars (no 200E), base-8, groups of 6 ===")
char_to_digit_8v2 = {
    '\u200B': 0, '\u200C': 1, '\u200D': 2,
    '\u202C': 3, '\u202D': 4, '\u2062': 5, '\u2063': 6, '\uFEFF': 7
}
# Filter out 200E
filtered8 = [c for c in invisible_only if c in char_to_digit_8v2]
d8 = [char_to_digit_8v2[c] for c in filtered8]
print(f"  Chars: {len(filtered8)}, Groups of 6: {len(filtered8)/6}")
remainder8 = len(d8) % 6  
if remainder8:
    d8.extend([0] * (6 - remainder8))
result9 = ''
for i in range(0, len(d8), 6):
    group = d8[i:i+6]
    val = 0
    for d in group:
        val = val * 8 + d
    try:
        if val == 0:
            result9 += '[NUL]'
        elif val <= 0x10FFFF:
            result9 += chr(val)
        else:
            result9 += f'[{val}]'
    except:
        result9 += f'[{val}]'
ascii_result9 = ''.join(c if c.isprintable() else f'[U+{ord(c):04X}]' for c in result9)
print(f"  Result: {ascii_result9}")

# FINAL: Let's try with the web tool directly via browser
# But first, let me also try if the 330k tool uses a DIFFERENT order
# Maybe the order is sorted by unicode value: 200B, 200C, 200D, 200E, 202C, 202D, 2062, 2063, FEFF
# (9 chars, skip 202A since it's not in data)
# This is actually the same as MAPPING 5

# One more thing: what if the encoding uses a DIFFERENT group size?
# Let me try all group sizes from 3 to 8 with the 9-char base-9 mapping
print("\n=== BRUTEFORCE: 9 chars, base-9, various group sizes ===")
for gs in range(3, 9):
    d = [char_to_digit_9v2[c] for c in invisible_only]
    if len(d) % gs:
        d.extend([0] * (gs - len(d) % gs))
    result = ''
    for i in range(0, len(d), gs):
        group = d[i:i+gs]
        val = 0
        for digit in group:
            val = val * 9 + digit
        try:
            if 32 <= val <= 126:
                result += chr(val)
            elif val == 0:
                result += '.'
            else:
                result += '?'
        except:
            result += '?'
    alpha_count = sum(1 for c in result if c.isalnum())
    print(f"  Group {gs}: alpha={alpha_count}/{len(result)} => {result[:80]}")
