#include "util.h"
#include "device.h"

int main() {
    // the list of devices on the network
    std::vector<Device> devices;

    // debug statment that the program is starting
    std::cout << "Network Scanner Starting...\n";

    // write to output
    while (true) {
        // run and get the result of the `arp-scan` command
        std::string result = exec("sudo arp-scan -xq 192.168.1.0/24");
        parseDevices(result, devices);  /** @see util.h */
        sortDevices(devices);           /** @see util.h */

        // clear the screen and print the devices
        clearScreen();
        for (const auto& device : devices) {
            std::cout << device << '\n';
        }
    }
}