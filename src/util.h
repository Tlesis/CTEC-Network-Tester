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

// Source: https://stackoverflow.com/a/478960/16902023
/** executes a terminal command and returns the output as a string
 * @param cmd the command to execute
 * @return the output of the command as a string
 */
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

/**
 * parses the result of the `arp-scan` command and stores the devices in the `devices` vector
 * @param result the result of the `arp-scan` command
 * @param devices the vector to store the devices in
*/
void parseDevices(const std::string& result, std::vector<Device>& devices) {
    // make sure the devices vector is empty
    devices.clear();

    // add the header
    devices.push_back(Device{"\033[1mIP ADDRESS\033[0m", " \033[1mMAC ADDRESS\033[0m", false});

    // parse the result
    std::istringstream iss(result);
    std::string line;
    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::string ip, mac;

        if (lineStream >> ip >> mac) {
            Device device{ip, mac, true};
            // if the IP is valid, add it to the list otherwise ignore it
            if (device.validIP()) {
                devices.push_back(device);
            }
        }
    }
}

/**
 * sorts the devices by their IP address
 * @param devices the list of devices to sort
*/
void sortDevices(std::vector<Device>& devices) {
    std::sort(devices.begin() + 1, devices.end(), [](const Device& a, const Device& b) {
        return a.asInt() < b.asInt();
    });
}

/** helper function that clears the screen with ANSI text codes
 * then prints out the banner and our names :) */
void clearScreen() {
    std::cerr
        << "\033[2J\033[1;1H"
        << banner
        << "\n\tMade by Leah Johnson & Jack Williamson (2024)\n\n";
}