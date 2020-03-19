#pragma once

#include "LabyrinthConfiguration.h"
#include <optional>

std::optional<LabyrinthInformation> InitializeLabyrinth(const std::string fileName);
