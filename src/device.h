#pragma once

#include <iostream>
#include <string>
#include <sstream>

/** List of "bad" IPs that should not be displayed */
const std::string badIPs[] = {
    "192.168.1.1",  // Router IP
    "192.168.1.161" // Raspberry Pi IP
};


struct Device {
    // i didnt want to type out `unsigned int` every time
    typedef unsigned int uint;

    std::string ip;
    std::string mac;
    /** used to determine if the device should be displayed with color */
    bool valid;

    /** checks the IP to make sure that it is not one of the `badIPs` */
    bool validIP() const {
        for (const auto& badIP : badIPs) {
            if (ip == badIP) return false;
        }
        return true;
    }

    /**
     * converts the ip string to its (unsigned) integer representation
     * used for sorting the devices by IP
     * @return the ip as an (unsigned) integer
     */
    uint asInt() const {
        int a, b, c, d;
        char ch;
        std::istringstream ss(ip);
        ss >> a >> ch >> b >> ch >> c >> ch >> d;
        return (a << 24) + (b << 16) + (c << 8) + d;
    }


    // Helper operators

    /** makes printing of the MAC and IP address easy to do */
    friend std::ostream& operator<<(std::ostream& os, const Device& device) {
        if (!device.valid) {
            os << device.ip << "\t" << device.mac;
            return os;
        } else {
            os << "\033[38;5;196m" << device.ip << "\033[0m\t" << device.mac;
            return os;
        }
    }

    /** used to compare two devices for sorting */
    bool operator==(const Device& other) const {
        return ip == other.ip && mac == other.mac;
    }
};