//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/filesystem.hpp>

#include "Interpreter.h"
#include "globals.hpp"

namespace po = boost::program_options;

namespace vera
{

std::string profile;
boost::filesystem::path root_dir;
std::vector<std::string> input_files;
std::vector<problem> problems;

} // namespace vera

static std::vector<std::string> getListOfScriptNames(const std::string& profile)
{
    boost::filesystem::path fileName(vera::root_dir / "profiles" / profile);

    std::ifstream file(fileName.c_str());
    if (!file)
    {
        throw std::runtime_error(
                "cannot open profile description for profile " + profile);
    }

    std::vector<std::string> allRules;
    std::string line;
    while (file)
    {
        std::getline(file, line);
        boost::trim(line);

        if (!line.empty() && line[0] != '#')
        {
            allRules.push_back(line);
        }
    }

    return allRules;
}

int main(int argc, char* argv[])
{
//  bool nofail;
//  bool nodup;
//  bool msvc;
    int lOO = 100;

    int exit_failure = EXIT_FAILURE;

    po::options_description desc("Recognized options");
    desc.add_options()
        ("help", "print this message")
        ("version", "print version number")
        ("nofail", "do not fail even when finding rule violations")
        ("nodup", "do not duplicate messages if a single rule is violated")
        ("msvc", "show output compatible with Microsoft Visual Studio")
        ("profile", po::value<std::string>(&vera::profile)->default_value("default"), "execute all rules from the given profile")
        ("root-dir", po::value<boost::filesystem::path>(&vera::root_dir)->default_value("."), "the directory containing the profile and rule definitions")
        ;

    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("input-file", po::value<std::vector<std::string>>(&vera::input_files), "input file")
        ;

    po::positional_options_description positional;
    positional.add("input-file", -1);

    po::options_description options;
    options.add(desc).add(hidden);

    try
    {
        po::command_line_parser parser(argc, argv);
        parser.options(options);
        parser.positional(positional);

        po::variables_map vm;
        po::store(parser.run(), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout
                << "vera++ [options] [input-files]\n\n"
                << desc << '\n'
                ;
            return 0;
        }

      if( vm.count("version") )  {
            std::cout << "Vera++ 1.1.1 (Community Edition)\n";
            return 0;
        }

        if (vera::input_files.empty())
        {
            throw std::runtime_error("no input files");
        }

        BOOST_FOREACH(std::string & file, vera::input_files)
        {
            file = boost::filesystem::absolute(file).make_preferred().string();
        }

        BOOST_FOREACH(const std::string& script, getListOfScriptNames(vera::profile))
        {
            Vera::Interpreter::execute(script);
        }

        std::sort(vera::problems.begin(), vera::problems.end());

        BOOST_FOREACH(const vera::problem& p, vera::problems)
        {
            //std::cerr << p.file << ':' << p.line << ": " << p.msg << '\n';
            std::cerr
                << p.file
                << '(' << p.line << ") : "
                << p.msg << '\n'
                ;
        }
    }
    catch (const std::exception& except)
    {
        std::cerr << "error: " << except.what() << std::endl;
        return exit_failure;
    }
}
