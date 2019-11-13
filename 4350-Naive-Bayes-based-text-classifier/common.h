//Project 3 - Report
//Name : Hugo Duret
//Student ID : 20555806
//Due date : Nov 13, 2019

#ifndef COMMON_OBJECTS_H
#define COMMON_OBJECTS_H
#include"string"

using namespace std;

class Word_count {
    string word;
    int counter;

public:
    Word_count(string w) : word(w), counter(1) {}
    Word_count(string w, int c) : word(w), counter(c) {}
    Word_count() : word(""), counter(1) {}
    void operator++() {
        counter = counter + 1;
    }
    Word_count & operator=(Word_count & other) {
        if (this != &other) { // self-assignment check expected
                counter = other.get_counter();
                word = other.get_word();
            }
            return *this;
    }
    string get_word() {return word;}
    void set_word(string w) {word = w;}
    int get_counter() {return counter;}

};

class Word_frequency {
    string word;
    float frequency;

public:
    Word_frequency(string w, float freq) : word(w), frequency(freq) {}
    Word_frequency() : word(""), frequency(0) {}
    Word_frequency & operator=(Word_frequency & other) {
        if (this != &other) { // self-assignment check expected
                frequency = other.get_frequency();
                word = other.get_word();
            }
            return *this;
    }
    string get_word() {return word;}
    float get_frequency() {return frequency;}

};

#endif // COMMON_OBJECTS_H
