#include "SvnParser.hpp"

sf::Shape SvgParser::ParseFromFile(const std::string& file) {
        sf::Shape shape;

        boost::property_tree::ptree pt;
        read_xml(file, pt);

        std::string d = pt.get("svg.g.path.<xmlattr>.d", "");

        Point current_point(0,0);

        // split "d" at delimiters
        std::vector<std::string> strs;
        boost::split_regex(strs, d, boost::regex("[ ,]+"));
        std::cout << "Found path: " << d << std::endl;

        unsigned int i = 0;
        std::string last_part = "";
        while (i < strs.size()){
            std::string part = strs[i];
            if (part == ""){
                std::cout << "Empty part..." << std::endl;
                i++;
                continue;
            }

            std::cout << "-----"<< std::endl<<"Parsing part # " << part << " # ..." << std::endl;

            if (SvgParser::IsNumeric(&part[0])){
                // command left out
                if (last_part == ""){
                    std::cout << "Oh shit, there was no command in the path data." << std::endl;
                    exit(1);
                }
                else{
                    part = last_part;
                    i--;
                }
            }

            if (part == "m" or part == "l"){
                // draw line to rel. point
                current_point = Point(current_point.x + boost::lexical_cast<float>(strs[i+1]),
                                      current_point.y + boost::lexical_cast<float>(strs[i+2]));
                i+=2;
                shape.AddPoint(current_point.x, current_point.y, sf::Color(0,0,0),sf::Color(0,0,0));
                std::cout << "added point " << current_point.x << "/" << current_point.y << std::endl;
            }
            else if (part == "M" or part == "L"){
                // draw line to abs. point
                current_point = Point(boost::lexical_cast<float>(strs[i+1]),
                                      boost::lexical_cast<float>(strs[i+2]));
                i+=2;
                shape.AddPoint(current_point.x, current_point.y, sf::Color(0,0,0),sf::Color(0,0,0));
                std::cout << "added point " << current_point.x << "/" << current_point.y << std::endl;
            }

            last_part = part;
            i++;
        }

        return shape;
    }
