# Creates the example output
echo NOT ENOUGH INPUT > not.txt
echo -n "NOT ENOUGH INPUT" > idk.txt

# Runs the program
./calc 4 > output.txt 

# Ensures exit code is one (non-zero).
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm not.txt
    exit 1
fi

#Compare bad_input with output
diff output.txt not.txt
if [ $? -eq 1 ]; then
    echo "Test failed: A sum was output."
    rm output.txt
    rm not.txt
    exit 1
fi

./calc 4 
if [ $? -eq 0 ]; then
    echo "Test failed."
    rm output.txt
    exit 1
fi

diff output.txt idk.txt
if [ $? -eq 0 ]; then
    echo "Test failed."
    rm output.txt
    exit 1
fi

# Prints a message on success
echo "Output was as expected: PASS."
# Cleans up files created
rm output.txt
rm not.txt
rm idk.txt
exit 0
