#ifndef JSONEXTRACTOR_H
#define JSONEXTRACTOR_H

#include <json/json.hpp>
#include <CoreClass/CoreClassPreDec.h>
#include <string>
#include <iostream>
#include <fstream>

namespace core
{
    class JsonExtractor
    {
    public:
        static nlohmann::json *loadJsonFromPath(std::string path);

        friend class core::MainHandler;
        friend class core::SaveLoadHandler;
    };
}

#endif