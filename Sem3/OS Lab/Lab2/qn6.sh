#!/usr/bin/env bash

list_files() {
  files=$(ls)
  echo "$files"
}

count_files() {
  num_files=$(ls | wc -l)
  echo "Number of files: $num_files"
}

list_files
count_files

