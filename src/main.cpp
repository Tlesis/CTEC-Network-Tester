#include "util.h"
#include "device.h"

int main() {
    std::vector<Device> devices;

    // clear screen
    std::cerr << "Network Scanner Starting...\n";

    // write to output
    while (true) {
        // "sudo arp-scan -xq 192.168.0.0/24"
        std::string result = exec("sudo arp-scan -xq 192.168.1.0/24");
        parseDevices(result, devices);
        sortDevices(devices);

        clearScreen();
        for (const auto& device : devices) {
            std::cerr << device << '\n';
        }
    }
}