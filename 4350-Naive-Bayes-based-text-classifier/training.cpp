#include"string"
#include"vector"
#include <iostream>
#include <fstream>
#include"dirent.h"
#include"common.h"

// C++ program to extract words from
// a strung using stringstream
#include<bits/stdc++.h>

using namespace std;


bool is_word_significant(string word);
void increment_count_word(vector<Word_count> & current_list, string word);
Word_count max_word_in_cat(vector<Word_count> find_in, vector<Word_count> not_in);
Word_count max_word_in_remaining(vector<Word_count> find_in, vector<vector<Word_count>>not_in_cat, vector<Word_count> not_in_all);

//m (number of categories)
//n (number of most frequent words)
//k (number of text files under each categories)
void training(const unsigned int training_configuration[]) {
    const unsigned int m = training_configuration[0];
    const unsigned int n = training_configuration[1];
    const unsigned int k = training_configuration[2];
    // to compute the most frequent words and their frequencies, we have to
    // count the times the words appear, both in total and also per category
    // then deduce the frequencies, in total and also per category
    // To do it, we need the variables below
    // We use vector because they provide simplicity of use
    // But we restrict their sizes to the sizes we need
    vector< vector<Word_count> > count_words_per_category;
    count_words_per_category.resize(m);
    vector<Word_count> count_words_in_all_categories;
    unsigned int nb_words_in_category[m];
    for (unsigned int i = 0; i < m ; i++) {
        nb_words_in_category[i] = 0;
    }
    unsigned int total_nb_words = 0 ;
    vector< vector<Word_count> > most_frequent_words_per_category ;
    most_frequent_words_per_category.resize(m);
    for (unsigned int i = 0; i < m ; i++) {
        most_frequent_words_per_category[i].resize(int(n/m));
    }
    vector<Word_count> most_frequent_words_in_all_categories;
    most_frequent_words_in_all_categories.resize(n);
    // these two will contain the words with the highest frequencies
    // both per category, or in globally
    vector <vector<Word_frequency> > frequencies_most_frequent_words_per_category;
    frequencies_most_frequent_words_per_category.resize(m);
    for (unsigned int i = 0; i < m ; i++) {
        frequencies_most_frequent_words_per_category[i].resize(int(n/m));
    }
    vector<Word_frequency> frequencies_most_frequent_words_in_all_categories;
    frequencies_most_frequent_words_in_all_categories.resize(n);
    // will contain the path of all files, with k files in each of the m categories
    vector <string> category_names;
    vector < vector <string> > path_to_texts_per_category;
    path_to_texts_per_category.resize(m);
    for (unsigned int i = 0; i < m ; i++) {
        path_to_texts_per_category[i].resize(k);
    }

    // read the folder mini_newsgroups to get the m categories
    // and for each category get the path and name of the k files
    DIR *dir;
    DIR *dir2;
    struct dirent *ent;
    struct dirent *ent2;
    unsigned int category_counter = 0;
    if ((dir = opendir ("../../mini_newsgroups")) != nullptr) {
      /* print all the files and directories within directory mini_newsgroups */
      while ( ((ent = readdir (dir)) != nullptr) and category_counter < m) {
        unsigned int text_counter = 0;
        string path_to_category = "../../mini_newsgroups/"; // to be completed just below
        path_to_category.append(ent->d_name);
        category_names.push_back(ent->d_name);

        // print all the files and directories within directory mini_newsgroups\-current_category-
        if ((dir2 = opendir ( path_to_category.c_str() ) ) != nullptr) {
            while ( ( (ent2 = readdir (dir2)) != nullptr ) and (text_counter < k) ) {
                string path_to_text = path_to_category + "/";
                path_to_text.append(ent2->d_name);
                path_to_texts_per_category[category_counter][text_counter] = path_to_text;
                text_counter++;
            }
            closedir (dir2);
        } else {
            /* could not open directory */
            cout << "error1: could not open directory " << path_to_category.c_str();
        }
        category_counter++;
      }
      closedir (dir);
    } else {
      /* could not open directory */
      cout << "error2: could not open directory mini_newsgroups";
    }

    // for each category
    for(unsigned int cat = 0; cat < m; cat++) {
        // for each file in each category
        for(unsigned int j = 0; j < k; j++) {
            // we read a word
            string line;
            ifstream file (path_to_texts_per_category[cat][j].c_str());
            if (file.is_open()) {
              while ( getline (file,line) )
              {
                  // word variable to store word
                  string word;
                  // making a string stream
                  stringstream iss(line);
                  // Read the string and find next word to store in word variable.
                  while (iss >> word) {
                    if ( !is_word_significant(word) ) {
                        continue;
                    }
                    // update the counter for the word globally (in all categories)
                    increment_count_word(count_words_in_all_categories, word);
                    nb_words_in_category[cat]++;
                    total_nb_words++;
                    // update the counter for the word in its category
                    increment_count_word(count_words_per_category[cat], word);
                    nb_words_in_category[cat]++;
                    total_nb_words++;
                  }
              }
              file.close();
            } else {
                printf("error3:Unable to open file");
            }
        }
    }

    // now that we have counted all the words, we find the list
    // of n words {W1, W2, ..., Wn } containing n/m most frequent words
    // for each selected category
    for(unsigned int cat = 0; cat < m; cat++) {
        for(unsigned int nb_words_in_cat = 0; nb_words_in_cat < int(n/m); nb_words_in_cat++) {
            // find word with max counter in count_words_per_category[cat]
            // and such as word is not already in most_frequent_words_per_category[cat]
            Word_count word = max_word_in_cat(count_words_per_category[cat], most_frequent_words_per_category[cat]);
            most_frequent_words_per_category[cat][nb_words_in_cat] = word;
            // create a new object Word_frequency with the word itself, and the frequency of this word in its category
            Word_frequency freq_word = Word_frequency(word.get_word(), float(word.get_counter()) / float(nb_words_in_category[cat]) );
            frequencies_most_frequent_words_per_category[cat][nb_words_in_cat] = freq_word;
        }
    }

    // find the most frequent words among the remaining words in all categories.
    // so we already found before the n/m words for each category, that is n words in total
    // here we find again n words, whatever the category, that are not found in the previous
    // search by category
    for(unsigned int nb_words = 0; nb_words < n; nb_words++) {
        // find the word with max_count not in most_frequent_words_per_category[cat] for all cat
        // and not in most_frequent_words_all_categories
        Word_count word = max_word_in_remaining(count_words_in_all_categories, most_frequent_words_per_category, most_frequent_words_in_all_categories);
        most_frequent_words_in_all_categories[nb_words] = word;
        // create a new object Word_frequency with the word itself, and the frequency of this word in its category
        Word_frequency freq_word = Word_frequency( word.get_word(), float(word.get_counter()) / float(total_nb_words) );
        frequencies_most_frequent_words_in_all_categories[nb_words] = freq_word;
    }

    // print results
    // for each category, we print the most frequent words along with their frequency
    for(unsigned int cat = 0; cat < m; cat++) {
        printf(" Most frequent words per category \n ");
        printf("%s\n", category_names[cat].c_str());
        for(unsigned int i = 0; i < int(n/m); i++) {
            // print the current word in the current category, with its frequency
            Word_frequency current = frequencies_most_frequent_words_per_category[cat][i];
            printf("%s: %f\n", current.get_word().c_str(), current.get_frequency());
        }
    }

    printf(" Most frequent words among the remaining words in all categories\n ");
    for(unsigned int i = 0; i < n; i++) {
        // print the current word, with its frequency
        Word_frequency current = frequencies_most_frequent_words_in_all_categories[i];
        printf("%s: %f\n", current.get_word().c_str(), current.get_frequency());
    }


}

