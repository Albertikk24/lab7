/********************************************************
 * Автор:     Иккерт А.С.                               *
 * Название:  Частота повторений                        *
 * Вариант:   7                                         *
 ********************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <cctype>

using namespace std;

// Функция для приведения символа к нижнему регистру
char toLower(char character) {
    return tolower(character);
}

// Функция для проверки, является ли символ буквой
bool isAlpha(char character) {
    return isalpha(static_cast<unsigned char>(character));
}

int main() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string fullText;
    string currentLine;
    
    // Чтение всего файла
    while (getline(inputFile, currentLine)) {
        fullText += currentLine + " ";
    }
    inputFile.close();

    // Статистика для отдельных букв
    map<char, int> letterFrequency;
    int totalLetterCount = 0;

    // Статистика для двухбуквенных сочетаний
    map<string, int> bigramFrequency;
    int totalBigramCount = 0;

    // Обработка текста
    for (size_t textIndex = 0; textIndex < fullText.length(); ++textIndex) {
        char currentCharacter = toLower(fullText[textIndex]);
        
        // Подсчет отдельных букв
        if (isAlpha(currentCharacter)) {
            ++letterFrequency[currentCharacter];
            ++totalLetterCount;
        }

        // Подсчет двухбуквенных сочетаний
        if (textIndex < fullText.length() - 1) {
            char nextCharacter = toLower(fullText[textIndex + 1]);
            if (isAlpha(currentCharacter) && isAlpha(nextCharacter)) {
                string currentBigram = string(1, currentCharacter) + nextCharacter;
                ++bigramFrequency[currentBigram];
                ++totalBigramCount;
            }
        }
    }

    // Вывод статистики для отдельных букв
    cout << "\n=== LETTER FREQUENCY ===" << endl << "Total letters: " << totalLetterCount << endl << "Letter\tCount\tFrequency" << endl << "------------------------" << endl;
    
    for (const auto& letterPair : letterFrequency) {
        double letterPercentage = static_cast<double>(letterPair.second) / totalLetterCount * 100;
        cout << letterPair.first << "\t" << letterPair.second << "\t" 
             << fixed << setprecision(2) << letterPercentage << "%" << endl;
    }

    // Вывод статистики для двухбуквенных сочетаний
    cout << "\n=== BIGRAM FREQUENCY ===" << endl << "Total bigrams: " << totalBigramCount << endl << "Bigram\tCount\tFrequency" << endl << "------------------------" << endl;
    
    for (const auto& bigramPair : bigramFrequency) {
        double bigramPercentage = static_cast<double>(bigramPair.second) / totalBigramCount * 100;
        cout << bigramPair.first << "\t" << bigramPair.second << "\t" 
             << fixed << setprecision(2) << bigramPercentage << "%" << endl;
    }

    return 0;
}