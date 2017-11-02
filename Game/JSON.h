#pragma once


#include <json/json.h>
#include <string>

std::string file_get_contents( const char *path );
Json::Value JSONparse(std::string json);