// to keep it simple
// we consider that a word is significant if
// its length is superior to 3
// It is relevant as many articles and prepositions
// are short words
bool is_word_significant(string word) {
    if (word.length() > 3) {
        return true;
    }
    else return false;
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

// find word with max counter in find_in
// and such as word is not already in not_in
Word_count max_word_in_cat(vector<Word_count> find_in, vector<Word_count> not_in) {
    Word_count max_word = find_in[0];
    for(unsigned int i = 1; i < find_in.size(); i++) {
        // if the current word is already in not_in, we continue to next word
        bool is_already_in_not_in = false;
        for(unsigned int j = 0; j < not_in.size(); j++) {
            if ( not_in[j].get_word() == find_in[i].get_word() ) {
                is_already_in_not_in = true;
                break;
            }
        }
        if (is_already_in_not_in) continue;

        // if the current word has a better counter, it becomes the new max
        if ( find_in[i].get_counter() > max_word.get_counter() ) {
            max_word = find_in[i];
        }
    }
    return max_word;
}

// find word with max counter in find_in
// and such as word is not already in not_in_cat or not_in_all
Word_count max_word_in_remaining(vector<Word_count> find_in, vector<vector<Word_count>>not_in_cat, vector<Word_count> not_in_all) {
    Word_count max_word = find_in[0];
    for(unsigned int i = 1; i < find_in.size(); i++) {
        // if the current word is already in not_in_all, we continue to next word
        bool is_already_in_not_in_all = false;
        for(unsigned int j = 0; j < not_in_all.size(); j++) {
            if ( not_in_all[j].get_word() == find_in[i].get_word() ) {
                is_already_in_not_in_all = true;
                break;
            }
        }
        if (is_already_in_not_in_all) continue;

        // if the current word is already in not_in_cat, we continue to next word
        // for this, we need to iterate through the words in all the categories
        // (same than just above but with one more loop)
        bool is_already_in_not_in_cat = false;
        for(unsigned int cat = 0; cat < not_in_cat.size(); cat++) {
            for(unsigned int k = 0; k < not_in_cat[cat].size(); k++) {
                if ( not_in_cat[cat][k].get_word() == find_in[i].get_word() ) {
                    is_already_in_not_in_cat = true;
                    break;
                }
            }
            if (is_already_in_not_in_cat) break;
        }
        if (is_already_in_not_in_cat) continue;

        // if the current word has a better counter, it becomes the new max
        if ( find_in[i].get_counter() > max_word.get_counter() ) {
            max_word = find_in[i];
        }
    }
    return max_word;
}

