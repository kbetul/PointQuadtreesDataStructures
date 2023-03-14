#include <iostream>
#include "PointQuadTree.h"
#include <string>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

PointQuadTree::PointQuadTree()
{ // Constructor which generates an empty root
    root = NULL;
}

bool PointQuadTree::check_range(search_point point, pointQuadTreeNode * variable)
{ //checking if the variable is in the range of point
    bool return_val = true;
    if (variable != NULL){
        int x_pow = pow(variable->x_coord - point.x_coord,2.0);
        int y_pow = pow(variable->y_coord - point.y_coord,2.0);
        float distance = sqrt(x_pow + y_pow);
        if (distance > point.radius) {
            return_val = false;
        }
    } else {
        return_val = false;
    }
    return return_val;
}

string PointQuadTree::compare(search_point P, pointQuadTreeNode * compare)
{ //comparing 2 points to check their locations to see if its whether SE, SW, NE or NW
    string val_return;
    if (compare != NULL)
        if (P.x_coord < compare->x_coord){
            if (P.y_coord < compare->y_coord){
                val_return = "SW";
            } else {
                val_return = "NW";
            }
        } else if (P.y_coord < compare->y_coord) {
            val_return = "SE";
        } else {
            val_return = "NE";
        }
    return val_return;
}

vector<string> PointQuadTree::compare_edge(search_point search_obj, pointQuadTreeNode * P)
{ //checking every edge of range and collecting a vector of directions to visit all cities
    vector<string> comparison;
    if (check_range(search_obj, P) == true) { //if the city is in the range
        comparison.push_back("SE"); comparison.push_back("SW"); comparison.push_back("NE"); comparison.push_back("NW");
    } else {
        if (!(find(comparison.begin(), comparison.end(), compare(search_obj, P)) != comparison.end())) //dont add if the direction is already in vector
            comparison.push_back(compare(search_obj, P));
        int orig_x, orig_y, temp_x, temp_y;
        orig_x = search_obj.x_coord; orig_y = search_obj.y_coord;
        temp_x =search_obj.x_coord+search_obj.radius; search_obj.x_coord = temp_x; //adding radius and temporarily changing the x_coord value
        if (!(find(comparison.begin(), comparison.end(), compare(search_obj, P)) != comparison.end())) //dont add if the direction is already in vector
            comparison.push_back(compare(search_obj, P));
        temp_x = search_obj.x_coord-(search_obj.radius)*2; search_obj.x_coord = temp_x; //subtracting radius and temporarily changing the x_coord value
        if (!(find(comparison.begin(), comparison.end(), compare(search_obj, P)) != comparison.end())) //dont add if the direction is already in vector
            comparison.push_back(compare(search_obj, P));
        search_obj.x_coord = orig_x; //changing it back to its original value
        temp_y = search_obj.y_coord+search_obj.radius; search_obj.y_coord = temp_y; //adding radius and temporarily changing the y_coord value
        if (!(find(comparison.begin(), comparison.end(), compare(search_obj, P)) != comparison.end())) //dont add if the direction is already in vector
            comparison.push_back(compare(search_obj, P));
        temp_y = search_obj.y_coord-(search_obj.radius)*2; search_obj.y_coord = temp_y;//subtracting radius and temporarily changing the y_coord value
        if (!(find(comparison.begin(), comparison.end(), compare(search_obj, P)) != comparison.end())) //dont add if the direction is already in vector
            comparison.push_back(compare(search_obj, P));
        search_obj.y_coord = orig_y; //changing it back to its original value
    }
    return comparison;
}

void PointQuadTree::insert(string cityName, int x_coord, int y_coord)
{ //inserting non-recursively
    pointQuadTreeNode *father, *T, *toAdd = new pointQuadTreeNode(cityName, x_coord, y_coord); string quadrant;
    if (root == NULL) { root = toAdd; } //if the tree is empty add the insert to root
    else {
        T = root;
        while (T != NULL) { //tree is not empty
            father = T; //to remember the father
            search_point temp = search_point(x_coord, y_coord, 0);
            quadrant = compare(temp,T);
            if      (quadrant == "SE"){ T = father->SE; } //checking where to add
            else if (quadrant == "SW"){ T = father->SW; }
            else if (quadrant == "NE"){ T = father->NE; }
            else if (quadrant == "NW"){ T = father->NW; }
        }
        if (T == NULL){ //found the direction to add
            if      (quadrant == "SE"){ father->SE = toAdd; }
            else if (quadrant == "SW"){ father->SW = toAdd; }
            else if (quadrant == "NE"){ father->NE = toAdd; }
            else if (quadrant == "NW"){ father->NW = toAdd; }
        }
    }
}

