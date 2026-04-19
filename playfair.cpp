#include "playfair.h"
#include "colors.h"
#include <iostream>
#include <string>
using namespace std;

void Playfair::buildMatrix()
{
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string fullList = keyword + alphabet;
    string preparedString = "";

    for (char c : fullList)
    {
        c = toupper(c);
        if (isalnum(c) && preparedString.find(c) == string::npos)
        {
            preparedString += c;
        }
    }

    int k = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (k < preparedString.length())
                cipher[i][j] = preparedString[k++];
        }
    }
}

Playfair::Playfair(string key)
{
    keyword = key;
    buildMatrix();
}

void Playfair::findPosition(char c, int &row, int &col)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (cipher[i][j] == toupper(c))
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string Playfair::prepareText(string plaintext)
{
    string cleantext = "";
    for (char c : plaintext)
    {
        if (isalnum(c))
            cleantext += toupper(c);
    }
    string preparedText = "";
    for (int i = 0; i < cleantext.length(); i += 2)
    {
        preparedText += cleantext[i];
        if (i + 1 < cleantext.length())
        {
            if (cleantext[i] == cleantext[i + 1])
            {
                char padChar = (cleantext[i] == 'X') ? 'Q' : 'X';
                preparedText += padChar;
                i--;
            }
            else
            {
                preparedText += cleantext[i + 1];
            }
        }
        else
        {
            char padChar = (cleantext[i] == 'X') ? 'Q' : 'X';
            preparedText += padChar;
        }
    }
    return preparedText;
}

string Playfair::encrypt(string plaintext)
{
    string preparedText = prepareText(plaintext);
    string encryptedText = "";
    for (int i = 0; i < preparedText.length(); i += 2)
    {
        int row1, row2, col1, col2;
        findPosition(preparedText[i], row1, col1);
        findPosition(preparedText[i + 1], row2, col2);

        if (row1 == row2)
        {
            encryptedText += cipher[row1][(col1 + 1) % 6];
            encryptedText += cipher[row2][(col2 + 1) % 6];
        }
        else if (col1 == col2)
        {
            encryptedText += cipher[(row1 + 1) % 6][col1];
            encryptedText += cipher[(row2 + 1) % 6][col2];
        }
        else
        {
            encryptedText += cipher[row1][col2];
            encryptedText += cipher[row2][col1];
        }
    }
    return encryptedText;
}

string Playfair::decrypt(string encryptedText)
{
    string decryptedText = "";
    for (int i = 0; i < encryptedText.length(); i += 2)
    {
        int row1, row2, col1, col2;
        findPosition(encryptedText[i], row1, col1);
        findPosition(encryptedText[i + 1], row2, col2);

        if (row1 == row2)
        {
            decryptedText += cipher[row1][(col1 + 5) % 6];
            decryptedText += cipher[row2][(col2 + 5) % 6];
        }
        else if (col1 == col2)
        {
            decryptedText += cipher[(row1 + 5) % 6][col1];
            decryptedText += cipher[(row2 + 5) % 6][col2];
        }
        else
        {
            decryptedText += cipher[row1][col2];
            decryptedText += cipher[row2][col1];
        }
    }
    return decryptedText;
}

// Enhanced file operations - Legacy methods (kept for compatibility)
void Playfair::encryptFile(string inputFileName, string outputFileName)
{
    encryptFilePreserveFormat(inputFileName, outputFileName);
}

void Playfair::decryptFile(string inputFileName, string outputFileName)
{
    decryptFilePreserveFormat(inputFileName, outputFileName);
}

