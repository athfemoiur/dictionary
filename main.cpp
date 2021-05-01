#include <iostream>
#include <string>

using namespace std;

struct Word {
    string value;
    Word *next;
    Word *syn;
};

Word *createWord(string);

void toLower(string &);

void addSynonym(Word *&node, Word *synonym);


int main() {
    string s1 = "glad";
    string s2 = "happy";
    string s3 = "fine";
    string s4 = "good";
    Word *temp = createWord(s1);
    addSynonym(temp->syn, createWord(s2));
    addSynonym(temp->syn, createWord(s3));
    addSynonym(temp->syn, createWord(s4));
    while (temp->syn) {
        cout << temp->syn->value << " ";
        temp->syn = temp->syn->next;
    }


}

Word *createWord(string word) {
    toLower(word);
    Word *temp = new Word{std::move(word), nullptr, nullptr};
    return temp;
}

void toLower(string &s) {
    for (char &i : s) {
        if (i >= 65 && i <= 90)
            i += 32;
    }
}

void addSynonym(Word *&node, Word *synonym) {
    if (node == nullptr) {
        node = synonym;
        return;
    }
    Word *prev = nullptr;
    Word *current = node;

    while (current) {
        if (synonym->value.compare(current->value) == -1) {
            if (current == node) {
                synonym->next = current;
                node = synonym;
            } else {
                synonym->next = current;
                prev->next = synonym;
            }
            return;
        }
        prev = current;
        current = current->next;
    }
    prev->next = synonym;
    synonym->next = nullptr;
}




