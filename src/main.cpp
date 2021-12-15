#include <iostream>

#include "dictionary.hpp"

static int menu() {
    int choice = 0;
    std::cout << "====================[Dictionary menu]====================\n"
                 "\t1 - Add word\n"
                 "\t2 - Delete word\n"
                 "\t3 - None\n"
                 "\t4 - None\n"
                 "\t5 - Print dictionary\n"
                 "\t6 - None\n"
                 "=========================================================\n"
                 "\t7 - Exit\n"
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
    std::cout << ">> Please, enter word in russian transliterate:\n<< ";
    std::cin >> rus;
    dictionary.addWord(eng, rus);
}

static void deleteWordDialog(Dictionary &dictionary) {
    char eng[MAX_WORD_SIZE];
    std::cout << ">> Please, enter word in english:\n<< ";
    std::cin >> eng;
    dictionary.deleteWord(eng);
}

int main(int argc, char const *argv[]) {
    Dictionary dictionary;
    while (true) {
        switch (menu()) {
            case 1: addWordDialog(dictionary); break;
            case 2: deleteWordDialog(dictionary); break;
            case 3:
            case 4: break;
            case 5: std::cout << ">> Dictionary, words count = " << dictionary; break;
            case 6: break;
            case 7: return 0;
            default: std::cout << ">> Input must be in range [1, 7].\n";
        }
    }
    return 0;
}
