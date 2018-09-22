#include "run.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{

    std::vector<std::string> fnames;
    const std::string default_fname("settings.json");
    for (size_t i(1); i < argc; ++i)
        fnames.push_back((std::string)argv[i]);

    if (!fnames.size()) {
        std::cerr << "Usage: " << argv[0] << " settings_fname1.json"
                  << " settings_fname2.json ..." << std::endl;
        std::cerr << "No settings file name provided, trying default: " << default_fname << "\n\n";
        fnames.push_back(default_fname);
    }

    try {
        for (const auto& fname : fnames)
            csmp::tperm::run(fname.c_str());
    } catch (std::exception& e) {
        std::cout << "\nException raised: " << e.what() << "\n\n";
    }
    return 0;
}
