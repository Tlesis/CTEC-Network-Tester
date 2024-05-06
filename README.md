# CTEC-Network-Tester
Code for a device used to connect to and troubleshoot network devices at CTEC. It reads and prints out the IPs and MAC addresses of all devices on the network, excluding those of the router and Raspberry Pi.

## Troubleshooting

### Reaching the Command Line

To reach the command line, connect a keyboard to one of the Raspberry Pi's USB ports. Then, type `sudo systemctl stop networkTester` and hit enter. You won't be able to see the text as you type, but the command will still work.

### Startup
A systemd service file is used for running the network tester program on startup. Its filepath is: 

`/etc/systemd/system/networkTester.service`

You can edit it by typing: 

`sudo nano /etc/systemd/system/networkTester.service` 

For info on how to use systemd, see [the docs](https://wiki.debian.org/systemd).

### The Program

The program is stored in `/home`. A `.sh` file is used to make the program easier to run, but the `networkTester.out` can also be run directly.

You can edit the code on the Pi directly with `nano`, but it's a lot easier to edit it on another computer. To do so, you'll need to transfer it to a flash drive. Plug a flash drive into one of the Pi's USB ports, then type: 

`sudo mount -t vfat /dev/sda1 /mnt/media/usbstick`

The USB stick should now be mounted, and its files can be accessed in the `/mnt/media/usbstick` directory. If that fails, change `sda1` to `sdb1`, then try `sdc1`, then `sdd1`, etc.
