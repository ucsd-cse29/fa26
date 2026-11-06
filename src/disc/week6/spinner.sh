#!/bin/bash
# 1. Spawn a spinner loop in a background subshell
(while true; do
    for frame in "⠋" "⠙" "⠹" "⠸" "⠼" "⠴" "⠦" "⠧" "⠇" "⠏"; do
        echo -ne "\r$frame Processing heavy task..."
        sleep 0.1
    done
done) &

# 2. Store the Process ID (PID) of the most recently backgrounded process
SPINNER_PID=$!

# 3. Perform work in the foreground
# sleep 5
seconds=10
for ((i = seconds; i > 0; i--)); do
    # \r moves the cursor back to the start of the line
    printf "\rTime remaining: %d seconds" "$i"
    sleep 1
done

printf "\rTime's up!        \n"

# 4. Terminate the background spinner
kill $SPINNER_PID 2>/dev/null
echo -e "\r✓ Task complete!"
