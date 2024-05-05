In a Bash script, you can use the set -e command to make the script exit if any command returns a non-zero status, which usually indicates an error. To capture the last command being run, you can use the trap command with the DEBUG and ERR signals.

Here's an example:

```bash
#!/bin/bash

set -e

trap 'last_command=$current_command; current_command=$BASH_COMMAND' DEBUG
trap 'echo "\"${last_command}\" command filed with exit code $?."' ERR

# Your commands here
```

```bash
#!/bin/bash

set -e

function error_handler {
    local err_line=$1
    echo "An error occurred in line ${err_line} while executing: ${last_command}"
    # Add your error handling code here
}

trap 'last_command=$BASH_COMMAND; last_line=${BASH_LINENO[0]}' ERR
trap 'error_handler $last_line' EXIT

# Your commands here
```