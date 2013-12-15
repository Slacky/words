/**
 * @author Zach Knight
 * 
 * @comment License in main folder.
 */

#include <algorithm>
#include <iostream>

class Dictionary {
private:
    std::string *words;
public:
    Dictionary(int);
    ~Dictionary();
    std::string *getWords();
    void setWords(std::string*);
};

Dictionary::Dictionary(int count) {
    this->words = new std::string[count]();
}

Dictionary::~Dictionary() {
    delete[] words;
}

std::string *Dictionary::getWords() {
    return this->words;
}

unsigned int getDistance(const std::string &s1, const std::string & s2) {
    const size_t len1 = s1.size(), len2 = s2.size();
    int *col = new int[len2+1];
    int *prevCol = new int[len2+1];

    for (unsigned int i = 0; i < len2 + 1; i++)
        prevCol[i] = i;
    for (unsigned int i = 0; i < len1; i++) {
        col[0] = i+1;
        for (unsigned int j = 0; j < len2; j++)
            col[j+1] = std::min(std::min(1 + col[j], 1 + prevCol[1 + j]), prevCol[j] + (s1[i]==s2[j] ? 0 : 1));
        std::swap(col, prevCol);
    }

    return prevCol[len2];
}

int main(void) {
    int i;
    std::cout << "How many words will be in the dictionary?" << std::endl;
    std::cin >> i;

    Dictionary dictionary(i + 1);

    std::cout << "Enter " << i << " words to use:" << std::endl;
    for(int j = 0; j < i; j++)
        std::cin >> dictionary.getWords()[j];

    std::string line;
    for(int j = 0; j < i; j++) {
        int count = 0;
        for(int j1 = 0; j1 < i; j1++)
            if(getDistance(dictionary.getWords()[j], dictionary.getWords()[j1]) < 2 && dictionary.getWords()[j].compare(dictionary.getWords()[j1]) != 0) {
                std::cout << dictionary.getWords()[j] << "->" << dictionary.getWords()[j1] << " ";
                count++;
            }
        if(count)
            std::cout << std::endl;
    }

    return 0;
}
