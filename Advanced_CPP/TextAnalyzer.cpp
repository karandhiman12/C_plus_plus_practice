#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iomanip>

class TextAnalyzer {
private:
    std::string text;
    std::map<std::string, int> wordFrequency;
    int totalWords;
    int totalSentences;
    int totalSyllables;
    
    // Helper functions
    std::string toLowerCase(const std::string& word);
    std::string cleanWord(const std::string& word);
    int countSyllables(const std::string& word);
    bool isVowel(char c);
    void processText();
    
public:
    TextAnalyzer();
    bool loadFromFile(const std::string& filename);
    void loadFromString(const std::string& inputText);
    
    // Analysis functions
    void analyzeWordFrequency();
    void displayWordFrequency(int topN = 10);
    void displayBasicStats();
    double calculateReadingLevel();
    void findMostCommonWords(int count = 5);
    void findLeastCommonWords(int count = 5);
    void exportResults(const std::string& filename);
};

// Constructor
TextAnalyzer::TextAnalyzer() : totalWords(0), totalSentences(0), totalSyllables(0) {}

// Load text from file
bool TextAnalyzer::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    
    std::string line;
    text.clear();
    while (std::getline(file, line)) {
        text += line + " ";
    }
    file.close();
    
    processText();
    return true;
}

// Load text from string
void TextAnalyzer::loadFromString(const std::string& inputText) {
    text = inputText;
    processText();
}

