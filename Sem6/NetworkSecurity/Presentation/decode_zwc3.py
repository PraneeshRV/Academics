#!/usr/bin/env python3
"""Try the 330k Unicode Steganography encoding scheme and other approaches."""

text = "\u200B\u200B\u200B\u202D\u202D\u200B\u200B\u200B\u200D\u200E\u202C\u200B\u200B\u200B\u200C\u200D\u202C\u200B\u200B\u200B\u200C\u202C\u202C\u200B\u200B\u200B\u200C\u2063\u200B\u202D\u202D\u200B\u200B\u200B\u200C\u2062\uFEFF\u200B\u200B\u200B\u200C\u200D\u2062\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u202C\u200B\u200B\u200B\u200B\u200D\u202C\u2062BITSCTF\u200B\u200B\u200B\u200C\u200D\u202C\u200B\u200B\u200B\u200C\u202C\u202C\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u2062\uFEFF\u200B\u200B\u200B\u200C\u200D\u2062{\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u202C\u200B\u200B\u200B\u200B\u200D\u202C\u2062\u200B\u200B\u200B\u200D\u200C\u2062\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200C\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200C\u200B\u2062\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200B\uFEFF\uFEFFyour_\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200D\uFEFF\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200C\u200B\uFEFF\u200B\u200B\u200B\u200D\u200B\uFEFF\u200B\u200B\u200B\u200C\u200B\u200B\u200B\u200B\u200B\u200D\u200C\u2063\u200B\u200B\u200B\u200D\u200B\u2063\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u200B\u200Cflag\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200B\u2062\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200D\u200C\u202C\u200B\u200B\u200B\u200D\u200C\u202C\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200D\u202C\uFEFF_goes_here}"

invisible_set = {'\u200B', '\u200C', '\u200D', '\u200E', '\u202C', '\u202D', '\u2062', '\u2063', '\uFEFF'}
invisible_only = [c for c in text if c in invisible_set]

print(f"Total invisible chars: {len(invisible_only)}")

# APPROACH 1: Groups of 6, map each position to bits based on the char
# Position 1 is always U+200B — could be padding
# Let's look at what each position's char represents in terms of bits

# First, let's try: each group of 6 encodes 1 byte
# The "data" chars are: U+200B(0), U+200C(1), U+200D(2)
# The "metadata/frame" chars provide additional bits

# Let me try: extract chars at positions 0, 2, 3, 4, 5 (skip position 1 which is always 200B)
# and map them

# Approach: What if position 0 and 5 are "frame" bytes that don't contribute to data,
# and positions 2, 3, 4 form a ternary (base-3) number?
print("\n=== Approach: pos 2,3,4 as ternary ===")
ternary_map = {'\u200B': 0, '\u200C': 1, '\u200D': 2}
results = []
for i in range(0, len(invisible_only) - 5, 6):
    g = invisible_only[i:i+6]
    if g[2] in ternary_map and g[3] in ternary_map and g[4] in ternary_map:
        val = ternary_map[g[2]] * 9 + ternary_map[g[3]] * 3 + ternary_map[g[4]]
        results.append(val)
    elif g[2] in ternary_map and g[3] not in ternary_map:
        # g[3] might be a higher-value char
        val3_map = {'\u200B': 0, '\u200C': 1, '\u200D': 2, '\u200E': 3, '\u202C': 4, '\u202D': 5, '\u2062': 6, '\u2063': 7, '\uFEFF': 8}
        val = ternary_map[g[2]] * 81 + val3_map.get(g[3], 0) * 9 + val3_map.get(g[4], 0)
        results.append(val)
    else:
        results.append(-1)

print(f"Values: {results}")
result_str = ''.join(chr(v + 32) if 0 <= v < 95 else f'[{v}]' for v in results)
print(f"ASCII+32: {result_str}")
result_str2 = ''.join(chr(v) if 32 <= v < 127 else f'[{v}]' for v in results)
print(f"Direct: {result_str2}")

# Approach 2: Map full 6-char group using all 9 chars  
# But only use positions 0, 2, 3, 4, 5 (5 positions)
print("\n=== Approach: 5 positions (skip pos1), base-9 ===")
val9_map = {'\u200B': 0, '\u200C': 1, '\u200D': 2, '\u200E': 3, '\u202C': 4, '\u202D': 5, '\u2062': 6, '\u2063': 7, '\uFEFF': 8}
for positions_to_use in [[0,2,3,4], [2,3,4,5], [0,3,4,5], [3,4], [0,5]]:
    results = []
    for i in range(0, len(invisible_only) - 5, 6):
        g = invisible_only[i:i+6]
        val = 0
        for p in positions_to_use:
            val = val * 9 + val9_map[g[p]]
        results.append(val)
    result_str = ''.join(chr(v) if 32 <= v < 127 else f'[{v}]' for v in results)
    printable_count = sum(1 for v in results if 32 <= v < 127)
    print(f"  Positions {positions_to_use}: ({printable_count}/{len(results)} printable) {result_str[:100]}")

# Approach 3: What if we focus on chars 3,4,5 with each being one of 9 values?
# 9^3 = 729 — too big for ASCII
# But 9^2 = 81 — perfect for printable ASCII (32-126 = 95 chars)
# Maybe chars 3 and 4 encode the ASCII char, and the rest is structure

