# Creates the example output
echo -e "3.0000000000\n4.0000000000" > expected.txt

# Runs the program
echo -e "1 2 +\n1 3 +" | ./calc > output.txt

# Ensures exit code is non-Zero
if [ $? -eq 1 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

#Compare bad_input with output
diff output.txt expected.txt
if [ $? -eq 1 ]; then
    echo "Test failed."
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "PASS."
# Cleans up files created
rm output.txt
rm expected.txt
exit 0
