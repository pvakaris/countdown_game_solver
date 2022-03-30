#include "Countdown.h"

#include <iostream>
using std::cout;
using std::endl;


#include <vector>
using std::vector;

int main() {

    int retval = 0;
    
    {
        cout << "Countdown numbers game: {1,2,3,4,5,6}, target 21 (can be solved by adding all the numbers together)\n";
        
        vector<int> numbers{1,2,3,4,5,6};
        CountdownSolution answer = solveCountdownProblem(numbers, 21);
        
        
        if (answer.getValue() == 21) {
            cout << "1) Pass: Correctly got to the target of 21\n";
        } else {
            cout << "1) Fail: Should have got to the target of 21, but only got " << answer.getValue() << std::endl;
            ++retval;
        }
    }
    
    {
        cout << "\n\nCountdown numbers game: {1,2,3,4,5,6}, target 123 (can be solved by e.g. 4 5 6 * * * 3 + )\n";
        
        vector<int> numbers{1,2,3,4,5,6};
        CountdownSolution answer = solveCountdownProblem(numbers, 123);
        
        
        if (answer.getValue() == 123) {
            cout << "2) Pass: Correctly got to the target of 123\n";
        } else {
            cout << "2) Fail: Should have got to the target of 123, but only got " << answer.getValue() << std::endl;
            ++retval;
        }
    }
    
    {
        cout << "\n\nCountdown numbers game: {75,2,5,6,1,4}, target 273 (can be solved by e.g. 75 6 - 4 * 2 - 1 - )\n";
        
        vector<int> numbers{75,2,5,6,1,4};
        CountdownSolution answer = solveCountdownProblem(numbers, 273);
        
        
        if (answer.getValue() == 273) {
            cout << "3) Pass: Correctly got to the target of 273\n";
        } else {
            cout << "3) Fail: Should have got to the target of 273, but only got " << answer.getValue() << std::endl;
            ++retval;
        }
    }
    
    return retval;
}
