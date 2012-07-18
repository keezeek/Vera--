//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "Parameters.h"
#include <fstream>
#include <sstream>
#include <map>

namespace Vera
{

typedef std::map<std::string, std::string> ParametersCollection;
static ParametersCollection parameters_;

void Parameters::set(const std::string& assoc)
{
    std::string::size_type pos = assoc.find("=");
    if (pos != std::string::npos)
    {
        std::string name = assoc.substr(0, pos);
        std::string value = assoc.substr(pos + 1);

        parameters_[name] = value;
    }
    else
    {
        std::ostringstream ss;
        ss << "Invalid parameter association: " << assoc;
        throw std::runtime_error(ss.str());
    }
}

std::string Parameters::get(const std::string& name, const std::string& defaultValue)
{
    ParametersCollection::iterator it = parameters_.find(name);
    if (it != parameters_.end())
    {
        return it->second;
    }
    else
    {
        return defaultValue;
    }
}

void Parameters::readFromFile(const std::string& name)
{
    std::ifstream file(name.c_str());
    if (file.is_open() == false)
    {
        std::ostringstream ss;
        ss << "cannot open parameters file " << name;
        throw std::runtime_error(ss.str());
    }

    std::string line;
    int lineNumber = 0;
    while (getline(file, line))
    {
        ++lineNumber;

        if (line.empty())
        {
            continue;
        }

        if (line[0] != '#')
        {
            set(line);
        }
    }
}

} // namespace Vera
