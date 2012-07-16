//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "structures/SourceFiles.h"
#include "plugins/Profiles.h"
#include "plugins/Rules.h"
#include "plugins/Exclusions.h"
#include "plugins/Transformations.h"
#include "plugins/Parameters.h"
#include "plugins/Reports.h"
#include "plugins/RootDirectory.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

static const char *programVersion = "Vera++ 1.1.1 (Community Edition)";

// helper function that checks whether the given file name names the C or C++ source file
static bool isSourceFileName(const Vera::Structures::SourceFiles::FileName& name)
{
	const std::string suffixes[] =
        { ".cpp", ".cxx", ".cc", ".c", ".C", ".h", ".hh", ".hpp", ".hxx", ".ipp" };

	const int numOfSuffixes = sizeof(suffixes) / sizeof(std::string);
    for (int i = 0; i != numOfSuffixes; ++i)
    {
		const std::string suf = suffixes[i];
        const Vera::Structures::SourceFiles::FileName::size_type pos = name.rfind(suf);

        if (pos != Vera::Structures::SourceFiles::FileName::npos &&
            pos == name.size() - suf.size())
        {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[])
{
    int exitCodeOnFailure = EXIT_FAILURE;

    try
    {
		Vera::Plugins::Profiles::ProfileName profile("default");

        // the directory containing the profile and rule definitions
        // by default it is (in this order, first has highest precedence):
        // - VERA_ROOT (if VERA_ROOT is defined)
        // - HOME/.vera (if HOME is defined)
        // - current directory

		Vera::Plugins::RootDirectory::DirectoryName veraRoot(".");
        char * veraRootEnv = getenv("HOME");
        if (veraRootEnv != NULL)
        {
            veraRoot = veraRootEnv;
            veraRoot += "/.vera++";
        }
        veraRootEnv = getenv("VERA_ROOT");
        if (veraRootEnv != NULL)
        {
            veraRoot = veraRootEnv;
        }

        Vera::Plugins::RootDirectory::setRootDirectory(veraRoot);

        // collect all source file names and interpret options

        Vera::Plugins::Rules::RuleName singleRule;
        Vera::Plugins::Transformations::TransformationName singleTransformation;

        bool omitDuplicates = false;

        int i = 1;
        while (i != argc)
        {
			const std::string arg(argv[i]);

            if (arg == "-help")
            {
				std::cout << "vera++ [options] [list-of-files]\n\n"
                    "Recognized options:\n\n"
                    "-                  (a single minus sign) indicates that the list of\n"
                    "                   source file names will be provided on the stdin.\n\n"
                    "-exclusions file   read exclusions from file\n\n"
                    "-help              print this message\n\n"
                    "-nofail            do not fail even when finding rule violations\n\n"
                    "-nodup             do not duplicate messages if a single rule is violated\n"
                    "                   many times in a single line of code\n\n"
                    "-profile name      execute all rules from the given profile\n\n"
                    "-param name=value  provide parameters to scripts (can be used many times)\n\n"
                    "-paramfile file    read parameters from file\n\n"
                    "-rule name         execute the given rule\n"
                    "                   (note: the .tcl extension is added automatically)\n\n"
                    "-showrules         include rule name in each report\n\n"
                    "-transform name    execute the given transformation\n\n"
                    "-version           print version number\n\n";
                exit(EXIT_SUCCESS);
            }
            else if (arg == "-version")
            {
				std::cout << programVersion << '\n';
                exit(EXIT_SUCCESS);
            }
            else if (arg == "-nofail")
            {
                exitCodeOnFailure = EXIT_SUCCESS;
            }
            else if (arg == "-nodup")
            {
                omitDuplicates = true;
            }
            else if (arg == "-")
            {
                // list of source files is provided on stdin
				Vera::Structures::SourceFiles::FileName name;
				while (std::cin >> name)
                {
					Vera::Structures::SourceFiles::addFileName(name);
                }
            }
            else if (arg == "-showrules")
            {
				Vera::Plugins::Reports::setShowRules(true);
            }
            else if (arg == "-rule")
            {
                ++i;
                if (argv[i] != NULL)
                {
                    singleRule = argv[i];
                }
                else
                {
					std::cerr << "error: option -rule provided with no rule name\n";
                    exit(exitCodeOnFailure);
                }
            }
            else if (arg == "-profile")
            {
                ++i;
                if (argv[i] != NULL)
                {
                    profile = argv[i];
                }
                else
                {
					std::cerr << "error: option -profile provided with no profile name\n";
                    exit(exitCodeOnFailure);
                }
            }
            else if (arg == "-exclusions")
            {
                ++i;
                if (argv[i] != NULL)
                {
					Vera::Plugins::Exclusions::ExclusionFileName file(argv[i]);
                    Vera::Plugins::Exclusions::setExclusions(file);
                }
                else
                {
					std::cerr << "error: option -exclusions provided without name of file\n";
                    exit(exitCodeOnFailure);
                }
            }
            else if (arg == "-param")
            {
                ++i;
                if (argv[i] != NULL)
                {
					Vera::Plugins::Parameters::ParamAssoc assoc(argv[i]);
                    Vera::Plugins::Parameters::set(assoc);
                }
                else
                {
					std::cerr << "error: option -param provided without name and value\n";
                    exit(exitCodeOnFailure);
                }
            }
            else if (arg == "-paramfile")
            {
                ++i;
                if (argv[i] != NULL)
                {
                    Vera::Plugins::Parameters::FileName file(argv[i]);
                    Vera::Plugins::Parameters::readFromFile(file);
                }
                else
                {
					std::cerr << "error: option -paramfile provided without name of file\n";
                    exit(exitCodeOnFailure);
                }
            }
            else if (arg == "-transform")
            {
                ++i;
                if (argv[i] != NULL)
                {
                    singleTransformation = argv[i];
                }
                else
                {
					std::cerr << "error: option -transform provided without name of transformation\n";
                    exit(exitCodeOnFailure);
                }
            }
            else if (isSourceFileName(arg))
            {
				Vera::Structures::SourceFiles::addFileName(arg);
            }
            else
            {
                // the option was not recognized as a name of the source file
                // or a vera-specific option

				std::cerr << "error: option " << arg << " not recognized\n";
            }

            ++i;
        }

		if (Vera::Structures::SourceFiles::empty())
        {
			std::cerr << "vera++: no input files\n";
            exit(exitCodeOnFailure);
        }

        if (singleTransformation.empty() == false)
        {
            if (singleRule.empty() == false || profile != "default")
            {
				std::cerr <<
                    "error: transformation cannot be specified together with rules or profiles\n";
                exit(exitCodeOnFailure);
            }

            Vera::Plugins::Transformations::executeTransformation(singleTransformation);
        }
        else if (singleRule.empty() == false)
        {
            // single rule requested
            Vera::Plugins::Rules::executeRule(singleRule);
        }
        else
        {
            Vera::Plugins::Profiles::executeProfile(profile);
        }

		Vera::Plugins::Reports::dumpAll(std::cerr, omitDuplicates);
    }
	catch (const std::exception& e)
    {
		std::cerr << "error: " << e.what() << '\n';
        exit(exitCodeOnFailure);
    }
}
