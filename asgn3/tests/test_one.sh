#!/bin/bash

# Generate input file
echo -e "Line 1\nLine 2\nLine 3" > input.txt

# Generate output file using delayinput.sh
./delayinput.sh input.txt > output.txt

# Run xd program on the output file
./xd output.txt > xd_output.txt

echo xd_output.txt
# Compare output with expected output
expected_output=$(cat <<EOF
00000000: 4c69 6e65 2031 0a4c 696e 6520 320a 4c69  Line 1.Line 2.Li
00000010: 6e65 2033 0a                             ne 3.
EOF
)

echo "$expected_output" > expected_output.txt
if ! diff -u xd_output.txt expected_output.txt; then
    echo "Error: Output mismatch."
    exit 1
fi


echo "Test passed: xd program produced the expected output."

# Clean up
rm input.txt output.txt xd_output.txt

