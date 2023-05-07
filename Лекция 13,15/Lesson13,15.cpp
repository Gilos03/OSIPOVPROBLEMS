#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class Map {
    string word, translation;
    map<string, string> dictionary;
public:
    Map(ifstream & f) {
        string s;
        getline(f,s);
        int n = stoi(s);
        for(size_t i = 0; i < n; ++i) {
            getline(f,word);
            getline(f,translation);
            dictionary[word]=translation;
        }
    }
    ~Map() {
        dictionary.clear();
    }
    void write_dictionary() {
        map <string, string> :: iterator it = dictionary.begin();
        for (;it!=dictionary.end();++it)
        {
            cout << it->first << " " << it->second << '\n';
        }
        cout << endl;
    }
    void add_word(ifstream & f) {
        
        getline(f, word);
        getline(f,translation);
        dictionary.insert(pair<string,string>(word,translation));
    }
    void edit_translation(ifstream & f) {
        
        getline(f,word);
        getline(f,translation);
        map <string,string> :: iterator it;
        it = dictionary.find(word);
        it -> second = translation;

    }

    void find_word(ifstream & k) {
        getline(k,word);
        map <string,string> :: iterator it;
        it = dictionary.find(word);
        if (it != dictionary.end())
            cout << it -> first << " " << it -> second << '\n';
        else cout << "Такого слова нет" << '\n';
        cout << endl;
    }
    void delete_word(ifstream & v) {
        getline(v,word);
        map <string,string> :: iterator it;
        it = dictionary.find(word);
        dictionary.erase(it);
    }
};

int main() {
    ifstream f("dictionary.txt");
    ifstream v("delete.txt");
    ifstream k("find.txt");
    Map dict(f);
    dict.write_dictionary();
    dict.add_word(f);
    dict.write_dictionary();
    dict.delete_word(v);
    dict.write_dictionary();
    dict.find_word(k);
    dict.edit_translation(f);
    dict.write_dictionary();
}
