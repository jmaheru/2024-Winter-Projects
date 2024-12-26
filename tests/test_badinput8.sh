# Creates the example output
echo "BAD INPUT" > bad_input.txt

# Runs the program
./calc 0.0 4 > output.txt 

# Ensures exit code is non-Zero
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm bad_input.txt
    exit 1
fi

#Compare bad_input with output
diff output.txt bad_input.txt
if [ $? -eq 1 ]; then
    echo "Test failed: A sum was output."
    rm output.txt
    rm bad_input.txt
    exit 1
fi

# Prints a message on success
echo "Output was BAD INPUT: PASS."
# Cleans up files created
rm output.txt
rm bad_input.txt
exit 0