void PointQuadTree::pretty_print()
{ //public function of pretty_print
    pretty_print(root); cout << endl;
}

void PointQuadTree::pretty_print(pointQuadTreeNode * root)
{ //private and recursive function of pretty_print from the assignment pdf
    if (root != NULL){
        cout << root->cityName << endl;
        pretty_print(root->SE);
        pretty_print(root->SW);
        pretty_print(root->NE);
        pretty_print(root->NW);
    }
}

void PointQuadTree::search(int x_coord, int y_coord, int range)
{ //public search function
    search_point search_obj = search_point(x_coord,y_coord,range);
    search(search_obj, root);
    if(cities_in_range.size()==0){ //cities_in_range is a private variable of the class which is a string array that keeps the cities in the range
        cout << "<None>"; //print none if cities_in_range is empty
    } else {
        for (int i=0; i<cities_in_range.size();i++){ //printing every index of vector
            cout << cities_in_range[i];
            if (i!=cities_in_range.size()-1) //printing comma in between if its not the last element
                cout << ", ";
        }
    }
    cout << endl;
    for (int i=0; i<cities_visited.size();i++){ //cities_visited is a private variable of the class which is a string array that keeps the visited cities
        cout << cities_visited[i];
        if (i!=cities_visited.size()-1) //printing comma in between if its not the last element
            cout << ", ";
    }
    cout << endl; cout << endl;
    cities_in_range.clear(); cities_visited.clear();
}

void PointQuadTree::search(search_point search_obj, pointQuadTreeNode * P)
{ //private recursive function search
    vector<string> comparison;
    comparison = compare_edge(search_obj, P);
    if (check_range(search_obj,P) == true) { //if the point is in the range add it to cities_in_range vector
        if (!(find(cities_in_range.begin(), cities_in_range.end(), P->cityName) != cities_in_range.end()))
            cities_in_range.push_back(P->cityName);
    }
    if(P!=NULL){
        if (find(comparison.begin(), comparison.end(),"SE") != comparison.end()){ //if vector comparison has SE direction
            if (!(find(cities_visited.begin(), cities_visited.end(), P->cityName) != cities_visited.end())) //if the cities_visited does not already have the value in it add it to vector
                cities_visited.push_back(P->cityName);
            search(search_obj, P->SE); //recursively search for direction SE
        }
        if (find(comparison.begin(), comparison.end(),"SW") != comparison.end()){ //if vector comparison has SW direction
            if (!(find(cities_visited.begin(), cities_visited.end(), P->cityName) != cities_visited.end()))
                cities_visited.push_back(P->cityName);
            search(search_obj, P->SW); //recursively search for direction SW
        }
        if (find(comparison.begin(), comparison.end(),"NE") != comparison.end()){ //if vector comparison has NE direction
            if (!(find(cities_visited.begin(), cities_visited.end(), P->cityName) != cities_visited.end()))
                cities_visited.push_back(P->cityName);
            search(search_obj, P->NE); //recursively search for direction NE
        }
        if (find(comparison.begin(), comparison.end(),"NW") != comparison.end()){ //if vector comparison has NW direction
            if (!(find(cities_visited.begin(), cities_visited.end(), P->cityName) != cities_visited.end()))
                cities_visited.push_back(P->cityName);
            search(search_obj, P->NW); //recursively search for direction NW
        }
    }
}

void PointQuadTree::make_empty(pointQuadTreeNode *& point) const
{ //emptying the whole tree recursively
    if(point!=NULL){
        make_empty(point->SE);
        make_empty(point->SW);
        make_empty(point->NE);
        make_empty(point->NW);
        delete point;
    }
    point = NULL;
}

PointQuadTree::~PointQuadTree()
{ //destructor for class
    make_empty(root);
}

