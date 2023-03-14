#include "PointQuadTree.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    PointQuadTree object;
    string city_name;
    int max_x, max_y, x_coord, y_coord, range;
    ifstream file;
    file.open("cities.txt"); //read the cities.txt file
    file >> max_x >> max_y; //the first line which includes the max values
    while (!file.eof()){ //read the rest until the end
        file >> city_name >> x_coord >> y_coord;
        object.insert(city_name, x_coord, y_coord);
    }
    file.close();
    
    object.pretty_print(); //print the tree
    
    file.open("queries.txt"); //read the queries.txt file
    string line; unsigned long index;
    while(getline(file,line)){ //getting line and then storing datas without the comma separating them
        index = line.find(',');
        x_coord = stoi(line.substr(0,index));
        line = line.substr(index+1);
        index = line.find(',');
        y_coord = stoi(line.substr(0,index));
        line = line.substr(index+1);
        index = line.find(',');
        range = stoi(line.substr(0,index));
        object.search(x_coord, y_coord, range);
    }
    file.close();
    return 0;
}
