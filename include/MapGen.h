#ifndef MAPGEN_H
#define MAPGEN_H

#include <stdio.h>
#include <iostream>
#include <vector>

#define HEIGHT 15
#define WIDTH 25

class MapGen
{
    public:
        MapGen();
        virtual ~MapGen();
        std::vector< std::vector<int> > generateMap();

    protected:
        void generatePath(std::vector< std::vector<int> > &map);
    private:
};

#endif // MAPGEN_H
