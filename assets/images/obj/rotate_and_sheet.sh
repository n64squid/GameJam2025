#!/usr/bin/env bash
set -e

prefix="$1"

if [ -z "$prefix" ]; then
    echo "Usage: $0 <prefix>"
    exit 1
fi

# Collect matching files, sorted numerically
mapfile -t files < <(ls "${prefix}_"*.png | sort -V)

count=${#files[@]}
if (( count < 2 )); then
    echo "Not enough files to rotate"
    exit 1
fi

# Move to temp names
for i in "${!files[@]}"; do
    mv "${files[$i]}" "${prefix}_tmp_$i.png"
done

# Rotate: last -> first, others shift forward
mv "${prefix}_tmp_$((count-1)).png" "${prefix}_0.png"
for ((i=0; i<count-1; i++)); do
    mv "${prefix}_tmp_$i.png" "${prefix}_$((i+1)).png"
done

# Create spritesheet
magick "${prefix}_"*.png +append "${prefix}_spritesheet.png"

echo "Created ${prefix}_spritesheet.png"
