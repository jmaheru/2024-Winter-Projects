# Creates the example output
echo 7 > 7.txt

# Runs the program
./calc 3 4 > 3.4.txt 

# Ensures exit code is Zero
if [ $? -eq 1 ]; then
    echo "invalid exit code" $?
    rm 3.4.txt
    rm 7.txt
    exit 1
fi

# Ensures differences *are* found
diff 3.4.txt 7.txt
if [ $? -eq 1 ]; then
    echo "Somehow, the output of 3+4 is not 7!"
    rm 3.4.txt
    rm 7.txt
    exit 1
fi

# Prints a message on success
echo "Test found that 3+4 = 7: PASS"

# Cleans up files created
rm 3.4.txt
rm 7.txt
exit 0
