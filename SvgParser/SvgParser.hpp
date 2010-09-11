#ifndef SVGPARSER_HPP
#define SVGPARSER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/lexical_cast.hpp>


struct Point{
public:
    Point(float ax, float ay){
        x = ax; y = ay;
    }
    void Set(float ax, float ay){
        x = ax; y = ay;
    }
    float x,y;
};

class SvgParser{
public:
    static sf::Shape ParseFromFile(const std::string& file);
    static bool IsNumeric(const char *p)
    {
      for ( ; *p; p++)
        if (*p < '0' || *p > '9')
          return false;
      return true;
    };

};

#endif
