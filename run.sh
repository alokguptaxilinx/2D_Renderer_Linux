#!/bin/bash

# Define the directory where the models are located
MODEL_DIR="meshes/"

# List all the models in the directory
MODELS=$(ls $MODEL_DIR)

# Compile the program
make

# Function to check if the program is running and kill it
kill_program() {
    PID=$(pgrep -f "./bin")
    if [ -n "$PID" ]; then
        kill $PID
    fi
}

# Run each model one by one
for MODEL in $MODELS; do
    # Check if it's a valid model file
    if [[ "$MODEL" == *".obj" ]]; then
        echo "Running model: $MODEL"
        # Kill the existing program
        kill_program
        # Run the program with the model file
        ./bin "$MODEL_DIR$MODEL" &
        sleep 10s  # Wait for 10 seconds before running the next model
    fi
done

# Kill the program after running all the models
kill_program