// Convert string to lowercase
std::string TextAnalyzer::toLowerCase(const std::string& word) {
    std::string result = word;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Remove punctuation and clean word
std::string TextAnalyzer::cleanWord(const std::string& word) {
    std::string cleaned;
    for (char c : word) {
        if (std::isalnum(c)) {
            cleaned += c;
        }
    }
    return toLowerCase(cleaned);
}

// Count syllables in a word (simplified algorithm)
int TextAnalyzer::countSyllables(const std::string& word) {
    if (word.empty()) return 0;
    
    int syllables = 0;
    bool prevWasVowel = false;
    
    for (size_t i = 0; i < word.length(); i++) {
        bool currentIsVowel = isVowel(word[i]);
        if (currentIsVowel && !prevWasVowel) {
            syllables++;
        }
        prevWasVowel = currentIsVowel;
    }
    
    // Handle silent 'e'
    if (word.length() > 1 && word.back() == 'e' && !isVowel(word[word.length()-2])) {
        syllables--;
    }
    
    return std::max(1, syllables); // Every word has at least 1 syllable
}

bool TextAnalyzer::isVowel(char c) {
    char lower = std::tolower(c);
    return (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u');
}

// Process the loaded text
void TextAnalyzer::processText() {
    wordFrequency.clear();
    totalWords = 0;
    totalSentences = 0;
    totalSyllables = 0;
    
    std::istringstream iss(text);
    std::string word;
    
    while (iss >> word) {
        // Count sentences (simplified - look for .!?)
        for (char c : word) {
            if (c == '.' || c == '!' || c == '?') {
                totalSentences++;
            }
        }
        
        std::string cleanedWord = cleanWord(word);
        if (!cleanedWord.empty()) {
            wordFrequency[cleanedWord]++;
            totalWords++;
            totalSyllables += countSyllables(cleanedWord);
        }
    }
    
    if (totalSentences == 0) totalSentences = 1; // Avoid division by zero
}

// Display basic statistics
void TextAnalyzer::displayBasicStats() {
    std::cout << "\n=== TEXT ANALYSIS RESULTS ===\n";
    std::cout << "Total Words: " << totalWords << std::endl;
    std::cout << "Total Sentences: " << totalSentences << std::endl;
    std::cout << "Total Syllables: " << totalSyllables << std::endl;
    std::cout << "Unique Words: " << wordFrequency.size() << std::endl;
    std::cout << "Average Words per Sentence: " << std::fixed << std::setprecision(2) 
              << (double)totalWords / totalSentences << std::endl;
    std::cout << "Average Syllables per Word: " << std::fixed << std::setprecision(2)
              << (double)totalSyllables / totalWords << std::endl;
}

// Calculate Flesch-Kincaid Reading Level
double TextAnalyzer::calculateReadingLevel() {
    if (totalWords == 0 || totalSentences == 0) return 0.0;
    
    double avgWordsPerSentence = (double)totalWords / totalSentences;
    double avgSyllablesPerWord = (double)totalSyllables / totalWords;
    
    // Flesch-Kincaid Grade Level formula
    double readingLevel = 0.39 * avgWordsPerSentence + 11.8 * avgSyllablesPerWord - 15.59;
    
    std::cout << "Reading Level (Flesch-Kincaid): " << std::fixed << std::setprecision(1) 
              << readingLevel << " (Grade " << (int)readingLevel << ")" << std::endl;
    
    return readingLevel;
}

// Display word frequency
void TextAnalyzer::displayWordFrequency(int topN) {
    // Convert map to vector for sorting
    std::vector<std::pair<std::string, int>> wordVec(wordFrequency.begin(), wordFrequency.end());
    
    // Sort by frequency (descending)
    std::sort(wordVec.begin(), wordVec.end(), 
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::cout << "\n=== TOP " << topN << " WORD FREQUENCIES ===\n";
    for (int i = 0; i < std::min(topN, (int)wordVec.size()); i++) {
        std::cout << std::setw(15) << wordVec[i].first << ": " << wordVec[i].second << std::endl;
    }
}

// Find most common words
void TextAnalyzer::findMostCommonWords(int count) {
    std::vector<std::pair<std::string, int>> wordVec(wordFrequency.begin(), wordFrequency.end());
    std::sort(wordVec.begin(), wordVec.end(), 
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::cout << "\n=== " << count << " MOST COMMON WORDS ===\n";
    for (int i = 0; i < std::min(count, (int)wordVec.size()); i++) {
        std::cout << (i+1) << ". " << wordVec[i].first << " (" << wordVec[i].second << " times)\n";
    }
}

// Find least common words
void TextAnalyzer::findLeastCommonWords(int count) {
    std::vector<std::pair<std::string, int>> wordVec(wordFrequency.begin(), wordFrequency.end());
    std::sort(wordVec.begin(), wordVec.end(), 
              [](const auto& a, const auto& b) { return a.second < b.second; });
    
    std::cout << "\n=== " << count << " LEAST COMMON WORDS ===\n";
    for (int i = 0; i < std::min(count, (int)wordVec.size()); i++) {
        std::cout << (i+1) << ". " << wordVec[i].first << " (" << wordVec[i].second << " times)\n";
    }
}

// Export results to file
void TextAnalyzer::exportResults(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create output file " << filename << std::endl;
        return;
    }
    
    file << "TEXT ANALYSIS REPORT\n";
    file << "===================\n\n";
    file << "Total Words: " << totalWords << "\n";
    file << "Total Sentences: " << totalSentences << "\n";
    file << "Unique Words: " << wordFrequency.size() << "\n";
    file << "Reading Level: " << calculateReadingLevel() << "\n\n";
    
    file << "WORD FREQUENCY:\n";
    std::vector<std::pair<std::string, int>> wordVec(wordFrequency.begin(), wordFrequency.end());
    std::sort(wordVec.begin(), wordVec.end(), 
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    for (const auto& pair : wordVec) {
        file << pair.first << "," << pair.second << "\n";
    }
    
    file.close();
    std::cout << "Results exported to " << filename << std::endl;
}

// Main function with menu system
int main() {
    TextAnalyzer analyzer;
    std::string filename;
    int choice;
    
    std::cout << "=== TEXT ANALYZER ===\n";
    std::cout << "1. Load text from file\n";
    std::cout << "2. Enter text manually\n";
    std::cout << "Choice: ";
    std::cin >> choice;
    std::cin.ignore(); // Clear the newline
    
    if (choice == 1) {
        std::cout << "Enter filename: ";
        std::getline(std::cin, filename);
        if (!analyzer.loadFromFile(filename)) {
            return 1;
        }
    } else if (choice == 2) {
        std::cout << "Enter your text (end with a line containing only 'END'):\n";
        std::string text, line;
        while (std::getline(std::cin, line) && line != "END") {
            text += line + " ";
        }
        analyzer.loadFromString(text);
    } else {
        std::cout << "Invalid choice!\n";
        return 1;
    }
    
    // Analysis menu
    while (true) {
        std::cout << "\n=== ANALYSIS OPTIONS ===\n";
        std::cout << "1. Basic Statistics\n";
        std::cout << "2. Word Frequency (Top 10)\n";
        std::cout << "3. Most Common Words\n";
        std::cout << "4. Least Common Words\n";
        std::cout << "5. Reading Level\n";
        std::cout << "6. Export Results\n";
        std::cout << "7. Exit\n";
        std::cout << "Choice: ";
        
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                analyzer.displayBasicStats();
                break;
            case 2:
                analyzer.displayWordFrequency(10);
                break;
            case 3:
                analyzer.findMostCommonWords(5);
                break;
            case 4:
                analyzer.findLeastCommonWords(5);
                break;
            case 5:
                analyzer.calculateReadingLevel();
                break;
            case 6:
                std::cout << "Enter output filename: ";
                std::cin >> filename;
                analyzer.exportResults(filename);
                break;
            case 7:
                std::cout << "Thank you for using Text Analyzer!\n";
                return 0;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
    
    return 0;
}