#!/usr/bin/env bash
n=0
echo "while loop"
while [ $n -lt 10 ]; do
  echo $n
  n=$((n + 1))
done

echo "for loop"
for i in {1..4}; do
  echo "loop number $i"
done

