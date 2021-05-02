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

void deleteWord(Word *&, const string &, bool);

void mainDeleteWord(Word *&);

void deleteSyn(Word *&, Word *&, const string &, const string &);

void mainDeleteSyn(Word *&);

void printAll(Word *);

void showOneWord(Word *);

void deleteAllSynonyms(Word *);


int main() {
    Word *HEAD = nullptr;
    for (int i = 0; i < 3; ++i) {
        mainAddWOrd(HEAD);
    }
    showOneWord(HEAD);
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

void deleteWord(Word *&head, const string &word, bool deleteSyn) {
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
                if (deleteSyn)
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
        Word *synHead = head->syn;
        while (synHead) {
            cout << synHead->value << " ";
            synHead = synHead->next;
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
    cin >> word;
    deleteWord(head, word, true);
}

void mainDeleteSyn(Word *&head) {
    string word;
    string syn;
    cout << "Enter the word you want to delete its synonym from the dictionary :";
    cin >> word;
    cout << "Enter the synonym you want to delete :";
    cin >> syn;
    Word *wordNode = checkWordExist(head, word);
    Word *synHead = wordNode->syn;
    deleteSyn(head, synHead, syn, word);
    if (!synHead)
        deleteWord(head, word, false);
}

void deleteSyn(Word *&head, Word *&synHead, const string &syn, const string &word) {

    Word *prev = nullptr;
    Word *current = synHead;
    if (synHead == nullptr) {
        cout << "This word has no synonyms!";
        return;
    } else {
        while (current) {
            if (syn == current->value) {
                if (current == synHead && current->next == nullptr) {
                    synHead = nullptr;
                } else if (current == synHead)
                    synHead = synHead->next;
                else
                    prev->next = current->next;

                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

}

void showOneWord(Word *head) {
    string word;
    cout << "Enter the word you want to find :";
    cin >> word;
    Word *temp = checkWordExist(head, word);
    cout << temp->value << " : ";
    while (temp->syn) {
        cout << temp->syn->value << " ";
        temp->syn = temp->syn->next;
    }
}
