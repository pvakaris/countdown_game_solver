#include <iostream>
using std::endl;

#include <string>
using std::string;

#include <sstream>
using std::istringstream;
using std::ostringstream;

#include <stack>
using std::stack;

#include <vector>
using std::vector;

#include <algorithm>
using std::next_permutation;

using std::pair;

/**
 * Class represents a solution to the countdown game
 */
class CountdownSolution {

private:
    string solution;
    int value;

public:
    CountdownSolution()
            : solution(), value(0) {
    }

    CountdownSolution(const string & solutionIn, const int valueIn)
            : solution(solutionIn), value(valueIn) {
    }

    const string & getSolution() const {
        return solution;
    }

    int getValue() const {
        return value;
    }

};

/**
 * Converts integer to String
 * @param x int which to convert to
 * @return x value as a String
 */
string intToString(const int x) {
    ostringstream str;
    str << x;
    return str.str();
}

/**
 * Divide the given sequence of arithmetic symbols and numbers separated by whitespaces
 * and put all those parts into a vector
 * @param sequence A sequence of symbols.
 * @return A vector that contains number and symbols in string objects.
 */
vector<string> divideString(string sequence) {
    vector<string> elements;
    istringstream iss(sequence);

    for(string el; iss >> el; ) {
        elements.push_back(el);
    }
    return elements;
}

/**
 * Evaluate a string which contains a sequence of symbols in RPN and return the answer.
 * @param seq A sequence of arithmetic symbols and numbers in RPN.
 * @return Answer of the RPN string.
 */
double evaluateCountdown(const string & seq) {

    stack<double> st;
    vector<string> parts = divideString(seq);

    // WORK WITH THE STACK
    for(auto & part : parts) {
        // If the part 'i' is not a mathematical symbol.
        if(part != "+" && part != "-" && part != "/" && part != "*") {
            st.push(stod(part));
        }
        else {
            double two = st.top(); // Used to get top 2 elements of the stack and then remove them from it.
            st.pop();
            double one = st.top();
            st.pop();

            if(part == "+") {
                st.push(one + two);
            }
            else if(part == "-") {
                st.push(one - two);
            }
            else if(part == "/") {
                st.push(one / two);
            }
            else if(part == "*") {
                st.push(one * two);
            }
        }
    }
    // RESULT WILL BE THE TOP ELEMENT OF THE STACK
    return st.top();
}

/**
 * Used to make a primitive Reverse Polish Notation given the idea that
 * the equation is always ofa format 4*7/9/6+3-5.....
 * @param equation An equation.
 * @return A RPN of the equation.
 */
 string makeRPN(string equation) {
     bool notFinished = true;
     int y = 0;
     string number;
     while(notFinished) {
         if(isdigit(equation[y])) {
             number += equation[y];
         }
         else {
             notFinished = false;
         }
         y ++;
     }
     string answer;
     answer += number;
     for(int i = 1; i < equation.size(); i ++) {
         if(equation[i] == '*' || equation[i] == '+' || equation[i] == '/' || equation[i] == '-') {
             bool notFinished = true;
             int y = (i+1);
             string number;
             while(notFinished) {
                 if(isdigit(equation[y])) {
                     number += equation[y];
                 }
                 else {
                     notFinished = false;
                 }
                 y ++;
             }
             answer += " ";
             answer += number;
             answer += " ";
             answer += equation[i];
         }
     }
     return answer;
 }

/**
 * Use the operation on two numbers.
 * @param currentValue First number.
 * @param operationNumber Operation number.
 * @param nextNumber Second number.
 * @return return the firstNumber (operation) secondNumber.
 */
int updateValue(int currentValue, int operationNumber, int nextNumber){
    if (operationNumber == 0) {
        currentValue = currentValue + nextNumber;
    }
    else if (operationNumber == 1) {
        currentValue = currentValue - nextNumber;
    }
    else if (operationNumber == 2) {
        currentValue = currentValue * nextNumber;
    }
    else if (operationNumber == 3) {
        currentValue = currentValue / nextNumber;
    }
    return currentValue;
}

/**
 * Get the operation symbol according to the provided number.
 * @param operationNumber Operation number.
 * @return
 */
