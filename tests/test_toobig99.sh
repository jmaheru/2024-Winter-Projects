# Creates the example output
echo -n "0" > expected.txt

# Runs the program
./calc 0 0 > output.txt 

# Ensures exit code is non-Zero
if [ $? -eq 1 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

#Compare bad_input with output
diff output.txt expected.txt
if [ $? -eq 0 ]; then
    echo "Test failed expected."
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Output was TOO BIG: PASS."
# Cleans up files created
rm output.txt
rm expected.txt
exit 0
