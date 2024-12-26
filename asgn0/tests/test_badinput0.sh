# Creates the example output
echo 0 > bad_input.txt

# Runs the program
./calc 1.1 4 

# Ensures exit code is non-Zero
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm bad_input.txt
    exit 1
fi

./calc 1.1 4
echo $? > output.txt

#Compare bad_input with output
diff output.txt bad_input.txt
if [ $? -eq 0 ]; then
    echo "Test failed: A sum was output."
    rm output.txt
    rm bad_input.txt
    exit 1
fi

# Prints a message on success
echo "Output was non-zero: PASS."
# Cleans up files created
rm output.txt
rm bad_input.txt
exit 0
