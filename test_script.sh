#!/bin/bash

echo "========================================="
echo "  PLAYFAIR CIPHER PROJECT TEST SCRIPT  "
echo "========================================="

# Test 1: Create a test message file
echo "Creating test message file..."
echo -e "Hello World!\nThis is a test message.\nWith multiple lines and numbers: 123\nSpecial chars: @#$%" > test_message.txt

echo "Test message created:"
cat test_message.txt

echo ""
echo "========================================="
echo "Running basic functionality test..."
echo "========================================="

# Test 2: Automated test (you can run this manually)
echo "To test the program:"
echo "1. Run: ./playfair"
echo "2. Enter keyword: TEST123"
echo "3. Choose option 11 to create sample files"
echo "4. Choose option 3 to encrypt a file"
echo "5. Choose option 4 to decrypt the file"
echo "6. Compare original vs decrypted to verify formatting"

echo ""
echo "Compile command used: g++ -o playfair main.cpp playfair.cpp"
echo "Run command: ./playfair"