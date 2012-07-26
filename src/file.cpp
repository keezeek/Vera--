/*
 * file.cpp
 *
 *  Created on: 26.07.2012
 *      Author: dapf4486
 */

#include "file.hpp"
#include "globals.hpp"
#include <fstream>

vera::file::file(const std::string& name)
{
    std::ifstream file(name.c_str());
    if (!file)
    {
        throw std::runtime_error("cannot open source file " + name);
    }

    std::string line;
    std::string fullSource;
    while (std::getline(file, line))
    {
        lines_.push_back(line);
        fullSource += line;

        // built-in rule
        if (file.eof())
        {
            vera::problems.push_back(vera::problem(name, lines_.size(), "no newline at end of file"));
        }
        else
        {
            fullSource += '\n';
        }
    }

	Vera::Tokens::parse(name, fullSource);
}
