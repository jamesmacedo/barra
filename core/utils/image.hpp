#pragma once
#include <cstdint>
#include <tuple>
#include <string>

using namespace std;

tuple<double, double, double> rgb_to_cairo(uint8_t r, uint8_t g, uint8_t b);
tuple<uint8_t, uint8_t, uint8_t> load_image(const string& image);
