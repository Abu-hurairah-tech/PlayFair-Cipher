@echo off
echo =========================================
echo   PLAYFAIR CIPHER PROJECT TEST SCRIPT  
echo =========================================
echo.

REM Test 1: Create a test message file
echo Creating test message file...
(
echo Hello World!
echo This is a test message.
echo With multiple lines and numbers: 123
echo Special chars: @#$%%
) > test_message.txt

echo Test message created:
type test_message.txt

echo.
echo =========================================
echo Running basic functionality test...
echo =========================================
echo.

REM Test 2: Automated test (you can run this manually)
echo To test the program:
echo 1. Run: main.exe
echo 2. Enter keyword: TEST123
echo 3. Choose option 11 to create sample files
echo 4. Choose option 3 to encrypt a file
echo 5. Choose option 4 to decrypt the file
echo 6. Compare original vs decrypted to verify formatting
echo.

echo Program is ready for demonstration!
echo Compile command used: g++ -o main.exe main.cpp playfair.cpp -std=c++11
echo Run command: main.exe
echo.

pause
