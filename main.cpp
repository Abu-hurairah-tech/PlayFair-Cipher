#include "playfair.h"
#include "colors.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    cout << Color::RESET; // Reset any previous colors
}

void waitForEnter()
{
    cout << Color::DIM << "\nPress Enter to continue..." << Color::RESET;
    cin.get();
}

void createSampleFiles()
{
    // Create a sample message file for testing
    ofstream messageFile("message.txt");
    if (messageFile.is_open())
    {
        messageFile << "Hello World! This is a sample message for encryption.\n";
        messageFile << "It contains multiple lines to test formatting preservation.\n";
        messageFile << "Line 1: Numbers like 123 and 456\n";
        messageFile << "Line 2: Special characters: @#$%^&*()\n";
        messageFile << "Line 3: Mixed content: ABC123xyz!@#\n";
        messageFile << "\nEnd of sample message.";
        messageFile.close();
        cout << Color::GREEN << "[SUCCESS] Sample file 'message.txt' created successfully!" << Color::RESET << endl;
    }

    // Create a larger sample file for testing
    ofstream largeFile("large_sample.txt");
    if (largeFile.is_open())
    {
        largeFile << "========================================\n";
        largeFile << "         LARGE SAMPLE DOCUMENT\n";
        largeFile << "========================================\n\n";
        largeFile << "This is a larger sample document to test the cipher's ability\n";
        largeFile << "to handle longer texts with various formatting elements.\n\n";
        largeFile << "Chapter 1: Introduction\n";
        largeFile << "-----------------------\n";
        largeFile << "The Playfair cipher is a digraph substitution cipher.\n";
        largeFile << "It was invented by Charles Wheatstone, but is named after\n";
        largeFile << "Lord Playfair who promoted its use.\n\n";
        largeFile << "Technical Details:\n";
        largeFile << "- Uses a 5x5 grid (extended to 6x6 in our implementation)\n";
        largeFile << "- Operates on pairs of letters\n";
        largeFile << "- Includes numbers 0-9 in our version\n\n";
        largeFile << "Sample data: User123, Pass456, Code789\n";
        largeFile << "Email: user@example.com\n";
        largeFile << "Phone: +1-555-0123\n\n";
        largeFile << "End of document.";
        largeFile.close();
        cout << Color::GREEN << "[SUCCESS] Large sample file 'large_sample.txt' created successfully!" << Color::RESET << endl;
    }
}

bool validateChoice(int &choice)
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << Color::RED << "[ERROR] Invalid input! Please enter a number." << Color::RESET << endl;
        return false;
    }
    return true;
}


