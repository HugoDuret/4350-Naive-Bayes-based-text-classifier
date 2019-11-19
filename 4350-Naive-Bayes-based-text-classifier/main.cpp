//Project 3 Stage 2 - Code
//Name : Hugo Duret
//Student ID : 20555806
//Due date : Dec 05, 2019

#include <iostream>
#include "training.cpp"

using namespace std;

// m, n, k
const unsigned int Training_Configuration_1 [3] = {5, 25, 10};
const unsigned int Training_Configuration_2 [3] = {5, 25, 20};
const unsigned int Training_Configuration_3 [3] = {10, 50, 10};

int main()
{
    printf("\nWelcome in this Naïve-Bayes based text classifier!");
    printf("\nm (number of categories)");
    printf("\nn (number of most frequent words)");
    printf("\nk (number of text files under each category)");

    printf("\n\nTraining with configuration one");
    printf("\n m=%d; n=%d, k=%d", Training_Configuration_1[0], Training_Configuration_1[1],Training_Configuration_1[2]);
    Training_results t1 = training(Training_Configuration_1);
    t1.print();

//    printf("\n\nTraining with configuration two");
//    printf("\n m=%d; n=%d, k=%d", Training_Configuration_2[0], Training_Configuration_2[1],Training_Configuration_2[2]);
//    Training_results t2 = training(Training_Configuration_2);
//    t2.print();

//    printf("\n\nTraining with configuration three");
//    printf("\n m=%d; n=%d, k=%d", Training_Configuration_3[0], Training_Configuration_3[1],Training_Configuration_3[2]);
//    Training_results t3 = training(Training_Configuration_3);
//    t3.print();


    return 0;
}
