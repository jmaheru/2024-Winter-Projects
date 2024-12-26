# Creates the example output
echo 1 > not.txt

# Runs the program
./calc 4  

# Ensures exit code is one (non-zero).
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm not.txt
    exit 1
fi

./calc 4 
echo $? > output.txt

#Compare bad_input with output
diff output.txt not.txt
if [ $? -eq 1 ]; then
    echo "Test failed: A sum was output."
    rm output.txt
    rm not.txt
    exit 1
fi

# Prints a message on success
echo "Output was as expected: PASS."
# Cleans up files created
rm output.txt
rm not.txt
exit 0