int main()
{
    clearScreen();
    cout << Color::BOLD << Color::BRIGHT_CYAN;
    cout << "===============================================" << endl;
    cout << "       " << Color::BRIGHT_MAGENTA << "PLAYFAIR CIPHER SYSTEM" << Color::BRIGHT_CYAN << "          " << endl;
    cout << "===============================================" << Color::RESET << endl;
    cout << Color::CYAN << "Enhanced with format preservation and keyword management" << Color::RESET << endl;

    string keyword;
    bool keywordLoaded = false;

    // Try to load existing keyword first
    cout << Color::YELLOW << "\n"
         << "Do you want to load a saved keyword? (y/n): " << Color::RESET;
    char loadChoice;
    cin >> loadChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (tolower(loadChoice) == 'y')
    {
        string keywordFile;
        cout << Color::YELLOW << "Enter keyword filename (default: 'keywords.txt'): " << Color::RESET;
        getline(cin, keywordFile);
        if (keywordFile.empty())
        {
            keywordFile = "keywords.txt";
        }

        // Create temporary cipher to test loading
        Playfair tempCipher("TEMP");
        if (tempCipher.loadKeyword(keywordFile))
        {
            keyword = tempCipher.getKeyword();
            keywordLoaded = true;
        }
    }

    if (!keywordLoaded)
    {
        cout << Color::YELLOW << "\n"
             << "Enter the keyword for cipher: " << Color::RESET;
        getline(cin, keyword);
        if (keyword.empty())
        {
            keyword = "PLAYFAIR";
            cout << Color::CYAN << "Using default keyword: " << Color::BOLD << keyword << Color::RESET << endl;
        }
    }

    Playfair pf(keyword);

    int choice;
    string inputText, outputText, inputFile, outputFile, filename;

    while (true)
    {
        clearScreen();
        pf.displayMenu();

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!validateChoice(choice))
        {
            waitForEnter();
            continue;
        }

        switch (choice)
        {
        case 1: // Encrypt Text
        {
            cout << Color::BRIGHT_CYAN << "\n"
                 << "========================" << endl;
            cout << "    ENCRYPT TEXT    " << endl;
            cout << "========================" << Color::RESET << endl;
            cout << Color::YELLOW << "Enter text to encrypt: " << Color::RESET;
            getline(cin, inputText);
            outputText = pf.encrypt(inputText);
            cout << Color::BLUE << "\n"
                 << "Original text: " << Color::WHITE << inputText << Color::RESET << endl;
            cout << Color::GREEN << "Encrypted text: " << Color::BOLD << outputText << Color::RESET << endl;

            cout << Color::YELLOW << "\n"
                 << "Save encrypted text to file? (y/n): " << Color::RESET;
            char saveChoice;
            cin >> saveChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (tolower(saveChoice) == 'y')
            {
                cout << Color::YELLOW << "Enter filename: " << Color::RESET;
                getline(cin, filename);
                ofstream outFile(filename);
                outFile << outputText;
                outFile.close();
                cout << Color::GREEN << "[SUCCESS] Encrypted text saved to " << filename << Color::RESET << endl;
            }
            break;
        }

        case 2: // Decrypt Text
        {
            cout << Color::BRIGHT_CYAN << "\n"
                 << "========================" << endl;
            cout << "    DECRYPT TEXT    " << endl;
            cout << "========================" << Color::RESET << endl;
            cout << Color::YELLOW << "Enter text to decrypt: " << Color::RESET;
            getline(cin, inputText);
            outputText = pf.decrypt(inputText);
            cout << Color::BLUE << "\n"
                 << "Encrypted text: " << Color::WHITE << inputText << Color::RESET << endl;
            cout << Color::GREEN << "Decrypted text: " << Color::BOLD << outputText << Color::RESET << endl;
            break;
        }

        case 3: // Encrypt File
        {
            cout << Color::BRIGHT_CYAN << "\n"
                 << "========================" << endl;
            cout << "    ENCRYPT FILE    " << endl;
            cout << "========================" << Color::RESET << endl;
            cout << Color::YELLOW << "Enter input filename: " << Color::RESET;
            getline(cin, inputFile);
            cout << Color::YELLOW << "Enter output filename: " << Color::RESET;
            getline(cin, outputFile);

            cout << Color::CYAN << "\n"
                 << "Analyzing input file..." << Color::RESET << endl;
            pf.showFileInfo(inputFile);

            pf.encryptFilePreserveFormat(inputFile, outputFile);

            cout << Color::CYAN << "\n"
                 << "Analyzing output file..." << Color::RESET << endl;
            pf.showFileInfo(outputFile);
            break;
        }

        case 4: // Decrypt File
        {
            cout << Color::BRIGHT_CYAN << "\n"
                 << "========================" << endl;
            cout << "    DECRYPT FILE    " << endl;
            cout << "========================" << Color::RESET << endl;
            cout << Color::YELLOW << "Enter input filename: " << Color::RESET;
            getline(cin, inputFile);
            cout << Color::YELLOW << "Enter output filename: " << Color::RESET;
            getline(cin, outputFile);

            cout << Color::CYAN << "\n"
                 << "Analyzing input file..." << Color::RESET << endl;
            pf.showFileInfo(inputFile);

            pf.decryptFilePreserveFormat(inputFile, outputFile);

            cout << Color::CYAN << "\n"
                 << "Analyzing output file..." << Color::RESET << endl;
            pf.showFileInfo(outputFile);
            break;
        }

        case 5: // Save Keyword
        {
            cout << Color::BRIGHT_CYAN << "\n"
                 << "========================" << endl;
            cout << "    SAVE KEYWORD    " << endl;
            cout << "========================" << Color::RESET << endl;
            cout << Color::YELLOW << "Enter filename to save keyword (default: 'keywords.txt'): " << Color::RESET;
            getline(cin, filename);
            if (filename.empty())
            {
                filename = "keywords.txt";
            }
            pf.saveKeyword(filename);
            break;
        }

        case 6: // Load Keyword
        {
            cout << Color::BRIGHT_CYAN << "\n"
                 << "========================" << endl;
            cout << "    LOAD KEYWORD    " << endl;
            cout << "========================" << Color::RESET << endl;
            cout << Color::YELLOW << "Enter filename to load keyword from: " << Color::RESET;
            getline(cin, filename);
            if (pf.loadKeyword(filename))
            {
                cout << Color::GREEN << "[SUCCESS] Keyword loaded and matrix rebuilt successfully!" << Color::RESET << endl;
            }
            break;
        }

        case 7: // Change Master Key
        {
            cout << Color::BRIGHT_CYAN << "\n"
                 << "============================" << endl;
            cout << "    CHANGE MASTER KEY    " << endl;
            cout << "============================" << Color::RESET << endl;
            cout << Color::YELLOW << "Enter new master key: " << Color::RESET;
            string newMasterKey;
            getline(cin, newMasterKey);
            pf.setMasterKey(newMasterKey);
            cout << Color::GREEN << "[SUCCESS] Master key updated successfully!" << Color::RESET << endl;
            break;
        }

        case 8: // Display Matrix
        {
            pf.displayCipher();
            break;
        }

        case 9: // Analyze Text
        {
            cout << Color::BRIGHT_CYAN << "\n"
                 << "========================" << endl;
            cout << "    TEXT ANALYSIS    " << endl;
            cout << "========================" << Color::RESET << endl;
            cout << Color::CYAN << "1. Analyze text from input" << endl;
            cout << "2. Analyze text from file" << Color::RESET << endl;
            cout << Color::YELLOW << "Enter choice: " << Color::RESET;
            int analyzeChoice;
            cin >> analyzeChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (analyzeChoice == 1)
            {
                cout << Color::YELLOW << "Enter text to analyze: " << Color::RESET;
                getline(cin, inputText);
                pf.analyzeText(inputText);
            }
            else if (analyzeChoice == 2)
            {
                cout << Color::YELLOW << "Enter filename: " << Color::RESET;
                getline(cin, filename);
                pf.showFileInfo(filename);
            }
            break;
        }

        case 10: // Show File Info
        {
            cout << Color::BRIGHT_CYAN << "\n"
                 << "==========================" << endl;
            cout << "    FILE INFORMATION    " << endl;
            cout << "==========================" << Color::RESET << endl;
            cout << Color::YELLOW << "Enter filename: " << Color::RESET;
            getline(cin, filename);
            pf.showFileInfo(filename);
            break;
        }

        case 11: // Create Test Files
        {
            cout << Color::BRIGHT_CYAN << "\n"
                 << "==========================" << endl;
            cout << "    CREATE TEST FILES   " << endl;
            cout << "==========================" << Color::RESET << endl;
            createSampleFiles();
            break;
        }

        case 0: // Exit
        {
            cout << Color::BRIGHT_MAGENTA << "\n"
                 << "========================" << endl;
            cout << "       GOODBYE       " << endl;
            cout << "========================" << Color::RESET << endl;
            cout << Color::GREEN << "Thank you for using Playfair Cipher System!" << Color::RESET << endl;
            cout << Color::CYAN << "Security reminder: Your keywords are encrypted for protection." << Color::RESET << endl;
            return 0;
        }

        default:
        {
            cout << Color::RED << "\n"
                 << "[ERROR] Invalid choice! Please select a number from 0-11." << Color::RESET << endl;
            break;
        }
        }

        waitForEnter();
    }

    return 0;
}
