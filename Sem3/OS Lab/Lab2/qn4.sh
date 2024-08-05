#!/usr/bin/env bash

multiply() {
  result=$(( $1 * $2 ))
  echo $result
}

echo "Enter the first number:"
read num1
echo "Enter the second number:"
read num2

product=$(multiply $num1 $num2)
echo "The product of $num1 and $num2 is: $product"
