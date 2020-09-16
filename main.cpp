#include <iostream>
#include <string>

std::string cyclicShiftString(std::string s){
    std::string newFront = s.substr(1);          // Grab all but the first character of the original string to use as the beginning of the new cycled string
    std::string newBack = s.substr(0,1);  // Grab the first character of the original string to append to the end of the new cycled string
    return newFront + newBack;                        // Concatenate the front and back of the new string together and return it
}

void encode(std::string& s, int algorithm_option){
    // Variables for the encoding algorithm
    size_t str_len = s.length();                           // Get the length of the input string
    auto *cycled_strings {new std::string[str_len]};       // Create a dynamically allocated array to hold all of the cycled strings with the size equal to the length of the string
    auto *sorted_cycles {new std::string[str_len]};        // Create a dynamically allocated array to hold all of the sorted cycles with the size equal to the length of the string
    auto *last_char{new char[str_len]};                    // Create a dynamically allocated char array to hold the last characters of each of the sorted strings
    int orig_index;                                        // Create an int to store the index of the original string in the sorted array

    cycled_strings[0] = s;                                 // The first element of the cycled strings is the uncycled original string
    //std::cout << "0: " << cycled_strings[0] << std::endl;  // Print out the first element in cycled_strings (the original string)
    // Cycle the input string iteratively until we've completed all of our cycles (we should cycle str_len-1 times)
    for(int i = 1; i < str_len; ++i){
        cycled_strings[i] = cyclicShiftString(cycled_strings[i-1]);
        //std::cout << i << ": " << cycled_strings[i] << std::endl;  // Output each cycled string and its index in the array
    }
    //std::cout << std::endl;


    //=====================================//
    //  Sort the cycles lexicographically  //
    //=====================================//

    // Insertion sort (option 0)
    if(algorithm_option == 0){
        int index;            // Variable to hold the index of the current value of the array we're trying to sort
        std::string compare;  // Variable to store the comparison value for the insertion sort (the current indexed value of the array)
        for(int i = 0; i < str_len; i++) {
            index = i;
            //std::cout << "Index" << index << std::endl;  // Print the current index being used for the insertion sort
            compare = cycled_strings[i];
            while (index > 0 && cycled_strings[index - 1] > compare) {
                //std::cout << "Shifting..." << std::endl;          // Print a notification for every shift performed
                cycled_strings[index] = cycled_strings[index - 1];  // Shift
                index = index - 1;                                  // Decrement the index
            }
            cycled_strings[index] = compare;
        }
    }

    // Quick sort (option 1)
    if(algorithm_option == 1){
        // Quick sort will go here...
    }

    // Print the sorted cycles and get the last character and store them into
    for(int i = 0; i < str_len; i++){
        //std::cout << i << ": " << cycled_strings[i] << std::endl;  // Output each cycled string and its index in the array
        last_char[i] = cycled_strings[i][str_len-1];  // Get the last character of the current string and put it into the corresponding entry for last_char
        if(cycled_strings[i].compare(s) == 0){  // Grab the index of the original string in the sorted array for the first part of the output
            orig_index = i;
        }
    }
    // Print the index of the original string in the sorted array
    //std::cout << "Original index:" << orig_index << std::endl;
    std::cout << orig_index << std::endl;

    // Get the clusters of characters from the last_char array
    int current_cluster_num = 1;  // Variable to hold the cluster number of the current character that is being examined in the last_char array; there's always at least one of each character
    //std::cout << "Calculating encoded string..." << std::endl;
    for(int i = 0; i < str_len; i++){
        //std::cout << "Current character: " << last_char[i] << std::endl;
        //std::cout << "Next character: " << last_char[i+1] << std::endl;
        if(i < str_len-1 && last_char[i+1] == last_char[i]){
            //std::cout << "Cluster Found!" << std::endl;
            current_cluster_num = current_cluster_num + 1;  // If the next character is equal to the current character, increment the current cluster number and the index
            //i++;
        }
        else{
            std::cout << current_cluster_num << " " << last_char[i] << " ";  // If the next character is not equal to the current character, the cluster is finished; output the number of the character that was found and the character itself
            current_cluster_num = 1;
        }
    }

    std::cout << std::endl;

}

int main(int argc, char** argv) {
    int insert_or_quick = 0; // 0 for insertion sort, 1 for quicksort
    /*
    // Track command line args
    std::cout << "Command Line Args: " << argc << std::endl;
    std:: cout << "Arguments entered: " << std::endl;
    for(int i = 0; i < argc; ++i){
        std::cout << argv[i] << std::endl;
    }
     */
    //std::cout << "Selected algorithm: " << argv[1] << std::endl;
    if(!strcmp(argv[1], "insertion")){
        //std::cout << "Insertion sort selected" << std::endl;
        insert_or_quick = 0;
    }
    else if(!strcmp(argv[1], "quick")){
        //std::cout << "Quick sort selected" << std::endl;
        insert_or_quick = 1;
    }
    else{
        std::cout << "Invalid input. Exiting..." << std::endl;
        return 0;
    }
    /*
    // Sample code to ensure base functionality of functions is correct
    std::cout << "Hello, World!" << std::endl;
    std::string stringToCycle;
    std::cin >> stringToCycle;
    std::string stringOne = cyclicShiftString(stringToCycle);
    std::cout << stringOne << std::endl;
    encode(stringToCycle, insert_or_quick);
    int str = stringToCycle.length();
    std::cout << "Back in main " << std::endl;
    std::cout << "Length of string: " << stringToCycle.length();
     */

    //
    std::string stringToEncode;                       // Set up variable to hold current string to encode
    while(!std::cin.eof()){                           // Keep going until end of file
        getline(std::cin, stringToEncode);                   // Get the next string in the file
        encode(stringToEncode, insert_or_quick);  // Encode the string
    }
    //std::cout << "Back in main " << std::endl;
    return 0;
}
