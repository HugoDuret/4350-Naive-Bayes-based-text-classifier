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
bool word_in_count_words_all_categories(string word);
void increment_count_word_all_categories(string word);
bool word_in_count_words_per_category(int cat, string word);
void increment_count_word_per_category(int cat, string word);

//m (number of categories)
//n (number of most frequent words)
//k (number of text files under each categories)
void training(unsigned int m, unsigned int n, unsigned int k) {
    // to compute the most frequent words and their frequencies, we have to
    // count the times the words appear, both in total and also per category
    // then deduce the frequencies, in total and also per category
    // To do it, we need these variables
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
    // will contain the path of all files, with k files in each of the m categories
    vector < vector <string> > path_to_texts_per_category;
    path_to_texts_per_category.resize(m);
    for (unsigned int i = 0; i < m ; i++) {
        most_frequent_words_per_category[i].resize(k);
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
        printf("debug: m=%d, category_counter =%d %s\n", m, category_counter, path_to_category.c_str());

        /* print all the files and directories within directory mini_newsgroups/-current_category- */
        printf("so far so goo1d");
        if ((dir2 = opendir ( path_to_category.c_str() ) ) != nullptr) {
            printf("so far so good");
            while ( ( (ent2 = readdir (dir2)) != nullptr ) and (text_counter < k) ) {
                string path_to_text = path_to_category + "/";
                path_to_text.append(ent2->d_name);
                path_to_texts_per_category[category_counter][text_counter] = path_to_text;
                printf("debug2 : k=%d, text_counter =%d %s\n", k, text_counter, path_to_text.c_str());
                text_counter++;
            }
            closedir (dir2);
        } else {
            /* could not open directory */
            printf("error1: could not open directory %s", path_to_category.c_str());
        }
        category_counter++;
      }
      closedir (dir);
    } else {
      /* could not open directory */
      printf("error2: could not open directory mini_newsgroups");
    }

    // DEBUG BEGIN
    for(unsigned int i = 0; i < m; i++) {
        for(unsigned int j = 0; j < k; j++) {
            printf("all path: %d, %d = %s\n", i, j, path_to_texts_per_category[i][j].c_str());
        }
    }


    // for each category
    for(unsigned int i = 0; i < m; i++) {
        // for each file in each category
        for(unsigned int j = 0; j < k; j++) {
            // we read a word
            string line;
            ifstream file (path_to_texts_per_category[i][j].c_str());
            if (file.is_open()) {
              while ( getline (file,line) )
              {
                printf("%s \n", line.c_str());
              }
              file.close();
            } else {
                printf("error3:Unable to open file");
            }

        }
    }
    // DEBUG END


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
                    if ( word_in_count_words_all_categories(word) ) {
                        increment_count_word_all_categories(word);
                        nb_words_in_category[cat]++;
                        total_nb_words++;
                    }
                    // update the counter for the word in its category
                    if ( word_in_count_words_per_category(cat, word) ) {
                        increment_count_word_per_category(cat, word);
                        nb_words_in_category[cat]++;
                        total_nb_words++;
                    }
                  }
              }
              file.close();
            } else {
                printf("error3:Unable to open file");
            }
        }
    }

    // now that we count all the words
    // we find the most frequent ones
    // by category,
    // and globally (only if not in a category)
    for(unsigned int cat = 0; cat < m; cat++) {

    }



}

bool is_word_significant(string word) {

}

bool word_in_count_words_all_categories(string word) {

}

void increment_count_word_all_categories(string word) {
    // update if exists
    // or create
}

bool word_in_count_words_per_category(unsigned int cat, string word) {

}

void increment_count_word_per_category(unsigned int cat, string word) {
    // update if exists
    // or create
}

