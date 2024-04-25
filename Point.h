#pragma once

#include <vector>
#include <ostream>

class Point : public std::vector<double>
{
public:
    using vector<double>::vector;

    Point(vector<double> v):vector(v) {}

    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        os << "{";

        for (int j = 0; j < p.size(); j++) {
            if (j != 0) os << ", ";

            os << p[j];
        }

        os << "}";
        
       return os;
    }
};