char getOperationSymbol(int operationNumber){
    char symbol;
    if (operationNumber == 0) {
        symbol = '+';
    }
    else if (operationNumber == 1) {
        symbol = '-';
    }
    else if (operationNumber == 2) {
        symbol = '*';
    }
    else {
        symbol = '/';
    }
    return symbol;
}

/**
 * Change the equation string according to the new data.
 * @param operationNumbers A vector of operation numbers.
 * @param numbers A vector of numbers.
 * @param equation A string containing the equation.
 */
void changeEquation(vector<int> & operationNumbers, vector<int> & numbers, string & equation){
    equation = "";
    equation.append(intToString(numbers[0]));
    for(int i = 1; i < numbers.size(); i ++) {
        equation += getOperationSymbol(operationNumbers[i - 1]);
        equation.append(intToString(numbers[i]));
    }
}

/**
 * Check if the value that is closest to the total value changes.
 * @param total Total to aim for.
 * @param closest Closest value to the total.
 * @param newValue A new value that could replace the closest.
 * @return true if newValue is closer to the total than closest, false otherwise.
 */
bool closestChanges(int & total, int & closest, int & newValue) {
    if(newValue == total) {
        return true;
    }
    else if(closest > total && newValue > total) {
        if((newValue-total) < (closest-total)) {
            return true;
        }
    }
    else if(closest < total && newValue < total){
        if((total-closest) > (total-newValue)) {
            return true;
        }
    }
    else if(closest < total && newValue > total){
        if((total-closest) > (newValue-total)) {
            return true;
        }
    }
    else if(closest > total && newValue < total){
        if((closest-total) > (total-newValue)) {
            return true;
        }
    }
    return false;
}

/**
 * Try to reach total with the given number.
 * @param numbers A vector of numbers.
 * @param total The goal to aim at.
 * @param closest Current closest value to the goal.
 * @param equation Equation that reached the current closest value.
 * @return true if the goal has been reached, false otherwise. (used to end the cycle of searching)
 */
bool loopOnce(vector<int> numbers, int total, int & closest, string & equation) {
    int temp = numbers[0];
    if(closestChanges(total, closest, temp)) {
        closest = temp;
        equation = "";
        equation.append(intToString(temp));
    }
    if(closest == total) {
        return true;
    }
    return false;
}

/**
 * Try to reach total with two given numbers.
 * @param numbers A vector of numbers.
 * @param total The goal to aim at.
 * @param closest Current closest value to the goal.
 * @param equation Equation that reached the current closest value.
 * @return true if the goal has been reached, false otherwise. (used to end the cycle of searching)
 */
bool loopTwice(vector<int> numbers, int total, int & closest, string & equation) {
    vector<int> operationNumbers;
    for(int i = 0; i < 4; i++){
        int temp = numbers[0];
        for (int m = 1; m < 2; m++){
            if (m == 1){
                temp = updateValue(temp, i, numbers[m]);
            }
        }
        if(closestChanges(total, closest, temp)) {
            closest = temp;
            operationNumbers.push_back(i);
            changeEquation(operationNumbers, numbers, equation);
            operationNumbers.clear();
        }
        if(closest == total) {
            return true;
        }
    }
    return false;
}

/**
 * Try to reach total with three given numbers.
 * @param numbers A vector of numbers.
 * @param total The goal to aim at.
 * @param closest Current closest value to the goal.
 * @param equation Equation that reached the current closest value.
 * @return true if the goal has been reached, false otherwise. (used to end the cycle of searching)
 */
bool loopThreeTimes(vector<int> numbers, int total, int & closest, string & equation) {
    vector<int> operationNumbers;
    for(int i = 0; i < 4; i++){
        for(int y = 0; y < 4; y++){
            int temp = numbers[0];
            for (int m = 1; m < 3; m++){
                if (m == 1){
                    temp = updateValue(temp, i, numbers[m]);
                }
                else if (m == 2){
                    temp = updateValue(temp, y, numbers[m]);
                }
            }
            if(closestChanges(total, closest, temp)) {
                closest = temp;
                operationNumbers.push_back(i);
                operationNumbers.push_back(y);
                changeEquation(operationNumbers, numbers, equation);
                operationNumbers.clear();
            }
            if(closest == total) {
                return true;
            }
        }
    }
    return false;
}

/**
 * Try to reach total with four given numbers.
 * @param numbers A vector of numbers.
 * @param total The goal to aim at.
 * @param closest Current closest value to the goal.
 * @param equation Equation that reached the current closest value.
 * @return true if the goal has been reached, false otherwise. (used to end the cycle of searching)
 */
