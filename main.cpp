//
//  main.cpp
//  Test read in
//
//  Created by Samantha Hemleben on 5/18/16.
//  Copyright © 2016 Samantha Hemleben. All rights reserved.
//



#include <iostream>
//#include "Test Read in.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <time.h>
#include <ctime>
using namespace std;
ifstream infile;
int size_of_array_one, size_of_array_two;
vector <vector <double>> import_array;
string strData = "";
vector <double> maximum;
int temp_location_x, temp_location_y, x_move, y_move;
vector<double> new_coordinate;
int x_origin = 15; // X was changed to 15
int y_origin = 12; // Y was changed to 12
int multiply_distance = 50; // There is 50 centimeters per step

// import data into the array import array
int readArray(){
    ifstream reader;
    import_array.clear();
    // Need to change to the according file path that it is it
    reader.open("/Users/hemlebensj/Desktop/Edge_detection/Fish_locations.csv");
    struct tokens: ctype<char>
    {
        tokens(): ctype<char>(get_table()) {}
        
        static ctype_base::mask const* get_table()
        {
            typedef ctype<char> cctype;
            static const cctype::mask *const_rc= cctype::classic_table();
            
            static cctype::mask rc[cctype::table_size];
            memcpy(rc, const_rc, cctype::table_size * sizeof(cctype::mask));
            
            rc[','] = ctype_base::space;
            rc[' '] = ctype_base::space;
            return &rc[0];
        }
    };
    for(int i=0; i<70; i++){
        // imports the data to the import array with a size of 70 which is HOPEFULLY as big as the csv file will get. If not WE NEED TO CHANGE THE SIZE ACCORDINGLY
        reader >> strData;
        stringstream ss(strData);
        ss.imbue(locale(locale(), new tokens()));
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector <string> vString(begin, end);
        import_array.push_back(vector<double>());
        if (reader.eof()) break;
        for (int j=0; j<70; j++){
            import_array[i].push_back(atof(vString[j].c_str()));
            if (reader.eof()) break;
            //cout << ' ' << import_array[i][j];
            
        }
        
    }
    
    //cout << "This is size" << import_array[0].size() << endl;
    return 0;
}

// Function that finds the max location in the csv file to start with
int find_max_location(){
    int temp =0;
    for(int i=0;i<import_array.size()-1;i++)
    {
        for (int j =1; j<import_array[0].size()-1;j++) {
            if(import_array[i][j] > temp){
            temp=import_array[i][j];
                temp_location_x = i+1;
                temp_location_y = j+1;}
        
        }}
    //cout << "This is biggest" << temp << endl;
    cout << "Location of x " << temp_location_x << " Location of y " << temp_location_y << endl;
    // add 50 back to the location in the csv code data values and don't forget that 1 is the origin reference location
  
    return 0;
}

//Based on the new coordinate system tells the fishing rod where to move
int move_to(){
    x_move = (x_origin - temp_location_x)*multiply_distance;
    y_move = (y_origin - temp_location_y)*multiply_distance;
    cout << "Move this much in x " << x_move << " Move this much in y " << y_move << endl;
    return 0;
}

int main(int argc, const char * argv[]) {
    readArray();
    find_max_location();
    move_to();
    return 0;
}
