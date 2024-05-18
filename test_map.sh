#!/bin/bash

# Define the directory containing the maps
map_dir="maps"

# Loop through each file in the map directory
for map_file in "$map_dir"/*; do
  # Check if it's a regular file (not a directory or hidden file)
  if [[ -f "$map_file" ]]; then
    # Extract the filename without the path
    filename=$(basename "$map_file")
    
    # Run cub3d with the current map file
    ./cub3d "$map_file"
    
    # Optional: Add a pause between maps (adjust sleep time as desired)
    # sleep 2
  fi
done

echo "Processed all maps in $map_dir"

