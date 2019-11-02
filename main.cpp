
/*
 Program Purpose: The program allows the user to enter double values into a vector. All entries up to twenty will be stored. The program then outputs minimum,
 maximum, mean, and population standard deviation for the values that the user entered. The prorggam also lets the user replace values in the vector. Afterwards, the program displays the recalculated values of the vectors.
 
 Program Testing: To test the program, I inputted numbers from 1 to 21 into my program to see if my program stopped storing values after 20. Afterwards, I checked
 to see if the standard deviation calculated for each of the programs was correct. The value that my program outputted was 5, while the value that should have been outputted
 was 5.76. This was because I had certain variables set as int in my standard deviation calculations, and returned an int value.
*/
 
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const int VECTOR_MAX = 20;

void vector_input(vector<double> &my_vector, int VECTOR_MAX);
//PURPOSE: allows users to input up to double values into the vector. After twenty are inputted, user can continue to enter values but it will not be stored in vector. User presses 'd' or done to quite.
//  INPUTS: my_vector - vector containing doubles
//  RETURNS: true or false value of whether vector input is finished

double vector_minimum(vector<double> &my_vector);
//PURPOSE: goes through the whole vector to find minimum value
//  INPUTS: my_vector - vector containing doubles
//  RETURNS: returns a double displaying the minimum value in the vector

double vector_maximum(vector<double> &my_vector);
//PURPOSE: goes through the whole vector to find maximum value
//  INPUTS: my_vector - vector containing doubles
//  RETURNS: returns a double displaying the maximum value in the vector

double vector_mean(vector<double> &my_vector);
//PURPOSE: calculates the mean of the values within the vectors
//  INPUTS: my_vector - vector containing doubles
//  RETURNS: returns a double containing the mean of the values

double vector_population_sd(vector<double> &my_vector, double mean);
//PURPOSE: calculates the standard deviation of the values within the vector
//  INPUTS: my_vector - vector containing doubles
//          minimum - minimum value within the vector
//          maximum - maximum value within the vector
//          mean - mean value of the vector
//  RETURNS: standard deviation value of the vectors

void stats_printer(double min, double max, double mean, double sd);
//PURPOSE: prints out the statistics for the array that the user inputted
//  INPUTS: my_vector - vector containing doubles
//  RETURNS: nothing to return

void number_replacer(vector<double> &my_vector, int place, double replacement);
//PURPOSE: replaces a value in my_vector with new value inputted by user
//  INPUTS: my_vector - vector containing doubles
//          place - index of vector value being replaced
//          replacement: number replacing current vector value
//  RETURNS: nothing to return

bool valid_place(vector<double> my_vector, int place);
//PURPOSE: checks if the position that user wants to cahnge is valid
//  INPUTS: vector_index - index of vector inputted by the user
//  RETURNS: true or false value of whether the vector index value is valid

bool vector_filled();
//PURPOSE: initiates user input
//  INPUTS: none
//  RETURNS: true or false value of whether program has successfully run.

int main() {
    bool vector_entered = vector_filled();
    if(vector_entered){
        cout << "Thank you for entering values into the vector! \n";
    }
    return 0;
}

bool vector_filled(){
    double min = 0;
    double max = 0;
    double mean = 0;
    double sd = 0;
    bool not_quit = true;
    int place_chosen = 0;
    string entered_value = "";
    double converted_value = 0;
    int index = 0;
    
    vector<double> my_vector(0);
    vector_input(my_vector, VECTOR_MAX);
    
    //calls functions for min, max, mean, and sd
    min = vector_minimum(my_vector);
    max = vector_maximum(my_vector);
    mean = vector_mean(my_vector);
    sd = vector_population_sd(my_vector, mean);
    
    stats_printer(min, max, mean, sd);
    
    while(not_quit){
        //keeps asking user to choose place until user has chose a valid place
        do{
            cout << "Choose a place from 1 to " << my_vector.size() << ". \n";
            cin >> place_chosen;
        } while (!valid_place(my_vector, place_chosen));
        
        cout << "Please enter a double value. Type in q or quit to exit the program.";
        cin >> entered_value;
        
        //breaks loop if user quits. Otherwise, replaces value and calculates statistics
        if(entered_value == "q" || entered_value == "quit"){
            not_quit = false;
        } else {
            converted_value = stod(entered_value);
            number_replacer(my_vector, place_chosen, converted_value);
            min = vector_minimum(my_vector);
            max = vector_maximum(my_vector);
            mean = vector_mean(my_vector);
            sd = vector_population_sd(my_vector, mean);
            stats_printer(min, max, mean, sd);
        }
    }
    return true;
}

void vector_input(vector<double> &my_vector, int VECTOR_MAX){
    int index = 0;
    double converted_value = 0;
    string entered_value = "";
    bool entering_values = true;
    
    //enters new values into array until user enters 'd' or 'done'
    while(entering_values){
        cout << "Please enter a double value. Up to twenty entries will be stored. Type in d or done to be finished. \n";
        cin >> entered_value;
        
        //checks if user entered value is equal to 'd' or 'done'
        if(entered_value == "d" || entered_value == "done"){
            entering_values = false;
        } else if (my_vector.size() < 20){
            converted_value = stod(entered_value);
            my_vector.push_back(converted_value);
        }
        index++;
    }
}

double vector_minimum(vector<double> &my_vector){
    int index = 0;
    double minimum = my_vector.at(0);
    
    //goes through all values and finds minimum
    for (index = 1; index < my_vector.size(); ++index){
        if(my_vector.at(index) < minimum){
            minimum = my_vector.at(index);
        }
    }
    return minimum;
}

double vector_maximum(vector<double> &my_vector){
    int index = 0;
    double max = my_vector.at(0);
    
    //goes through all values and finds max
    for (index = 1; index < my_vector.size(); ++index){
        if(my_vector.at(index) > max){
            max = my_vector.at(index);
        }
    }
    return max;
}

double vector_mean(vector<double> &my_vector){
    int index = 0;
    double sum = 0;
    double mean = 0;
    
    //adds up all the vector values
    for(index = 0; index < my_vector.size(); ++index){
        sum = sum + my_vector.at(index);
    }
    //calculates mean of the values
    mean = sum / my_vector.size();
    return mean;
}

double vector_population_sd(vector<double> &my_vector, double mean){
    int index = 0;
    double squared_difference = 0;
    double sum = 0;
    double sd = 0;
    
    //calculates variance
    for (index = 0; index < my_vector.size(); ++index){
        squared_difference = pow((my_vector.at(index) - mean) , 2);
        sum = sum + squared_difference;
    }
    
    //divides variance by vector size and square roots.
    sd = pow((sum / my_vector.size()) , 0.5);
    return sd;
}

void stats_printer(double min, double max, double mean, double sd){
    //prints out all the stats
    cout << "Statistics for the numbers you entered: \n"
         << "Minimum value entered: " << min << endl
         << "Maximum value entered: " << max << endl
         << "Mean value for numbers you entered: " << mean << endl
         << "Population standard deviation: " << sd << endl;
}

void number_replacer(vector<double> &my_vector, int place, double replacement){
    //replaces number at place that user chooses with different double that user enters
    int index = place - 1;
    my_vector.at(index) = replacement;
}

bool valid_place(vector<double> my_vector, int place){
    //checks if the place that user chose is within the range of the vector
    if (place > 0 && place <= my_vector.size()){
        return true;
    }
    else {
        cout << "You entered a value that is not from 1 to " << my_vector.size() << " Please enter a valid place. \n";
        return false;
    }
}
