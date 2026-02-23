#!/usr/bin/env python3
"""Decode zero-width Unicode steganography from CTF challenge."""

text = "\u200B\u200B\u200B\u202D\u202D\u200B\u200B\u200B\u200D\u200E\u202C\u200B\u200B\u200B\u200C\u200D\u202C\u200B\u200B\u200B\u200C\u202C\u202C\u200B\u200B\u200B\u200C\u2063\u200B\u202D\u202D\u200B\u200B\u200B\u200C\u2062\uFEFF\u200B\u200B\u200B\u200C\u200D\u2062\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u202C\u200B\u200B\u200B\u200B\u200D\u202C\u2062BITSCTF\u200B\u200B\u200B\u200C\u200D\u202C\u200B\u200B\u200B\u200C\u202C\u202C\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u2062\uFEFF\u200B\u200B\u200B\u200C\u200D\u2062{\u200B\u200B\u200B\u200C\u2063\u200B\u200B\u200B\u200B\u200C\u202C\u200B\u200B\u200B\u200B\u200D\u202C\u2062\u200B\u200B\u200B\u200D\u200C\u2062\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200C\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200C\u200B\u2062\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200B\uFEFF\uFEFFyour_\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200B\u200D\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200D\uFEFF\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200C\u200B\uFEFF\u200B\u200B\u200B\u200D\u200B\uFEFF\u200B\u200B\u200B\u200C\u200B\u200B\u200B\u200B\u200B\u200D\u200C\u2063\u200B\u200B\u200B\u200D\u200B\u2063\u200B\u200B\u200B\u200C\uFEFF\u2062\u200B\u200B\u200B\u200D\u200B\u200Cflag\u200B\u200B\u200B\u200C\u200B\u202C\u200B\u200B\u200B\u200D\u200D\u200D\u200B\u200B\u200B\u200C\u200B\u200D\u200B\u200B\u200B\u200D\u200B\u2062\u200B\u200B\u200B\u200D\u200D\u2063\u200B\u200B\u200B\u200D\u200C\u202C\u200B\u200B\u200B\u200D\u200C\u202C\u200B\u200B\u200B\u200D\u202C\u200D\u200B\u200B\u200B\u200D\u202C\uFEFF_goes_here}"

# All zero-width/invisible characters
invisible_set = {'\u200B', '\u200C', '\u200D', '\u200E', '\u202C', '\u202D', '\u2062', '\u2063', '\uFEFF'}

# Extract only invisible chars
invisible_only = [c for c in text if c in invisible_set]
print(f"Total invisible chars: {len(invisible_only)}")
print(f"Unique chars: {sorted(set(hex(ord(c)) for c in invisible_only))}")
print(f"Char counts:")
from collections import Counter
for c, count in Counter(invisible_only).most_common():
    print(f"  U+{ord(c):04X}: {count}")

print("\n" + "="*60)
print("METHOD 1: Ternary (200B=0, 200C=1, 200D=2), split by others")
print("="*60)
groups = []
current_group = []
for c in invisible_only:
    if c in ('\u200B', '\u200C', '\u200D'):
        current_group.append(c)
    else:
        if current_group:
            groups.append(current_group[:])
        current_group = []
if current_group:
    groups.append(current_group[:])

ternary_map = {'\u200B': 0, '\u200C': 1, '\u200D': 2}
result = ''
for g in groups:
    val = 0
    for c in g:
        val = val * 3 + ternary_map[c]
    tern_str = ''.join(str(ternary_map[c]) for c in g)
    char = chr(val) if 32 <= val < 127 else f'[{val}]'
    result += char if 32 <= val < 127 else ''
    print(f"  len={len(g)} tern={tern_str} val={val} char={char}")
print(f"Result: {result}")

print("\n" + "="*60)
print("METHOD 2: Quaternary (200B=0, 200C=1, 200D=2, FEFF=3), split by others")
print("="*60)
groups2 = []
current_group2 = []
for c in invisible_only:
    if c in ('\u200B', '\u200C', '\u200D', '\uFEFF'):
        current_group2.append(c)
    else:
        if current_group2:
            groups2.append(current_group2[:])
        current_group2 = []
if current_group2:
    groups2.append(current_group2[:])

quat_map = {'\u200B': 0, '\u200C': 1, '\u200D': 2, '\uFEFF': 3}
result2 = ''
for g in groups2:
    val = 0
    for c in g:
        val = val * 4 + quat_map[c]
    char = chr(val) if 32 <= val < 127 else f'[{val}]'
    result2 += char if 32 <= val < 127 else ''
    print(f"  len={len(g)} val={val} char={char}")
print(f"Result: {result2}")

