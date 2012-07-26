//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "Tokens.h"
#include "file.hpp"
#include <boost/wave.hpp>
#include <boost/wave/cpplexer/cpp_lex_token.hpp>
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>
#include <boost/wave/cpplexer/cpplexer_exceptions.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <cctype>

namespace Vera
{

std::vector<std::string> TokenRef::physicalTokens;

TokenRef::TokenRef(boost::wave::token_id id, int line, int column, int length) :
        id_(id), line_(line), column_(column), length_(length), index_(-1)
{
}

TokenRef::TokenRef(boost::wave::token_id id,
            int line, int column, int length, const std::string& value) :
        id_(id), line_(line), column_(column), length_(length)
{
    // newline is optimized as the most common case
    if (id_ != boost::wave::T_NEWLINE)
    {
        // value of the token is stored in physicalTokens collection
        // (because it has no physical representation in the source code)
        index_ = static_cast<int>(physicalTokens.size());
        physicalTokens.push_back(value);
    }
}

std::string TokenRef::name() const
{
    std::string tokenName = boost::wave::get_token_name(id_).c_str();
    boost::algorithm::to_lower(tokenName);
    return tokenName;
}

std::string TokenRef::value(const vera::file& file) const
{
    if (id_ == boost::wave::T_EOF)
        return std::string();

    if (id_ == boost::wave::T_NEWLINE)
        return "\n";

    if (index_ >= 0)
    {
        // token value stored in the physicalTokens structure
        // (this is used with line continuation and other cases
        // where the token has no representation in physical lines)
        return physicalTokens[static_cast<size_t>(index_)];
    }
    else
    {
        // token value has to be retrieved from the physical line collection
        return file.get_line(line_).substr(column_, length_);
    }
}

} // namespace Vera
