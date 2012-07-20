//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "SourceLines.h"
#include "Tokens.h"
#include "globals.hpp"
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Vera
{

typedef std::map<std::string, std::vector<std::string>> SourceFileCollection;
static SourceFileCollection sources_;

const std::vector<std::string>& SourceLines::getAllLines(const std::string& name)
{
    const SourceFileCollection::const_iterator it = sources_.find(name);
    if (it != sources_.end())
    {
        return it->second;
    }
    else
    {
        // lazy load of the source file
        loadFile(name);
        return sources_[name];
    }
}

void SourceLines::loadFile(const std::string& name)
{
    std::ifstream file(name.c_str());
    if (file.is_open() == false)
    {
        std::ostringstream ss;
        ss << "cannot open source file " << name;
        throw std::runtime_error(ss.str());
    }

    std::vector<std::string>& lines = sources_[name];

    std::string line;
    std::string fullSource;
    while (getline(file, line))
    {
        lines.push_back(line);
        fullSource += line;

        // built-in rule
        if (file.eof())
        {
            vera::problems.push_back(vera::problem(name, lines.size(), "no newline at end of file"));
        }
        else
        {
            fullSource += '\n';
        }
    }

    Tokens::parse(name, fullSource);
}

int SourceLines::getLineCount(const std::string& name)
{
    return static_cast<int>(getAllLines(name).size());
}

const std::string& SourceLines::getLine(const std::string& name, int lineNumber)
{
    const std::vector<std::string>& lines = getAllLines(name);
    if (lineNumber < 1 || lineNumber > static_cast<int>(lines.size()))
    {
        std::cerr << "Requested wrong line number: " << lineNumber << '\n';
        std::cerr << "lines.size in " << name << " is " << static_cast<int>(lines.size()) << '\n';
        throw std::runtime_error("requested line number is out of range");
    }

    return lines[lineNumber - 1];
}

} // namespace Vera
