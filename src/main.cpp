#include <fstream>
#include <iostream>

#include "dictionary.hpp"

static int menu() {
    int choice = 0;
    std::cout << "====================[Dictionary menu]====================\n"
                 "\t1 - Add word\n"
                 "\t2 - Delete word\n"
                 "\t3 - Translate from english\n"
                 "\t4 - Translate from russian\n"
                 "\t5 - Print dictionary\n"
                 "\t6 - Write dictionary to file\n"
                 "\t7 - Read words from file\n"
                 "=========================================================\n"
                 "\t8 - Exit\n"
                 "=========================================================\n"
                 ">> Your choice:\n<< ";
    std::cin >> choice;
    while (std::cin.fail()) {
        std::cout << ">> Input failed. Try again:\n<< ";
        std::cin.clear();
        std::cin.ignore(10, '\n');
        std::cin >> choice;
    }
    return choice;
}

static void addWordDialog(Dictionary &dictionary) {
    char eng[MAX_WORD_SIZE];
    char rus[MAX_WORD_SIZE];
    std::cout << ">> Please, enter word in english:\n<< ";
    std::cin >> eng;
    std::cout << ">> Please, enter word in russian:\n<< ";
    std::cin >> rus;
    dictionary.addWord(eng, rus);
}

static void deleteWordDialog(Dictionary &dictionary) {
    char eng[MAX_WORD_SIZE];
    std::cout << ">> Please, enter word in english:\n<< ";
    std::cin >> eng;
    dictionary.deleteWord(eng);
}

static void findRusByEngDialog(Dictionary &dictionary) {
    char eng[MAX_WORD_SIZE];
    std::cout << ">> Please, enter word in english:\n<< ";
    std::cin >> eng;
    const char *res = dictionary.findRusByEng(eng);
    if (!res) {
        std::cout << ">> No such word.\n";
        return;
    }
    std::cout << ">> In russian: " << res << std::endl;
}

static void findEngByRusDialog(Dictionary &dictionary) {
    char rus[MAX_WORD_SIZE];
    std::cout << ">> Please, enter word in russian:\n<< ";
    std::cin >> rus;
    const char *res = dictionary.findEngByRus(rus);
    if (!res) {
        std::cout << ">> No such word.\n";
        return;
    }
    std::cout << ">> In english: " << res << std::endl;
}

static void toFileWordsDialog(Dictionary &dictionary) {
    char file_to[MAX_WORD_SIZE];
    std::cout << ">> Please, enter file name:\n<< ";
    std::cin >> file_to;
    std::ofstream os(file_to);
    os << dictionary;
    os.close();
}

static void fromFileWordsDialog(Dictionary &dictionary) {
    char file_from[MAX_WORD_SIZE];
    std::cout << ">> Please, enter file name:\n<< ";
    std::cin >> file_from;
    std::ifstream is(file_from);
    is >> dictionary;
    is.close();
}

int main(int argc, char const *argv[]) {
    Dictionary dictionary;
    while (true) {
        switch (menu()) {
            case 1: addWordDialog(dictionary); break;
            case 2: deleteWordDialog(dictionary); break;
            case 3: findRusByEngDialog(dictionary); break;
            case 4: findEngByRusDialog(dictionary); break;
            case 5: std::cout << ">> Dictionary, words count = " << dictionary; break;
            case 6: toFileWordsDialog(dictionary); break;
            case 7: fromFileWordsDialog(dictionary); break;
            case 8: return 0;
            default: std::cout << ">> Input must be in range [1, 7].\n";
        }
    }
    return 0;
}
