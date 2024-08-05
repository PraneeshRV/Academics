#!/usr/bin/env bash
check_command_status() {
  command=$1
  $command
  status=$?
  if [ $status -eq 0 ]; then
    echo "Command '$command' executed successfully with return code $status."
  else
    echo "Command '$command' failed with return code $status."
  fi
}
command_to_check="ls"
echo "Checking execution status for command: $command_to_check"
check_command_status "$command_to_check"