// New format-preserving encryption method
string Playfair::prepareTextWithFormatting(string text)
{
    string result = "";
    string currentPair = "";

    for (char c : text)
    {
        if (isalnum(c))
        {
            currentPair += toupper(c);
            if (currentPair.length() == 2)
            {
                if (currentPair[0] == currentPair[1])
                {
                    result += currentPair[0];
                    result += (currentPair[0] == 'X') ? 'Q' : 'X';
                    currentPair = string(1, currentPair[1]);
                }
                else
                {
                    result += currentPair;
                    currentPair = "";
                }
            }
        }
        else
        {
            // Handle incomplete pair before non-alphanumeric character
            if (currentPair.length() == 1)
            {
                result += currentPair + ((currentPair[0] == 'X') ? "Q" : "X");
                currentPair = "";
            }
            result += c; // Preserve non-alphanumeric characters
        }
    }

    // Handle final incomplete pair
    if (currentPair.length() == 1)
    {
        result += currentPair + ((currentPair[0] == 'X') ? "Q" : "X");
    }

    return result;
}

string Playfair::encryptWithFormatting(string text)
{
    string result = "";
    string buffer = "";

    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];
        if (isalnum(c))
        {
            buffer += toupper(c);
            if (buffer.length() == 2)
            {
                // Check if both characters are the same
                if (buffer[0] == buffer[1])
                {
                    // Encrypt first char with 'X', keep second for next pair
                    string pair = string(1, buffer[0]) + ((buffer[0] == 'X') ? 'Q' : 'X');
                    string encrypted = encrypt(pair);
                    result += encrypted.substr(0, 2);
                    buffer = string(1, buffer[1]); // Keep second char for next pair
                }
                else
                {
                    string encrypted = encrypt(buffer);
                    result += encrypted;
                    buffer = "";
                }
            }
        }
        else
        {
            // Handle incomplete pair before non-alphanumeric character
            if (buffer.length() == 1)
            {
                string pair = buffer + ((buffer[0] == 'X') ? 'Q' : 'X');
                string encrypted = encrypt(pair);
                result += encrypted.substr(0, 2);
                buffer = "";
            }
            result += c; // Preserve formatting characters
        }
    }

    // Handle final incomplete pair
    if (buffer.length() == 1)
    {
        string pair = buffer + ((buffer[0] == 'X') ? 'Q' : 'X');
        string encrypted = encrypt(pair);
        result += encrypted.substr(0, 2);
    }

    return result;
}

string Playfair::decryptWithFormatting(string text)
{
    string result = "";
    string buffer = "";

    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];
        if (isalnum(c))
        {
            buffer += toupper(c);
            if (buffer.length() == 2)
            {
                string decrypted = decrypt(buffer);
                result += decrypted;
                buffer = "";
            }
        }
        else
        {
            // Handle incomplete encrypted pair (shouldn't happen in proper encryption)
            if (buffer.length() == 1)
            {
                result += buffer; // Add as-is if incomplete
                buffer = "";
            }
            result += c; // Preserve formatting characters
        }
    }

    // Handle final incomplete pair
    if (buffer.length() == 1)
    {
        result += buffer;
    }

    return result;
}

void Playfair::encryptFilePreserveFormat(string inputFileName, string outputFileName)
{
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (inputFile.is_open() && outputFile.is_open())
    {
        string line, fullText = "";

        // Read the whole file
        while (getline(inputFile, line))
        {
            fullText += line + "\n";
        }

        // Remove the last extra newline
        if (!fullText.empty() && fullText.back() == '\n')
        {
            fullText.pop_back();
        }

        // Encrypt while preserving format
        string encrypted = encryptWithFormatting(fullText);

        // Save to output file
        outputFile << encrypted;

        inputFile.close();
        outputFile.close();
        cout << Color::GREEN << "[SUCCESS] File encrypted successfully with preserved formatting!" << Color::RESET << endl;
    }
    else
    {
        cout << Color::RED << "[ERROR] Could not open files for encryption." << Color::RESET << endl;
    }
}

// Keyword Management Functions
void Playfair::saveKeyword(string filename)
{
    ofstream keyFile(filename);
    if (keyFile.is_open())
    {
        keyFile << keyword;
        keyFile.close();
        cout << Color::GREEN << "[SUCCESS] Keyword saved to " << Color::YELLOW << filename << Color::GREEN << " successfully!" << Color::RESET << endl;

        // Automatically encrypt the keyword file for security
        encryptKeywordFile(filename);
    }
    else
    {
        cout << Color::RED << "[ERROR] Could not save keyword to file." << Color::RESET << endl;
    }
}