# Approach 4: What if each char in the group represents a bit?
# 200B = 0, everything else = 1, and groups of 6 = 6 bits
print("\n=== Approach: 6 bits per group (200B=0, else=1) ===")
results4 = []
for i in range(0, len(invisible_only) - 5, 6):
    g = invisible_only[i:i+6]
    bits = ''.join('0' if c == '\u200B' else '1' for c in g)
    val = int(bits, 2)
    results4.append(val)
    
result_str4 = ''.join(chr(v) if 32 <= v < 127 else f'[{v}]' for v in results4)
print(f"  Result: {result_str4}")

# Try with offset
for offset in [32, 48, 64]:
    result_str = ''.join(chr(v+offset) if 32 <= v+offset < 127 else f'[{v}]' for v in results4)
    print(f"  +{offset}: {result_str}")

# Approach 5: Binary per group with different mapping
# 200B=0, 200C=1, 200D=1, 200E=1, 202C=0, 202D=0, 2062=0, 2063=0, FEFF=1
print("\n=== Approach: 6 bits, various bit mappings ===")
for mapping_name, map_fn in [
    ("200B/200C=0, rest=1", lambda c: '0' if c in ('\u200B', '\u200C') else '1'),
    ("200B=0, 200C/200D=1, rest=0", lambda c: '1' if c in ('\u200C', '\u200D') else '0'),
    ("data=0(200B),1(200C),1(200D), frame=0", lambda c: {'200B': '0', '200C': '1', '200D': '1'}.get(f'{ord(c):04X}', '0') if True else '0'),
]:
    pass  # Too complex, let me try the online tool approach

# Approach 6: Maybe the encoding is per-character, not per-group
# What if we just concatenate bits from the 4th and 5th positions?
print("\n=== Approach: Concatenate binary from specific positions ===")
for data_pos in [3, 4]:
    bits = ''
    data_map = {'\u200B': '00', '\u200C': '01', '\u200D': '10', '\u200E': '11', 
                '\u202C': '00', '\u202D': '01', '\u2062': '10', '\u2063': '11', '\uFEFF': '00'}
    for i in range(0, len(invisible_only) - 5, 6):
        g = invisible_only[i:i+6]
        bits += data_map[g[data_pos]]
    
    result = ''
    for i in range(0, len(bits) - 7, 8):
        val = int(bits[i:i+8], 2)
        result += chr(val) if 32 <= val < 127 else f'[{val}]'
    print(f"  Position {data_pos}, 2-bit: {result}")

# Approach 7: All 9 unique chars → maybe it's a homoglyph/lookup table
# Let's try if the encoding just maps pairs of (char_at_pos3, char_at_pos5) to ASCII
print("\n=== Approach: Pair (pos3, pos5) or (pos0, pos5) ===")
for p1, p2 in [(3, 5), (0, 5), (0, 2)]:
    pair_set = set()
    for i in range(0, len(invisible_only) - 5, 6):
        g = invisible_only[i:i+6]
        pair = (f'U+{ord(g[p1]):04X}', f'U+{ord(g[p2]):04X}')
        pair_set.add(pair)
    print(f"  Unique pairs at ({p1},{p2}): {len(pair_set)}")

# Approach 8: Try StegCloak decoding
# StegCloak uses ZWC characters to hide encrypted or plain text
# It typically uses: U+200B, U+200C, U+200D, U+FEFF as a base-4 encoding
# But it also has additional metadata/structure
# Try treating the data chars only as base-4 and grouping by 4 (4^4=256=1 byte)
print("\n=== Approach: StegCloak-style (data chars only, base-4, groups of 4) ===")
data_chars_only = [c for c in invisible_only if c in ('\u200B', '\u200C', '\u200D', '\uFEFF')]
print(f"  Data chars count: {len(data_chars_only)}")
qm = {'\u200B': '00', '\u200C': '01', '\u200D': '10', '\uFEFF': '11'}
binary = ''.join(qm[c] for c in data_chars_only)
print(f"  Binary length: {len(binary)}")
result = ''
for i in range(0, len(binary) - 7, 8):
    val = int(binary[i:i+8], 2)
    result += chr(val) if 32 <= val < 127 else f'[{val}]'
print(f"  Result: {result}")

# Try reversed bit order
qm_rev = {'\u200B': '00', '\u200C': '10', '\u200D': '01', '\uFEFF': '11'}
binary_rev = ''.join(qm_rev[c] for c in data_chars_only)
result_rev = ''
for i in range(0, len(binary_rev) - 7, 8):
    val = int(binary_rev[i:i+8], 2)
    result_rev += chr(val) if 32 <= val < 127 else f'[{val}]'
print(f"  Reversed: {result_rev}")

# Try yet another mapping
for name, mapping in [
    ("FEFF=0,200B=1,200C=2,200D=3", {'\uFEFF': '00', '\u200B': '01', '\u200C': '10', '\u200D': '11'}),
    ("200D=0,200C=1,200B=2,FEFF=3", {'\u200D': '00', '\u200C': '01', '\u200B': '10', '\uFEFF': '11'}),
    ("200B=0,200D=1,200C=2,FEFF=3", {'\u200B': '00', '\u200D': '01', '\u200C': '10', '\uFEFF': '11'}),
]:
    b = ''.join(mapping[c] for c in data_chars_only)
    r = ''
    for i in range(0, len(b) - 7, 8):
        val = int(b[i:i+8], 2)
        r += chr(val) if 32 <= val < 127 else f'[{val}]'
    printable = sum(1 for c in r if c.isalnum() or c in '_{}')
    print(f"  {name}: ({printable} alphanum) {r[:80]}")

# APPROACH 9: try npx stegcloak
print("\n=== Will try stegcloak via npx ===")
