#ifndef COMMON_OBJECTS_H
#define COMMON_OBJECTS_H
#include"string"

using namespace std;

class Word_count {
    string word;
    int counter;

public:
    Word_count(string w) : word(w), counter(1) {}
    Word_count() : word(""), counter(1) {}
    void operator++() {
        counter = counter + 1;
    }
    string get_word() {return word;}
    void set_word(string w) {word = w;}
    int get_counter() {return counter;}

};

class Word_frequency {
    string word;
    double frequency;

public:
    Word_frequency(string w, double freq) : word(w), frequency(freq) {}
    string get_word() {return word;}
    double get_frequency() {return frequency;}

};

#endif // COMMON_OBJECTS_H
