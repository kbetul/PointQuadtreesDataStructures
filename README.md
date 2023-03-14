# PointQuadtreesDataStructures
 Implementing a point quadtree of cities according to their locations.

 Assignment was done accordingly:

 Your program should read two text files, namely cities.txt and queries.txt. While the former specifies a two-dimensional space together with some cities located in this space, the latter specifies the queries to be answered.

 In the cities.txt file, the first line specifies the 2D space by presenting the coordinate of the upper right corner of the space in the form of
                     <x coordinate> <y coordinate>

 Note that the origin (0, 0) of the coordinate system corresponds to the lower left corner of the space and that negative coordinate values are not valid.

 Each of the remaining line in the cities.txt file then represents a city in the form of:
                <city_name> <x coordinate of the city> <y coordinate of the city>

 City names do not contain space characters and the coordinates cannot assume negative values.

 Given this file, your program shall insert the cities into an initially empty point quadtree in the order they are given and then shall pretty print the tree using the following recursive algorithm
    pretty_print (root): // pretty print the quadtree rooted at root: 
        if root != NULL: // if the tree is not empty print the city name stored at the root 
            pretty_print(root.SE) // recursively print the south east subtree
            pretty_print(root.SW) // recursively print the south west subtree
            pretty_print(root.NE) // recursively print the north east subtree
            pretty_print(root.NW) // recursively print the north west subtree

 Once the point quadtree is constructed, the queries.txt file is read. In this file, every line corresponds to a query in the form
                 <x coordinate> <y coordinate> <radius>

 Given such a query, two lines should be produced. The first line shall report the comma separated list of cities within <radius> unit of distance from the point (<x coordinate>, <y coordinate>). And, the second line shall report the comma separated list of cities visited during the search operation. Note that in each case cities should be reported in the order they have been found and visited, respectively; you shall visit the quadrants (i.e., subtrees) recursively in exactly the same order given in Figure 2.17 of the attached document. Note further that the result of a query should be printed out right after the query line is processed. Furthermore, if no cities are found, then the string ‘<None>’ should be printed out.

 Check the pdf for understanding what is a point quadtree :>