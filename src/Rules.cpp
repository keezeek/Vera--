//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "Rules.h"
#include "RootDirectory.h"
#include "Interpreter.h"

namespace Vera
{

static Rules::RuleName currentRule_;

void Rules::executeRule(const RuleName& name)
{
    currentRule_ = name;

    const RootDirectory::DirectoryName veraRoot = RootDirectory::getRootDirectory();
    Interpreter::execute(veraRoot, Interpreter::rule, name);
}

Rules::RuleName Rules::getCurrentRule()
{
    return currentRule_;
}

} // namespace Vera
