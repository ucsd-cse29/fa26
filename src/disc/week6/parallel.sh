#!/bin/bash
start_time=$SECONDS

echo "Dispatching 4 workers in parallel..."

for i in {1..4}; do
    (
        delay=$((RANDOM % 4 + 2))
        echo "Worker $i started (will take ${delay}s)..."
        sleep $delay
        echo "Worker $i finished!"
    ) &
done

echo "Main process waiting for completion..."
wait

echo "All workers completed in $((SECONDS - start_time)) seconds!"
