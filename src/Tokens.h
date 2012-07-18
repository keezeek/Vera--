//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TOKENS_H_INCLUDED
#define TOKENS_H_INCLUDED

#include "Reports.h"
#include <string>
#include <vector>

namespace Vera
{

class Tokens
{
public:
    struct SingleToken
    {
        SingleToken(const std::string& v, int ln, int cl, const std::string& n) :
                value_(v), line_(ln), column_(cl), name_(n)
        {
        }

        std::string value_;
        int line_;
        int column_;
        std::string name_;
    };

    typedef std::vector<SingleToken> TokenSequence;

    static void parse(const std::string& name, const std::string& src);

    static TokenSequence getTokens(const std::string& name,
        int fromLine, int fromColumn, int toLine, int toColumn,
        const std::vector<std::string>& filter);
};

} // namespace Vera

#endif // TOKENS_H_INCLUDED
