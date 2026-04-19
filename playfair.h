#ifndef PLAYFAIR_H
#define PLAYFAIR_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

class Playfair
{
private:
    char cipher[6][6];
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string keyword;
    string masterKey = "SECURITY2024";

    void buildMatrix();
    void findPosition(char c, int &row, int &col);
    string prepareText(string plaintext);
    string prepareTextWithFormatting(string text);
    string encryptWithFormatting(string text);    
    string decryptWithFormatting(string text);    

public:
    Playfair(string key);
    ~Playfair();

    // Core functionality
    void displayCipher();
    string encrypt(string plaintext);
    string decrypt(string encryptedText);

    // Enhanced file operations
    void encryptFile(string inputFileName, string outputFileName);
    void decryptFile(string inputFileName, string outputFileName);
    void encryptFilePreserveFormat(string inputFileName, string outputFileName);
    void decryptFilePreserveFormat(string inputFileName, string outputFileName);

    // Keyword management
    void saveKeyword(string filename);
    bool loadKeyword(string filename);
    void encryptKeywordFile(string filename);
    void decryptKeywordFile(string filename);

    // Utility functions
    bool fileExists(string filename);
    void displayMenu();
    string getKeyword() const { return keyword; }
    void setMasterKey(string newMasterKey) { masterKey = newMasterKey; }

    // Statistics and analysis
    void analyzeText(string text);
    void showFileInfo(string filename);
};

#endif