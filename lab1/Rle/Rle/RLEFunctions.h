#pragma once
#include "ParseComandLine.h"
#include <string>
#include <fstream>

bool RLEEncoding(const std::string& inputFileName, const std::string& outputFileName);

bool RLEDecoding(const std::string& inputFileName, const std::string& outputFileName);
