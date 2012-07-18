//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PARAMETERS_H_INCLUDED
#define PARAMETERS_H_INCLUDED

#include <string>
#include <stdexcept>

namespace Vera
{

struct Parameters
{
    static void set(const std::string& assoc);
    static void readFromFile(const std::string& name);

    static std::string get(const std::string& name, const std::string& defaultValue);
};

} // namespace Vera

#endif // PARAMETERS_H_INCLUDED
