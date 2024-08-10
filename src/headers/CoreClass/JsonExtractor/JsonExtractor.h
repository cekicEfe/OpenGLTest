#ifndef JSONEXTRACTOR_H
#define JSONEXTRACTOR_H

#include <json/json.hpp>
#include <CoreClass/CoreClass.h>
#include <string>
#include <iostream>
#include <fstream>

namespace core
{
    class JsonExtractor
    {
    protected:
        static nlohmann::json *loadJsonFromPath(std::string path);

        friend class core::MainHandler;
    };
}

#endif