#pragma once

#include <iostream>
#include <string>
#include <sstream>

const std::string badIPs[] = {
    "192.168.1.1",
    "192.168.1.161"
};

struct Device {
    typedef unsigned int uint;

    std::string ip;
    std::string mac;
    bool valid;

    friend std::ostream& operator<<(std::ostream& os, const Device& device) {
        if (!device.valid) {
            os << device.ip << "\t" << device.mac;
            return os;
        } else {
            os << "\033[38;5;196m" << device.ip << "\033[0m\t" << device.mac;
            return os;
        }
    }

    bool operator==(const Device& other) const {
        return ip == other.ip && mac == other.mac;
    }

    bool validIP() const {
        for (const auto& badIP : badIPs) {
            if (ip == badIP) {
                return false;
            }
        }

        return true;
    }

    uint getIPasInt() const {
        int a, b, c, d;
        char ch;
        std::istringstream ss(ip);
        ss >> a >> ch >> b >> ch >> c >> ch >> d;
        return (a << 24) + (b << 16) + (c << 8) + d;
    }
};