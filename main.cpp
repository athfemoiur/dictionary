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

void addWordOrSynonym(Word *&, Word *);

Word *checkWordExist(Word *, const string &);

void mainAddWOrd(Word *&);

void deleteWord(Word *&, const string &);

void mainDeleteWord(Word *&);

void printAll(Word *);

void deleteAllSynonyms(Word *synHead);

Word *HEAD = nullptr;

int main() {
    for (int i = 0; i < 2; ++i) {
        mainAddWOrd(HEAD);
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

void addWordOrSynonym(Word *&node, Word *synonym) {
    if (node == nullptr) {
        node = synonym;
        return;
    }
    Word *prev = nullptr;
    Word *current = node;

    while (current) {
        if (synonym->value < current->value) {
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

Word *checkWordExist(Word *head, const string &word) {
    while (head) {
        if (head->value == word)
            return head;
        head = head->next;
    }
    return nullptr;
}

void mainAddWOrd(Word *&head) {
    cout << "Enter the word you want to add :";
    string word;
    cin >> word;
    int n;
    cout << "Enter the number of synonyms :";
    cin >> n;
    Word *tempNode = checkWordExist(head, word);
    if (tempNode) {
        for (int i = 0; i < n; ++i) {
            string tempWord;
            cin >> tempWord;
            addWordOrSynonym(tempNode->syn, createWord(tempWord));
        }
    } else {
        tempNode = createWord(word);
        for (int i = 0; i < n; ++i) {
            string tempWord;
            cin >> tempWord;
            addWordOrSynonym(tempNode->syn, createWord(tempWord));
        }
        addWordOrSynonym(head, tempNode);
    }
}

void deleteWord(Word *&head, const string &word) {
    Word *prev = nullptr;
    Word *current = head;
    if (head == nullptr) {
        cout << "The dictionary is empty!";
        return;
    } else {
        while (current) {
            if (word == current->value) {
                if (current == head && current->next == nullptr)
                    head = nullptr;
                else if (current == head)
                    head = head->next;
                else
                    prev->next = current->next;

                deleteAllSynonyms(current->syn);
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
}

void printAll(Word *head) {
    while (head) {
        cout << head->value << " : ";
        while (head->syn) {
            cout << head->syn->value << " ";
            head->syn = head->syn->next;
        }
        head = head->next;
        cout << endl;
    }
}

void deleteAllSynonyms(Word *synHead) {
    Word *temp;
    while (synHead) {
        temp = synHead;
        synHead = synHead->next;
        delete temp;
    }
}

void mainDeleteWord(Word *&head) {
    string word;
    cout << "Enter the word you want to delete from the dictionary :";
    deleteWord(head, word);
}
