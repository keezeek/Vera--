//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SOURCELINES_H_INCLUDED
#define SOURCELINES_H_INCLUDED

#include <vector>

namespace Vera
{

struct SourceLines
{
    static const std::vector<std::string>& getAllLines(const std::string& name);
    static int getLineCount(const std::string& name);
    static const std::string& getLine(const std::string& name, int lineNumber);

    static void loadFile(const std::string& name);
};

} // namespace Vera

#endif // SOURCELINES_H_INCLUDED
