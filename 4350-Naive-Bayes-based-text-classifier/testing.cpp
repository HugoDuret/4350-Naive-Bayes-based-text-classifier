//Project 3 Stage 2 - Code
//Name : Hugo Duret
//Student ID : 20555806
//Due date : Dec 05, 2019

#include <iostream>
#include <fstream>
#include"dirent.h"
// C++ program to extract words from
// a string using stringstream
#include<bits/stdc++.h>

#include "common.h"
#include <math.h>

const unsigned int NB_TEXT_FILES = 100;


// declarations of functions that are implemented at the end of the file
vector<Word_frequency> word_frequencies_in_text(string category_name, unsigned int offset);
string classify_text(Training_results training_results, vector<Word_frequency> word_freq_in_text);

// from the training results obtained from the training of the classifier
// and the distribution of text files among the categories
// we test the accuracy of the classifier training
float testing(Training_results training_results, const vector<float> probability_distribution) {
    // first we "unpack" the values from the training_results
    // just so accessing them is done through variables with a nicer name
    const unsigned int number_of_categories = training_results.number_of_categories;
    const unsigned int number_of_most_frequent_words = training_results.number_of_most_frequent_words;
    const unsigned int number_of_texts_per_category = training_results.number_of_texts_per_category;
    const unsigned int total_nb_words = training_results.total_nb_words;
    const vector <vector<Word_frequency> > frequencies_most_frequent_words_per_category = training_results.frequencies_most_frequent_words_per_category;
    const vector<Word_frequency> frequencies_most_frequent_words_in_all_categories = training_results.frequencies_most_frequent_words_in_all_categories;
    const vector <string> category_names = training_results.category_names;
    const unsigned int * nb_words_in_category = training_results.nb_words_in_category;

    // the same number of categories should be used for the training
    // and the testing, if not, it's an error
    if (number_of_categories != probability_distribution.size()) {
        throw "ERROR (01): Different number of categories used.";
    }

    // we compute the number of text files chosen for each category
    unsigned int text_files_per_category [number_of_categories];
    for ( unsigned int cat = 0 ; cat < number_of_categories; cat++) {
        text_files_per_category[cat] = static_cast<unsigned int>(NB_TEXT_FILES * probability_distribution[cat]);
    }

    unsigned int nb_of_corrects_classification = 0;
    // for each category
    // we go through all the texts chosen for that category
    // we classify this text, and compare the classification with the reality
    for ( unsigned int cat = 0 ; cat < number_of_categories; cat++) {
        for ( unsigned int txt_nb = 0 ; txt_nb < number_of_categories; txt_nb++) {
            // get the word counters in the text
            // the offset is set to "txt_nb + number_of_texts_per_category" so we don't use the same texts for training and testing
            const vector<Word_frequency> word_freq_in_text = word_frequencies_in_text( category_names[cat], txt_nb + number_of_texts_per_category );
            // classify the text in one of the categories
            string classified_category = classify_text( training_results, word_freq_in_text );
            // test if the classification is correct
            if (classified_category == category_names[cat]) {
                nb_of_corrects_classification++;
            }
        }
    }

    return nb_of_corrects_classification / NB_TEXT_FILES;
}

vector<Word_frequency> word_frequencies_in_text(string category_name, unsigned int offset) {
    // read the folder mini_newsgroups to get the file text, with correct offset
    DIR *dir;
    struct dirent *ent;
    string path_to_file = "../../mini_newsgroups/" + category_name; //to be completed with file name
    // print all the files and directories within directory mini_newsgroup/category_name
    if ((dir = opendir ( path_to_file.c_str() ) ) != nullptr) {
        unsigned int skiped_nb = 0;
        while ( (ent = readdir (dir)) != nullptr ) {
            // we skip a number equals to "offset" of files
            if (skiped_nb < offset) {
                skiped_nb++;
                continue;
            }
            path_to_file = path_to_file + "/";
            path_to_file.append(ent->d_name);
            break;
        }
        closedir (dir);
    } else {
        /* could not open directory */
        cout << "error1: could not open directory " << path_to_file.c_str();
    }

    // We count the words inside the text
    // Now we count the words in each text file of each category
    vector<Word_count> word_counts;
    unsigned int nb_words_in_text = 0;
    string line;
    ifstream file (path_to_file.c_str());
    if (file.is_open()) {
      bool is_header = true;
      while ( getline (file,line) )
      {
          // word variable to store word
          string word;
          // making a string stream
          stringstream iss(line);
          // Read the string and find next word to store in word variable.
          while (iss >> word) {
            // we skip all the first lines until we reach the word "Lines:"
            // as it is the last line of the header in most files
            if (word == "Lines:") {
                is_header = false;
                continue;
            }
            if (is_header) {continue;}
            if ( !is_word_significant(word) ) {
                continue;
            }
            // update the counter for the word in its category
            increment_count_word(word_counts, word);
            nb_words_in_text++;
          }
      }
      file.close();
    } else {
        /* could not open directory */
        cout << "error2: could not open directory " << path_to_file.c_str();
    }

    vector<Word_frequency> word_frequencies;
    for ( unsigned int word_counter = 0 ; word_counter < word_counts.size(); word_counter++) {
        Word_count word = word_counts[word_counter];
        word_frequencies.push_back( Word_frequency(word.get_word(), word.get_counter() / nb_words_in_text) );
    }

    return word_frequencies;
}

// choose the category of the text based on the word frequencies in the text and in the categories
// for each word of the text, we iterate through all categories
// and for each word in these categories, we see if the text word is the same than the category word
// if so (the word appears in this category), we add to a variable the product of the frequency
// of the word in the category with the frequency of the word in the text
string classify_text(Training_results training_results, const vector<Word_frequency> word_freq_in_text) {
    const unsigned int number_of_categories = training_results.number_of_categories;
    const vector <vector<Word_frequency> > frequencies_most_frequent_words_per_category = training_results.frequencies_most_frequent_words_per_category;

    // keep trace of the probability of the text being in a category
    // initialize it to 0
    float probability_category[number_of_categories];
    for( unsigned int nb_cat = 0; nb_cat < number_of_categories; nb_cat++) {
        probability_category[nb_cat] = 0.0;
    }
    // for each word in the text
    for( unsigned int nb_text_word = 0; nb_text_word < word_freq_in_text.size(); nb_text_word++) {
        // for each category
        for( unsigned int nb_cat = 0; nb_cat < number_of_categories; nb_cat++) {
            // for each word in this category
            for( unsigned int nb_cat_word = 0; nb_cat_word < frequencies_most_frequent_words_per_category[nb_cat].size(); nb_cat_word++) {
                Word_frequency text_word = word_freq_in_text[nb_text_word];
                Word_frequency cat_word = frequencies_most_frequent_words_per_category[nb_cat][nb_cat_word];
                if ( text_word.get_word() == cat_word.get_word() ) {
                    probability_category[nb_cat] += text_word.get_frequency() * cat_word.get_frequency();
                }

            }
        }
    }

    // find the maximum in "probability_category"
    // that is, the index of the category in which the text has the higher probability to be
    unsigned int index_max = 0;
    for( unsigned int nb_cat = 0; nb_cat < number_of_categories; nb_cat++) {
        if (probability_category[nb_cat] > probability_category[index_max]) {
            index_max = nb_cat;
        }
    }

    const vector <string> category_names = training_results.category_names;
    return category_names[index_max];

}







