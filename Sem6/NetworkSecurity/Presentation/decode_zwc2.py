#!/usr/bin/env python3
"""More sophisticated zero-width Unicode steganography decoder."""

text = "\u200B\u200B\u200B\u202D\u202D\u200B\u200B\u200B\u200D\u200E\u202C\u200B\u200B\u200B\u200C\u200D\u202C\u200B\u200B\u200B\u200C\u202C\u202C\u200B\u200B\u200B\u200C\u2063\u200B\u202D\u202D\u200B\u200B\u200B\u200C\u2062\uFEFF\u200B\u200B\u200B\u200C\u200D\u2062\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u202C\u200B\u200B\u200B\u200B\u200D\u202C\u2062BITSCTF\u200B\u200B\u200B\u200C\u200D\u202C\u200B\u200B\u200B\u200C\u202C\u202C\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u2062\uFEFF\u200B\u200B\u200B\u200C\u200D\u2062{\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u202C\u200B\u200B\u200B\u200B\u200D\u202C\u2062\u200B\u200B\u200B\u200D\u200C\u2062\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200C\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200C\u200B\u2062\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200B\uFEFF\uFEFFyour_\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200D\uFEFF\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200C\u200B\uFEFF\u200B\u200B\u200B\u200D\u200B\uFEFF\u200B\u200B\u200B\u200C\u200B\u200B\u200B\u200B\u200B\u200D\u200C\u2063\u200B\u200B\u200B\u200D\u200B\u2063\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u200B\u200Cflag\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200B\u2062\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200D\u200C\u202C\u200B\u200B\u200B\u200D\u200C\u202C\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200D\u202C\uFEFF_goes_here}"

invisible_set = {'\u200B', '\u200C', '\u200D', '\u200E', '\u202C', '\u202D', '\u2062', '\u2063', '\uFEFF'}
invisible_only = [c for c in text if c in invisible_set]

print("=== RAW CHAR SEQUENCE (first 100) ===")
for i, c in enumerate(invisible_only[:200]):
    print(f"  {i:3d}: U+{ord(c):04X}", end='')
    if (i+1) % 10 == 0:
        print()
print()

# Look for repeating group patterns
print("\n=== LOOKING FOR GROUP SIZE PATTERNS ===")
# The data seems to have groups of 6 characters (5 data + 1 delimiter or similar)
# Let's check if chars at position 6n-1 are consistently "delimiter" chars
for group_sz in range(4, 10):
    delimiter_chars = set()
    for i in range(group_sz - 1, len(invisible_only), group_sz):
        delimiter_chars.add(f"U+{ord(invisible_only[i]):04X}")
    if len(delimiter_chars) <= 5:
        print(f"  Group size {group_sz}: last-char set = {delimiter_chars}")

# METHOD A: Groups of 6, where chars 1-4 are data (200B=0,200C=1,200D=2) and chars 5-6 delimiters
# Let's try splitting into fixed groups of 6 and see what positions 4 and 5 contain
print("\n=== POSITIONS ANALYSIS (groups of 6) ===")
for pos in range(6):
    chars_at_pos = set()
    for i in range(pos, len(invisible_only), 6):
        chars_at_pos.add(f"U+{ord(invisible_only[i]):04X}")
    print(f"  Position {pos}: {chars_at_pos}")

# METHOD B: Try reading as groups separated by SPECIFIC single delimiter chars
# Looking at the data, let's check what follows every 200B 200B 200B pattern
print("\n=== PATTERNS AFTER '200B 200B 200B' ===")
from collections import Counter
patterns_after = Counter()
for i in range(len(invisible_only) - 5):
    if invisible_only[i] == '\u200B' and invisible_only[i+1] == '\u200B' and invisible_only[i+2] == '\u200B':
        next_three = tuple(f"U+{ord(c):04X}" for c in invisible_only[i+3:i+6])
        patterns_after[next_three] += 1
for p, c in patterns_after.most_common(20):
    print(f"  {p}: {c}")

# METHOD C: The encoding might use position-based mapping
# Look at positions where 200E appears (it only appears once)
for i, c in enumerate(invisible_only):
    if c == '\u200E':
        print(f"\n200E found at position {i}")

# METHOD D: Try interpreting as groups of 6 with custom base encoding
print("\n=== METHOD D: Groups of 6, mixed base ===")
# Positions 0-2 might be the "header" (always 000 or 00x)
# Positions 3-4 are data
# Position 5 is type/delimiter

# Let's look at just positions 3 and 4 in each group of 6
if len(invisible_only) % 6 == 0 or True:
    print("Groups of 6, chars at pos 3,4,5:")
    results_d = []
    for i in range(0, len(invisible_only) - 5, 6):
        group = invisible_only[i:i+6]
        group_hex = [f"U+{ord(c):04X}" for c in group]
        
        # Try: pos 3-4 encode the value using {200B:0, 200C:1, 200D:2, 200E:3, 202C:4, 202D:5, ...}
        char_to_digit = {'\u200B': 0, '\u200C': 1, '\u200D': 2, '\u200E': 3, 
                         '\u202C': 4, '\u202D': 5, '\u2062': 6, '\u2063': 7, '\uFEFF': 8}
        # pos3*9 + pos4 gives 0-80
        val_34 = char_to_digit[group[3]] * 9 + char_to_digit[group[4]]
        # Or use all positions
        val_all = 0
        for c in group:
            val_all = val_all * 9 + char_to_digit[c]
        
        # Just positions 3 and 4
        char34 = chr(val_34) if 32 <= val_34 < 127 else f'[{val_34}]'
        results_d.append(char34)
        print(f"  {group_hex} -> pos34={val_34}({char34})")
    print(f"\nResult (pos 3-4): {''.join(results_d)}")

# METHOD E: Try treating the 4th and 5th chars as base-9 pair, offset by 32
print("\n=== METHOD E: pos 3-4 as base-9, offset adjustments ===")
for offset in [0, 32, 33, 48]:
    results_e = []
    char_to_digit = {'\u200B': 0, '\u200C': 1, '\u200D': 2, '\u200E': 3, 
                     '\u202C': 4, '\u202D': 5, '\u2062': 6, '\u2063': 7, '\uFEFF': 8}
    for i in range(0, len(invisible_only) - 5, 6):
        group = invisible_only[i:i+6]
        val = char_to_digit[group[3]] * 9 + char_to_digit[group[4]] + offset
        char = chr(val) if 32 <= val < 127 else f'[{val}]'
        results_e.append(char)
    print(f"  Offset {offset}: {''.join(results_e)}")

# METHOD F: what if chars encode individual bits in groups, 
# with specific chars as word separators?
print("\n=== METHOD F: Mapping all chars to 0-8, try as ASCII directly ===")
char_to_digit = {'\u200B': 0, '\u200C': 1, '\u200D': 2, '\u200E': 3, 
                 '\u202C': 4, '\u202D': 5, '\u2062': 6, '\u2063': 7, '\uFEFF': 8}
digits = [char_to_digit[c] for c in invisible_only]

# Try treating every 3 consecutive digits as base-9 number (0-728, only take printable ASCII)
for base in [4, 5, 8, 9, 10, 16]:
    for group_sz in [2, 3]:
        result = []
        for i in range(0, len(digits) - group_sz + 1, group_sz):
            val = 0
            for j in range(group_sz):
                val = val * base + min(digits[i+j], base-1)
            if 32 <= val < 127:
                result.append(chr(val))
            else:
                result.append('?')
        s = ''.join(result)
        if sum(1 for c in s if c.isalpha()) > len(s) * 0.3:
            print(f"  base={base} group={group_sz}: {s}")