bool Playfair::loadKeyword(string filename)
{
    // First try to decrypt the keyword file
    string tempFile = "temp_" + filename;
    decryptKeywordFile(filename);

    ifstream keyFile(tempFile);
    if (keyFile.is_open())
    {
        string loadedKey;
        getline(keyFile, loadedKey);
        keyFile.close();

        // Remove temporary file
        remove(tempFile.c_str());

        if (!loadedKey.empty())
        {
            keyword = loadedKey;
            buildMatrix(); // Rebuild matrix with new keyword
            cout << Color::GREEN << "[SUCCESS] Keyword loaded successfully from " << Color::YELLOW << filename << Color::RESET << endl;
            return true;
        }
    }

    cout << Color::RED << "[ERROR] Could not load keyword from file." << Color::RESET << endl;
    return false;
}

void Playfair::decryptKeywordFile(string filename)
{
    if (!fileExists(filename))
    {
        return;
    }

    // Create a temporary cipher with master key
    Playfair masterCipher(masterKey);

    string tempFile = "temp_" + filename;
    masterCipher.decryptFilePreserveFormat(filename, tempFile);
}

void Playfair::encryptKeywordFile(string filename)
{
    // Create a temporary cipher with master key
    Playfair masterCipher(masterKey);

    string tempFile = "temp_" + filename;
    masterCipher.encryptFilePreserveFormat(filename, tempFile);

    // Replace original with encrypted version
    remove(filename.c_str());
    rename(tempFile.c_str(), filename.c_str());

    cout << Color::CYAN << "[INFO] Keyword file encrypted with master key for security." << Color::RESET << endl;
}

void Playfair::decryptFilePreserveFormat(string inputFileName, string outputFileName)
{
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (inputFile.is_open() && outputFile.is_open())
    {
        string line, fullText = "";

        // Read the whole file
        while (getline(inputFile, line))
        {
            fullText += line + "\n";
        }

        // Remove the last extra newline
        if (!fullText.empty() && fullText.back() == '\n')
        {
            fullText.pop_back();
        }

        // Decrypt while preserving format
        string decrypted = decryptWithFormatting(fullText);

        // Save to output file
        outputFile << decrypted;

        inputFile.close();
        outputFile.close();
        cout << Color::GREEN << "[SUCCESS] File decrypted successfully with preserved formatting!" << Color::RESET << endl;
    }
    else
    {
        cout << Color::RED << "[ERROR] Could not open files for decryption." << Color::RESET << endl;
    }
}

// Utility Functions
bool Playfair::fileExists(string filename)
{
    ifstream file(filename);
    return file.good();
}

void Playfair::displayMenu()
{
    cout << Color::BOLD << Color::BRIGHT_CYAN;
    cout << "\n"
         << "===============================================" << endl;
    cout << "       PLAYFAIR CIPHER SYSTEM          " << endl;
    cout << "===============================================" << Color::RESET << endl;
    cout << Color::GREEN << " 1." << Color::WHITE << "  Encrypt Text (Manual Input)" << Color::RESET << endl;
    cout << Color::GREEN << " 2." << Color::WHITE << "  Decrypt Text (Manual Input)" << Color::RESET << endl;
    cout << Color::GREEN << " 3." << Color::WHITE << "  Encrypt File (Preserve Format)" << Color::RESET << endl;
    cout << Color::GREEN << " 4." << Color::WHITE << "  Decrypt File (Preserve Format)" << Color::RESET << endl;
    cout << Color::GREEN << " 5." << Color::WHITE << "  Save Current Keyword" << Color::RESET << endl;
    cout << Color::GREEN << " 6." << Color::WHITE << "  Load Keyword from File" << Color::RESET << endl;
    cout << Color::GREEN << " 7." << Color::WHITE << "  Change Master Key" << Color::RESET << endl;
    cout << Color::GREEN << " 8." << Color::WHITE << "  Display Cipher Matrix" << Color::RESET << endl;
    cout << Color::GREEN << " 9." << Color::WHITE << "  Analyze Text Statistics" << Color::RESET << endl;
    cout << Color::GREEN << "10." << Color::WHITE << "  Show File Information" << Color::RESET << endl;
    cout << Color::GREEN << "11." << Color::WHITE << "  Create Test Files" << Color::RESET << endl;
    cout << Color::RED << " 0." << Color::WHITE << "  Exit Program" << Color::RESET << endl;
    cout << Color::CYAN << "-----------------------------------------------" << Color::RESET << endl;
    cout << Color::MAGENTA << "Current Keyword: " << Color::BOLD << Color::YELLOW << keyword << Color::RESET << endl;
    cout << Color::YELLOW << "Enter your choice: " << Color::RESET;
}

