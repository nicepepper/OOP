#pragma once
#include "GeometricFigures.h"
#include <memory>
#include <optional>
#include <string>

std::optional<std::shared_ptr<IShape>> CreateShape(const std::string& shapeDescription);
