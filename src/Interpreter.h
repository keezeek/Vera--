//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef INTERPRETER_H_INCLUDED
#  define INTERPRETER_H_INCLUDED

#include <stdexcept>

namespace Vera
{

struct Interpreter
{
    static void execute(const std::string& name);
};

} // namespace Vera

#endif // INTERPRETER_H_INCLUDED
