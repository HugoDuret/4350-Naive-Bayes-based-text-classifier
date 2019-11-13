#include <iostream>
#include "training.cpp"

using namespace std;

// m, n, k
//const unsigned int Training_Configuration_1 [3] = {5, 25, 10};
const unsigned int Training_Configuration_2 [3] = {5, 25, 20};
//const unsigned int Training_Configuration_3 [3] = {10, 50, 10};

int main()
{
    training(Training_Configuration_2);
    return 0;
}
