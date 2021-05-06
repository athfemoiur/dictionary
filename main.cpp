#include <iostream>
#include <string>
#include <fstream>

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

void deleteSyn(Word *&, const string &);

void mainDeleteSyn(Word *&);

void printAll(Word *);

void showOneWord(Word *);

void deleteAllSynonyms(Word *);

void changeWord(Word *&);

void writeOnFile(Word *);

void addFromFile(Word *&);


int main() {
    Word *HEAD = nullptr;
    bool rerun = true;
    while (rerun) {
        rerun = true;
        cout << "##########################################################\n";
        cout << "1 : add word and synonym\n2: delete word\n3 : delete synonym\n4 : find word\n5 : show all words\n"
                "6 : change dictation\n7 : save on file\n8 : load from file\n9 : exit\n";
        int command;
        cin >> command;
        switch (command) {
            case 1:
                mainAddWOrd(HEAD);
                break;
            case 2:
                mainDeleteWord(HEAD);
                break;
            case 3:
                mainDeleteSyn(HEAD);
                break;
            case 4:
                showOneWord(HEAD);
                break;
            case 5:
                printAll(HEAD);
                break;
            case 6:
                changeWord(HEAD);
                break;
            case 7:
                writeOnFile(HEAD);
                break;
            case 8:
                addFromFile(HEAD);
                break;
            case 9:
                char ans;
                cout << "do you want to save ?(y/n)";
                cin >> ans;
                if (ans == 'y')
                    writeOnFile(HEAD);
                rerun = false;
                break;
            default:
                cout << "invalid input\n";
        }
    }
    cout << "Thanks for using this app :)";
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
    if (n==0)
        return;
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
    deleteSyn(wordNode->syn, syn);
    if (!wordNode->syn)
        deleteWord(head, word, false);
}

void deleteSyn(Word *&synHead, const string &syn) {

    Word *prev = nullptr;
    Word *current = synHead;
    if (synHead == nullptr) {
        return;
    } else {
        while (current) {
            if (syn == current->value) {
                if (current == synHead && current->next == nullptr)
                    synHead = nullptr;
                else if (current == synHead)
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
    cout << endl;
}

void changeWord(Word *&head) {
    string word;
    cout << "Enter the word you want to change :";
    cin >> word;
    Word *temp = checkWordExist(head, word);
    cout << "Enter the new word :";
    cin >> word;
    Word *new_word = createWord(word);
    new_word->syn = temp->syn;
    deleteWord(head, temp->value, false);
    addWordOrSynonym(head, new_word);
}

void writeOnFile(Word *head) {
    fstream f("data.txt", ios::out);
    while (head) {
        string temp;
        temp += head->value;
        Word *headSyn = head->syn;
        while (headSyn) {
            temp += " ";
            temp += headSyn->value;
            headSyn = headSyn->next;
        }
        head = head->next;
        f << temp << endl;
    }
    f.close();
}

void addFromFile(Word *&head) {
    string filePath;
    cout<<"Enter the file name :";
    cin>>filePath;
    fstream f(filePath, ios::in);
    string temp;
    while (getline(f, temp)) {
        Word *wordNode;
        int i, start = 0;
        for (i = 0; i < temp.length(); ++i) {
            if (temp[i] == ' ') {
                string word = temp.substr(start, i - start);
                if (start == 0) {
                    wordNode = createWord(word);
                } else
                    addWordOrSynonym(wordNode->syn, createWord(word));
                start = i + 1;
            }
        }
        addWordOrSynonym(wordNode->syn, createWord(temp.substr(start, i - start + 1)));
        addWordOrSynonym(head, wordNode);
    }
    f.close();
}
