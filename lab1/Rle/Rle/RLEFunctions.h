#pragma once
#include "ParseComandLine.h"
#include <string>
#include <fstream>

bool IsSuccessfulEcoding(const std::string& inputFileName, const std::string& outputFileName);

bool IsSuccessfulDecoding(const std::string& inputFileName, const std::string& outputFileName);
