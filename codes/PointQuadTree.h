#ifndef PointQuadTree_h
#define PointQuadTree_h
#include <string>
#include <vector>

using namespace std;

struct pointQuadTreeNode
{
    string cityName;
    int x_coord, y_coord;
    struct pointQuadTreeNode* NW;
    struct pointQuadTreeNode* NE;
    struct pointQuadTreeNode* SW;
    struct pointQuadTreeNode* SE;
    pointQuadTreeNode(string city, int x, int y)
    {
        cityName = city;
        x_coord = x; y_coord = y;
        NW = NULL; NE = NULL; SW = NULL; SE = NULL;
    }
};

struct search_point
{
    int x_coord, y_coord, radius;
    search_point (int x, int y, int r)
    {
        x_coord = x; y_coord = y; radius = r;
    }
};

class PointQuadTree
{
    private:
        pointQuadTreeNode * root;
        vector <string> cities_visited, cities_in_range;
        void pretty_print(pointQuadTreeNode * point);
        void search(search_point search, pointQuadTreeNode * P);
        void make_empty(pointQuadTreeNode *& point) const;
    public:
        PointQuadTree(); //constructor
        string compare(search_point P, pointQuadTreeNode * root);
        vector<string> compare_edge(search_point P, pointQuadTreeNode * compare);
        void insert(string cityName, int x_coord, int y_coord);
        bool check_range(search_point point, pointQuadTreeNode * variable);
        void pretty_print();
        void search(int x_coord, int y_coord, int range);
        ~PointQuadTree(); //destructor
};

#endif /* PointQuadTree_h */