bool loopFourTimes(vector<int> numbers, int total, int & closest, string & equation) {
    vector<int> operationNumbers;
    for(int i = 0; i < 4; i++){
        for(int y = 0; y < 4; y++){
            for(int j = 0; j < 4; j++){
                int temp = numbers[0];
                for (int m = 1; m < 4; m++){
                    if (m == 1){
                        temp = updateValue(temp, i, numbers[m]);
                    }
                    else if (m == 2){
                        temp = updateValue(temp, y, numbers[m]);
                    }
                    else if (m == 3){
                        temp = updateValue(temp, j, numbers[m]);
                    }
                }
                if(closestChanges(total, closest, temp)) {
                    closest = temp;
                    operationNumbers.push_back(i);
                    operationNumbers.push_back(y);
                    operationNumbers.push_back(j);
                    changeEquation(operationNumbers, numbers, equation);
                    operationNumbers.clear();
                }
                if(closest == total) {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Try to reach total with five given numbers.
 * @param numbers A vector of numbers.
 * @param total The goal to aim at.
 * @param closest Current closest value to the goal.
 * @param equation Equation that reached the current closest value.
 * @return true if the goal has been reached, false otherwise. (used to end the cycle of searching)
 */
bool loopFiveTimes(vector<int> numbers, int total, int & closest, string & equation) {
    vector<int> operationNumbers;
    for(int i = 0; i < 4; i++){
        for(int y = 0; y < 4; y++){
            for(int j = 0; j < 4; j++){
                for(int u = 0; u < 4; u++){
                    int temp = numbers[0];
                    for (int m = 1; m < 5; m++){
                        if (m == 1){
                            temp = updateValue(temp, i, numbers[m]);
                        }
                        else if (m == 2){
                            temp = updateValue(temp, y, numbers[m]);
                        }
                        else if (m == 3){
                            temp = updateValue(temp, j, numbers[m]);
                        }
                        else if (m == 4){
                            temp = updateValue(temp, u, numbers[m]);
                        }
                    }
                    if(closestChanges(total, closest, temp)) {
                        closest = temp;
                        operationNumbers.push_back(i);
                        operationNumbers.push_back(y);
                        operationNumbers.push_back(j);
                        operationNumbers.push_back(u);
                        changeEquation(operationNumbers, numbers, equation);
                        operationNumbers.clear();
                    }
                    if(closest == total) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/**
 * Try to reach total with six given numbers.
 * @param numbers A vector of numbers.
 * @param total The goal to aim at.
 * @param closest Current closest value to the goal.
 * @param equation Equation that reached the current closest value.
 * @return true if the goal has been reached, false otherwise. (used to end the cycle of searching)
 */
bool loopSixTimes(vector<int> numbers, int total, int & closest, string & equation) {
    vector<int> operationNumbers;
    for(int i = 0; i < 4; i++){
        for(int y = 0; y < 4; y++){
            for(int j = 0; j < 4; j++){
                for(int u = 0; u < 4; u++){
                    for(int p = 0; p < 4; p++){
                        int temp = numbers[0];
                        for (int m = 1; m < 6; m++){
                            if (m == 1){
                                temp = updateValue(temp, i, numbers[m]);
                            }
                            else if (m == 2){
                                temp = updateValue(temp, y, numbers[m]);
                            }
                            else if (m == 3){
                                temp = updateValue(temp, j, numbers[m]);
                            }
                            else if (m == 4){
                                temp = updateValue(temp, u, numbers[m]);
                            }
                            else if (m == 5){
                                temp = updateValue(temp, p, numbers[m]);
                            }
                        }
                        if(closestChanges(total, closest, temp)) {
                            closest = temp;
                            operationNumbers.push_back(i);
                            operationNumbers.push_back(y);
                            operationNumbers.push_back(j);
                            operationNumbers.push_back(u);
                            operationNumbers.push_back(p);
                            changeEquation(operationNumbers, numbers, equation);
                            operationNumbers.clear();
                        }
                        if(closest == total) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

/**
 * Get a vector that contains vector with all the possible combinations of numbers from the provided vector.
 * @param numbers A vector with numbers.
 * @return A vector of vectors with all possible combinations of given numbers.
 */
vector<vector<int>> getAllPossibleCombinationsOfNumbers(vector<int> numbers) {
    vector<vector<int>> toReturn;
    do {
        toReturn.push_back(numbers);
    } while (next_permutation(numbers.begin(),
                              numbers.end()));
    return toReturn;
}

/**
 * Find subset of numbers from the provided vector of numbers.
 * @param offset Number to start from.
 * @param howMany How big the subset must be.
 * @param combination Combination which to add to the vector of subsets.
 * @param numbers Number vector which is used to make subsets.
 * @param combinations A vector of subsets of a given size from the vector of numbers.
 */
void findSubset(int offset, int howMany, vector<int> *combination, vector<int> numbers, vector<vector<int>> *combinations) {
    vector<int> *c = combination;
    if (howMany == 0) {
        combinations->push_back(*combination);
        return;
    }
    for (int i = offset; i <= numbers.size() - howMany; ++i) {
        combination->push_back(numbers[i]);
        findSubset(i + 1, howMany - 1, c, numbers, combinations);
        combination->pop_back();
    }
}

/**
 * Get all subsets of the given size from the given vector of numbers:
 * Example: numbers = {1, 2, 3}.
 * getAllSubsetsOfSize(numbers, 2) -> {1, 2}, {2, 3}, {1, 3}.
 * @param numbers A vector of numbers.
 * @param size Size of subsets.
 * @return A vector containing all those subsets.
 */
vector<vector<int>> getAllSubsetsOfSize(vector<int> numbers, int size) {
    vector<int> combination;
    auto *combinations = new vector<vector<int>>;
    findSubset(0, size, &combination, std::move(numbers), combinations);
    return *combinations;
}

/**
 * Get a pair containing equation and the value that can be reached by that equation. The value
 * is the closest possible value that can be achieved with arithmetic operations *,/,+,- on the given vector
 * of numbers.
 * @param numbers Numbers to perform the arithmetic operations on.
 * @param total A value that has to be reached
 * @return A pair with answer equation and the value that equation reaches.
 */
pair<string,int> * getAnswer(const vector<int>& numbers, int total) {
    int closest = 0;
    string equation;
    for(int i = 1; i <= 6; i ++) {
        vector<vector<int>> combinations = getAllSubsetsOfSize(numbers, i);
        vector<vector<int>> cSuper;
        for (const auto &v: combinations) {
            auto n = getAllPossibleCombinationsOfNumbers(v);
            for (const auto &z: n) {
                cSuper.push_back(z);
            }
        }
        if (i == 1) {
            for (auto v: cSuper) {
                bool answerFound = loopOnce(v, total, closest, equation);
                if (answerFound) {
                    return new pair<string, int> (equation, closest);
                }
            }
        } else if (i == 2) {
            for (auto v: cSuper) {
                bool answerFound = loopTwice(v, total, closest, equation);
                if (answerFound) {
                    return new pair<string, int> (equation, closest);
                }
            }
        } else if (i == 3) {
            for (auto v: cSuper) {
                bool answerFound = loopThreeTimes(v, total, closest, equation);
                if (answerFound) {
                    return new pair<string, int> (equation, closest);
                }
            }
        } else if (i == 4) {
            for (auto v: cSuper) {
                bool answerFound = loopFourTimes(v, total, closest, equation);
                if (answerFound) {
                    return new pair<string, int> (equation, closest);
                }
            }
        } else if (i == 5) {
            for (auto v: cSuper) {
                bool answerFound = loopFiveTimes(v, total, closest, equation);
                if (answerFound) {
                    return new pair<string, int> (equation, closest);
                }
            }
        } else if (i == 6) {
            for (auto v: cSuper) {
                bool answerFound = loopSixTimes(v, total, closest, equation);
                if (answerFound) {
                    return new pair<string, int> (equation, closest);
                }
            }
        }
    }
    return new pair<string, int> (equation, closest);
}

/**
 * Solve the Countdown problem.
 * @param numbers A vector of six numbers.
 * @param target Target number.
 * @return A CountdownSolution object.
 */
CountdownSolution solveCountdownProblem(vector<int> numbers, int target) {
    pair<string, int> * answer = getAnswer(numbers, target);
    string rpn = makeRPN(answer->first);
    int number = answer->second;
    delete answer;
    return CountdownSolution(rpn, number);
}

