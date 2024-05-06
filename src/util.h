#pragma once

#include <cstdio>
#include <string>
#include <sstream>
#include <array>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

#include "device.h"
#include "banner.h"

std::string exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}

void parseDevices(const std::string& result, std::vector<Device>& devices) {
    devices.clear();
    devices.push_back(Device{"\033[1mIP ADDRESS\033[0m", " \033[1mMAC ADDRESS\033[0m", false});

    std::istringstream iss(result);
    std::string line;
    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::string ip, mac;

        if (lineStream >> ip >> mac) {
            Device device{ip, mac, true};
            if (device.validIP()) {
                devices.push_back(device);
            }
        }
    }
}

void sortDevices(std::vector<Device>& devices) {
    std::sort(devices.begin() + 1, devices.end(), [](const Device& a, const Device& b) {
        return a.getIPasInt() < b.getIPasInt();
    });
}

void clearScreen() {
    std::cerr << "\033[2J\033[1;1H" << banner << "\n\tMade by Leah Johnson & Jack Williamson\n\n";
}