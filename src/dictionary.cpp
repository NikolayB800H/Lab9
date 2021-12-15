#include <fstream>
#include <cstring>

#include "dictionary.hpp"

void Dictionary::Word::swap(Word &other) {
    Word tmp = other;
    other = *this;
    *this = tmp;
}

void Dictionary::binSearch(const char *eng, int &back, int &front) const {
    back = -1;
    front = words_cnt;
    int mid = 0;
    while (front > back + 1) {
        mid = (back + front) / 2;
        int cmp = strcmp(eng, word_arr[mid].eng);
        if (cmp < 0) {
            front = mid;
        } else if (cmp > 0) {
            back = mid;
        } else {
            front = mid;
            back = mid;
        }
    }
    if (front == back) {
        return;
    }
    if (back != -1 && !strcmp(eng, word_arr[back].eng)) {
        front = back;
        return;
    }
    if (front != words_cnt && !strcmp(eng, word_arr[front].eng)) {
        back = front;
        return;
    }
}

void Dictionary::emplaceBack(const char *eng, const char *rus) {
    strncpy(word_arr[words_cnt].eng, eng, MAX_WORD_SIZE - 1);
    word_arr[words_cnt].eng[MAX_WORD_SIZE - 1] = 0;
    strncpy(word_arr[words_cnt].rus, rus, MAX_WORD_SIZE - 1);
    word_arr[words_cnt].rus[MAX_WORD_SIZE - 1] = 0;
    ++words_cnt;
}

Dictionary::Dictionary() : words_cnt(0) {
}

void Dictionary::addWord(const char *eng, const char *rus) {
    int back = 0;
    int front = 0;
    if (!words_cnt) {
        emplaceBack(eng, rus);
        return;
    }
    binSearch(eng, back, front);
    if (back == front) {
        return;
    }
    emplaceBack(eng, rus);
    for (int adding = words_cnt - 1; adding != front; --adding) {
        word_arr[adding].swap(word_arr[adding - 1]);
    }
}

void Dictionary::deleteWord(const char *eng) {
    int back = 0;
    int front = 0;
    if (!words_cnt) {
        return;
    }
    binSearch(eng, back, front);
    if (back != front) {
        return;
    }
    for (int deleting = front; deleting != words_cnt - 1; ++deleting) {
        word_arr[deleting].swap(word_arr[deleting + 1]);
    }
    --words_cnt;
}

const char *Dictionary::findRusByEng(const char *eng) const {
    int back = 0;
    int front = 0;
    if (!words_cnt) {
        return nullptr;
    }
    binSearch(eng, back, front);
    if (back != front) {
        return nullptr;
    }
    return word_arr[front].rus;
}

const char *Dictionary::findEngByRus(const char *rus) const {
    for (int finding = 0; finding != words_cnt; ++finding) {
        if (!strcmp(word_arr[finding].rus, rus)) {
            return word_arr[finding].eng;
        }
    }
    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const Dictionary &dictionary) {
    os << dictionary.words_cnt << '\n';
    for (int i = 0; i < dictionary.words_cnt; ++i) {
        os << '\t' << dictionary.word_arr[i].eng << ' ' << dictionary.word_arr[i].rus << '\n';
    }
    os.flush();
    return os;
}

std::istream &operator>>(std::istream &is, Dictionary &dictionary) {
    int add_cnt = 0;
    is >> add_cnt;
    char eng[MAX_WORD_SIZE];
    char rus[MAX_WORD_SIZE];
    for (int i = 0; i < add_cnt; ++i) {
        is >> eng;
        is >> rus;
        dictionary.addWord(eng, rus);
    }
    return is;
}
