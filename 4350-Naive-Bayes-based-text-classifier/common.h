//Project 3 Stage 2 - Code
//Name : Hugo Duret
//Student ID : 20555806
//Due date : Dec 05, 2019

#ifndef COMMON_OBJECTS_H
#define COMMON_OBJECTS_H
#include"string"
#include"vector"

using namespace std;

class Word_count {
    string word;
    unsigned int counter;

public:
    Word_count(string w) : word(w), counter(1) {}
    Word_count(string w, unsigned int c) : word(w), counter(c) {}
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
    unsigned int get_counter() {return counter;}

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


// a word is significant if it is not a preposition nor an article
// we also try to extract only long words
bool is_word_significant(string word) {
    const string english_articles [3] = {"a", "an", "the"};
    const string english_prepositions [70] = {
        "aboard",
        "about",
        "above",
        "across",
        "after",
        "against",
        "along",
        "amid",
        "among",
        "anti",
        "around",
        "as",
        "at",
        "before",
        "behind",
        "below",
        "beneath",
        "beside",
        "besides",
        "between",
        "beyond",
        "but",
        "by",
        "concerning",
        "considering",
        "despite",
        "down",
        "during",
        "except",
        "excepting",
        "excluding",
        "following",
        "for",
        "from",
        "in",
        "inside",
        "into",
        "like",
        "minus",
        "near",
        "of",
        "off",
        "on",
        "onto",
        "opposite",
        "outside",
        "over",
        "past",
        "per",
        "plus",
        "regarding",
        "round",
        "save",
        "since",
        "than",
        "through",
        "to",
        "toward",
        "towards",
        "under",
        "underneath",
        "unlike",
        "until",
        "up",
        "upon",
        "versus",
        "via",
        "with",
        "within",
        "without"
    };

    const string meta_words [12] = {"Newsgroups:", "Newsgroups20", "From:", "Path:", "Subject:", "Date:", "Lines:", "Organization:", "References:", "Sender:", "Nntp-Posting-Host:", "Message-ID:"};

    // check if is a meta word
    for(unsigned int i = 0; i < meta_words->length(); i++) {
        if (word == meta_words[i]) {
            return false;
        }
    }
    // check if is an article
    for(unsigned int i = 0; i < english_articles->length(); i++) {
        if (word == english_articles[i]) {
            return false;
        }
    }
    // check if is a preposition
    for(unsigned int i = 0; i < english_prepositions->length(); i++) {
        if (word == english_prepositions[i]) {
            return false;
        }
    }

    // we also try to extract only long words
    // so we filter short words
    if (word.size() < 5) {
        return false;
    }

    return true;

}

// update the word if it exists inside current_list
// or create it inside current_list with counter set to one
void increment_count_word(vector<Word_count> & current_list, string word) {
    // check if exists, and update if it does
    for(unsigned int i = 0; i < current_list.size(); i++) {
        if (current_list[i].get_word() == word) {
            current_list[i].operator++();
            return;
        }
    }
    // else if we didn't find it, we create one
    current_list.push_back(Word_count(word));
}

#endif // COMMON_OBJECTS_H
