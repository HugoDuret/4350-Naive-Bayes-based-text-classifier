//Project 3 - Report
//Name : Hugo Duret
//Student ID : 20555806
//Due date : Nov 13, 2019

#ifndef COMMON_OBJECTS_H
#define COMMON_OBJECTS_H
#include"string"
#include"vector"

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

// this data structure is used to keep the results of the training
// so they can all be stored in one common variable
struct Training_results {
    const unsigned int number_of_categories;
    const unsigned int number_of_most_frequent_words;
    const unsigned int number_of_texts_per_category;
    const unsigned int total_nb_words;
    const vector <vector<Word_frequency> > frequencies_most_frequent_words_per_category;
    const vector<Word_frequency> frequencies_most_frequent_words_in_all_categories;
    const vector <string> category_names;
    const unsigned int * nb_words_in_category;

    // print results
    // for each category, we print the most frequent words along with their frequency
    void print() {
        printf("\nMost frequent words per category \n ");
        for(unsigned int cat = 0; cat < number_of_categories; cat++) {
            printf("\n\ncategory = %s\n", category_names[cat].c_str());
            for(unsigned int i = 0; i < int(number_of_most_frequent_words/number_of_categories); i++) {
                // print the current word in the current category, with its frequency
                Word_frequency current = frequencies_most_frequent_words_per_category[cat][i];
                printf("Word = %s; frequency = %.2f\n", current.get_word().c_str(), current.get_frequency());
            }
        }

        printf("\n\nMost frequent words among the remaining words in all categories\n ");
        for(unsigned int i = 0; i < number_of_most_frequent_words; i++) {
            // print the current word, with its frequency
            Word_frequency current = frequencies_most_frequent_words_in_all_categories[i];
            printf("Word = %s; frequency = %.4f\n", current.get_word().c_str(), current.get_frequency());
        }

    }
};

#endif // COMMON_OBJECTS_H