void Playfair::analyzeText(string text)
{
    cout << Color::BRIGHT_CYAN << "\n"
         << "========================" << endl;
    cout << "    TEXT ANALYSIS    " << endl;
    cout << "========================" << Color::RESET << endl;
    cout << Color::CYAN << "Total characters: " << Color::BOLD << Color::WHITE << text.length() << Color::RESET << endl;

    int alphanumeric = 0, uppercase = 0, lowercase = 0, digits = 0, special = 0;

    for (char c : text)
    {
        if (isalnum(c))
        {
            alphanumeric++;
            if (isupper(c))
                uppercase++;
            else if (islower(c))
                lowercase++;
            else if (isdigit(c))
                digits++;
        }
        else
        {
            special++;
        }
    }

    cout << Color::BLUE << "Alphanumeric characters: " << Color::BOLD << Color::WHITE << alphanumeric << Color::RESET << endl;
    cout << Color::GREEN << "Uppercase letters: " << Color::BOLD << Color::WHITE << uppercase << Color::RESET << endl;
    cout << Color::YELLOW << "Lowercase letters: " << Color::BOLD << Color::WHITE << lowercase << Color::RESET << endl;
    cout << Color::MAGENTA << "Digits: " << Color::BOLD << Color::WHITE << digits << Color::RESET << endl;
    cout << Color::RED << "Special characters: " << Color::BOLD << Color::WHITE << special << Color::RESET << endl;
    cout << Color::CYAN << "Lines: " << Color::BOLD << Color::WHITE << count(text.begin(), text.end(), '\n') + 1 << Color::RESET << endl;
}

void Playfair::showFileInfo(string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string content, line;
        while (getline(file, line))
        {
            content += line + "\n";
        }
        file.close();

        cout << Color::BRIGHT_CYAN << "\n"
             << "==========================" << endl;
        cout << "    FILE INFORMATION    " << endl;
        cout << "==========================" << Color::RESET << endl;
        cout << Color::YELLOW << "File: " << Color::BOLD << Color::WHITE << filename << Color::RESET << endl;
        analyzeText(content);
    }
    else
    {
        cout << Color::RED << "[ERROR] Could not open file " << Color::YELLOW << filename << Color::RESET << endl;
    }
}

// Original display cipher function
void Playfair::displayCipher()
{
    cout << Color::BRIGHT_CYAN << "\n"
         << "========================" << endl;
    cout << "    CIPHER MATRIX    " << endl;
    cout << "========================" << Color::RESET << endl;
    cout << Color::MAGENTA << "Keyword: " << Color::BOLD << Color::YELLOW << keyword << Color::RESET << endl;
    cout << Color::CYAN << "\nMatrix Layout:" << Color::RESET << endl;
    cout << Color::BRIGHT_BLUE << "   ";
    for (int j = 0; j < 6; j++)
    {
        cout << "\t" << "[" << j << "] ";
    }
    cout << Color::RESET << endl;

    for (int i = 0; i < 6; i++)
    {
        cout << Color::BRIGHT_BLUE << "[" << i << "]" << Color::RESET << " ";
        for (int j = 0; j < 6; j++)
        {
            cout << Color::BOLD << Color::GREEN << "\t" << cipher[i][j] << Color::RESET << "  ";
        }
        cout << endl;
    }
    cout << Color::CYAN << "--------------------------------" << Color::RESET << endl;
}

Playfair::~Playfair() {}
