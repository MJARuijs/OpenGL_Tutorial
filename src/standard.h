#pragma once

#include <array>
#include "graphics/objects/material/Color.h"

template<size_t size>
using ColorRow = std::array<Color, size>;

template<size_t size>
using ColorTable = std::array<ColorRow<size>, size>;