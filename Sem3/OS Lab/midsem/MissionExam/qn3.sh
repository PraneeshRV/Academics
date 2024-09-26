#!/bin/bash

prime() {
    num=$1
    if [ $num -lt 2 ]; then
        return 1
    fi
    for ((i=2; i*i<=num; i++)); do
        if [ $((num % i)) -eq 0 ]; then
            return 1
        fi
    done
    return 0
}

read -p "Enter your age: " age

if prime $age; then
    filename="process_${age}.txt"
    touch "$filename"

    remainder=$((age % 7))

    echo "Dividing age/7, Remainder = $remainder" > "$filename"

    echo "Age is prime.File $filename created."
else
    sum=0
    for ((i=1; i<=age; i++)); do
        sum=$((sum + i))
    done
    echo "Age is not prime. Sum from 1 to $age is: $sum"
	if [ -f "report.txt" ]; then
        echo "mission almost done" >> report.txt
    fi
fi
