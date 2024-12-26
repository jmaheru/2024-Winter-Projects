# Creates the example output
echo "usage: -h [-mh]" > expected.txt
echo "    -m: use libm trig function implementations instead of custom ones." >> expected.txt
echo "    -h: show help" >> expected.txt

# Runs the program
./calc -h > output.txt

# Ensures exit code is non-Zero
if [ $? -eq 0 ]; then
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
