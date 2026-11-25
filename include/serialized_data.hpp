#pragma once

#ifndef SERIALIZED_DATA_H
#define SERIALIZED_DATA_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdint> // для uint8_t
#include <algorithm> // для copy_n
#include <unordered_map>

class Data
{
public:
    Data(const std::string& line, const std::string& color)
        : line_(line)
        , color_(StringToColor(color))
    {}

    std::vector<uint8_t> Serialize() const
    {
        std::vector<uint8_t> data(sizeof(size_t) + sizeof(color_) + line_.size());
        size_t len = line_.size();
        std::copy_n(&len, 1, data.begin());
        std::copy_n(&color_, 1, data.begin() + sizeof(len));
        std::copy(line_.begin(), line_.end(), data.begin() + sizeof(color_) + sizeof(len));
        return data;
    }

    static Data Deserialize(const std::vector<uint8_t>& data)
    {
        const size_t len = *reinterpret_cast<const size_t*>(data.data());
        const int color = *reinterpret_cast<const int*>(data.data() + sizeof(len));
        std::string line(reinterpret_cast<const char*>(data.data() + sizeof(len) + sizeof(color)), len);
        return Data(line, color);
    }

    friend std::ostream& operator<<(std::ostream& stream, const Data& data)
    {
        return stream << "\033[" << data.color_ << "m" << data.line_ << "\033[0m";
    }

private:
    Data(const std::string& line, int color)
        : line_(line)
        , color_(color)
    {}

    int StringToColor(const std::string& str)
    {
        std::unordered_map<std::string, int> colors = {
            { "default", 0 },
            { "black", 30 },
            { "red", 91 },
            { "green", 92 },
            { "yellow", 93 },
            { "blue", 94 },
            { "white", 97 },
        };
        return colors.at(str);
    }

private:
    std::string line_;
    int color_;
};

#endif // SERIALIZED_DATA_H