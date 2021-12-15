#pragma ONCE

constexpr size_t MAX_WORDS_CNT = 100;
constexpr size_t MAX_WORD_SIZE = 31;

class Dictionary {
    struct Word {
        char eng[MAX_WORD_SIZE];
        char rus[MAX_WORD_SIZE];

        void swap(Word &other);
    };

    int words_cnt;
    Word word_arr[MAX_WORDS_CNT];

    void binSearch(const char *eng, int &back, int &front) const;
    void emplaceBack(const char *eng, const char *rus);

public:
    Dictionary();
    void addWord(const char *eng, const char *rus);
    void deleteWord(const char *eng);
    const char *findRusByEng(const char *eng) const;
    const char *findEngByRus(const char *rus) const;
    friend
    std::ostream &operator<<(std::ostream &os, const Dictionary &dictionary);
    friend
    std::istream &operator>>(std::istream &is, Dictionary &dictionary);
};

std::ostream &operator<<(std::ostream &os, const Dictionary &dictionary);
std::istream &operator>>(std::istream &is, const Dictionary &dictionary);