print("\n" + "="*60)
print("METHOD 3: Binary (200B=0, 200C=1), ignore others entirely")
print("="*60)
binary = ''.join('0' if c == '\u200B' else '1' if c == '\u200C' else '' for c in invisible_only)
print(f"Binary string ({len(binary)} bits): {binary}")
for bits in [7, 8]:
    result3 = ''
    for i in range(0, len(binary) - bits + 1, bits):
        val = int(binary[i:i+bits], 2)
        result3 += chr(val) if 32 <= val < 127 else f'[{val}]'
    print(f"  {bits}-bit: {result3}")

print("\n" + "="*60)
print("METHOD 4: Binary (200B=0, others=1), 8-bit groups")
print("="*60)
binary4 = ''.join('0' if c == '\u200B' else '1' for c in invisible_only)
result4 = ''
for i in range(0, len(binary4) - 7, 8):
    val = int(binary4[i:i+8], 2)
    result4 += chr(val) if 32 <= val < 127 else f'[{val}]'
print(f"  Result: {result4}")

print("\n" + "="*60)
print("METHOD 5: All 9 chars as base-9 digits, groups of 2")
print("="*60)
char_map9 = {
    '\u200B': 0, '\u200C': 1, '\u200D': 2, '\u200E': 3,
    '\u202C': 4, '\u202D': 5, '\u2062': 6, '\u2063': 7, '\uFEFF': 8
}
vals9 = [char_map9[c] for c in invisible_only]
result5 = ''
for i in range(0, len(vals9) - 1, 2):
    val = vals9[i] * 9 + vals9[i+1]
    result5 += chr(val) if 32 <= val < 127 else f'[{val}]'
print(f"  Result: {result5}")

print("\n" + "="*60)
print("METHOD 6: Groups of 6 chars, binary (200B=0, 200C=1, 200D=1)")
print("="*60)
binary6 = ''.join('0' if c == '\u200B' else '1' for c in invisible_only if c in ('\u200B', '\u200C', '\u200D'))
for bits in [5, 6, 7, 8]:
    result6 = ''
    for i in range(0, len(binary6) - bits + 1, bits):
        val = int(binary6[i:i+bits], 2)
        result6 += chr(val) if 32 <= val < 127 else f'[{val}]'
    print(f"  {bits}-bit: {result6}")

print("\n" + "="*60)
print("METHOD 7: Fixed 6-char groups from all invisible chars")
print("="*60)
for group_size in [3, 4, 5, 6]:
    result7 = ''
    for i in range(0, len(invisible_only) - group_size + 1, group_size):
        # Treat each char as a binary digit: 200B=0, anything else=1
        bits = ''.join('0' if invisible_only[i+j] == '\u200B' else '1' for j in range(group_size))
        val = int(bits, 2)
        result7 += chr(val) if 32 <= val < 127 else f'[{val}]'
    print(f"  Group size {group_size}: {result7}")

print("\n" + "="*60)
print("METHOD 8: Ternary groups split by 2062/2063/202C/202D (as delimiters)")
print("="*60)
delimiters = {'\u202C', '\u202D', '\u2062', '\u2063', '\u200E'}
data_chars = {'\u200B', '\u200C', '\u200D', '\uFEFF'}
groups8 = []
current8 = []
for c in invisible_only:
    if c in data_chars:
        current8.append(c)
    elif c in delimiters:
        if current8:
            groups8.append(current8[:])
        current8 = []
if current8:
    groups8.append(current8[:])

# Try with 200B=0, 200C=1, 200D=2, FEFF=3 as base-4
result8 = ''
qm = {'\u200B': 0, '\u200C': 1, '\u200D': 2, '\uFEFF': 3}
for g in groups8:
    val = 0
    for c in g:
        val = val * 4 + qm[c]
    char = chr(val) if 32 <= val < 127 else f'[{val}]'
    result8 += char if 32 <= val < 127 else ''
    print(f"  len={len(g)}: {[hex(ord(c)) for c in g]} -> val={val} char={char}")
print(f"Result: {result8}")

print("\n" + "="*60)
print("METHOD 9: Using 330k-style encoding")
print("="*60)
# 330k tool: U+200B=0, U+200C=1, U+200D=2, U+FEFF=3 (base-4)
# Groups of 4 quaternary digits = 1 byte (4^4 = 256)
q_chars = [c for c in invisible_only if c in ('\u200B', '\u200C', '\u200D', '\uFEFF')]
q_vals = [qm[c] for c in q_chars]
print(f"  Quaternary chars count: {len(q_chars)}")
for group_size in [3, 4, 5]:
    result9 = ''
    for i in range(0, len(q_vals) - group_size + 1, group_size):
        val = 0
        for j in range(group_size):
            val = val * 4 + q_vals[i + j]
        result9 += chr(val) if 32 <= val < 127 else f'[{val}]'
    print(f"  Group size {group_size}: {result9}")
