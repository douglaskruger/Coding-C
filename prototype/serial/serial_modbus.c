/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: serial_modbus.c $";

/* =============================================================================
   Description:
    Code based on
    https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
   ============================================================================= */

/* =============================================================================
                                 System Includes
   ============================================================================= */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define TERMINAL    "/dev/ttyUSB0"
#define BAUDRATE    B115200

typedef union CRC16
{
    unsigned char  val_uchar[2];
    unsigned short val_uint16;
} tuCRC16;

unsigned short crc16(unsigned char *ptr, unsigned char len)
{
    unsigned short crc=0xFFFF;
    unsigned char i;

    while(len--)
    {
        crc ^=*ptr++;
        for(i=0;i<8;i++)
        {
            if(crc & 0x01)
            {
                crc>>=1;
                crc^=0xA001;
            }
            else
            {
                crc>>=1;
            }
        }
    }
    return crc;
}

int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

int main(int argC, char *argV[])
{
    char *portname = TERMINAL;
    unsigned char msg[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xc4, 0x0b, 0xff, 0xff };
    int xlen = 12;

    // Check for input parameters
    if (argC > 1)
    {
        if ((strcmp(argV[1], "?") == 0) || (strcmp(argV[1], "-?") == 0))
        {
            printf("serial_modbus {device}\nDefault: %s\n", portname);
            printf("This program cycles through baudrates 300-115200\n");
            printf("and modbus adddresses through 0-255\n");
            exit(1);
        }
        portname = argV[1];
    }
        
    int fd = open(portname, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
        printf("Error opening %s: %s. Please try 'sudo' for permission issues.\n", portname, strerror(errno));
        return -1;
    }
    int baud;

    // Walk through the various baud rates
    for (int index = 0; index < 8; index++)
    {
        /* 8 bits, no parity, 1 stop bit */
        switch (index)
        {
            case 0:
                baud = 115200;
                set_interface_attribs(fd, B115200);
                break;

            case 1:
                baud = 57600;
                set_interface_attribs(fd, B57600);
                break;

            case 2:
                baud = 38400;
                set_interface_attribs(fd, B38400);
                break;

            case 3:
                baud = 19200;
                set_interface_attribs(fd, B19200);
                break;

            case 4:
                baud = 9600;
                set_interface_attribs(fd, B9600);
                break;

            case 5:
                baud = 4800;
                set_interface_attribs(fd, B4800);
                break;

            case 6:
                baud = 2400;
                set_interface_attribs(fd, B2400);
                break;

            case 7:
                baud = 1200;
                set_interface_attribs(fd, B1200);
                break;

            default:
            case 8:
                baud = 300;
                set_interface_attribs(fd, B300);
                break;
        }

        // Walk through all the possible addresses
        for (unsigned char address = 0; address < 255; address++)
        {
            // walk through all addresses
            msg[0] = address;
            tuCRC16 my_crc;
            my_crc.val_uint16  = crc16(msg, 6);
            msg[6] = my_crc.val_uchar[0];
            msg[7] = my_crc.val_uchar[1];

            // Print the message to the screen
            printf("\nDevice:%s Baudrate: %u Device Address: %u\n\n", portname, baud, address);
            for (int i= 0; i< 8; i++)
            {
                printf("(0x%02x) ", msg[i]);
            }
            printf("\n");

            int wlen = write(fd, &msg, xlen);
            if (wlen != xlen) {
                printf("Error from write: %d, %d\n", wlen, errno);
            }
            if (tcdrain(fd) != 0)
                perror("tcdrain error");

            // Sleep after we send the message to allow the device to process and response
            // Allow for 50 characters
            int sleep_msg = 500 * 1000000 / baud;
            usleep(sleep_msg);

            /* simple noncanonical input */
            int loop=0;
            do {
                unsigned char buf[256];
                int rdlen;

                rdlen = read(fd, buf, sizeof(buf) - 1);
                if (rdlen > 0)
                {
                    printf("Reading Baud: %u Address: %3u Bytes:%u  ", baud, address, rdlen);
                    for (unsigned char *p = buf; rdlen-- > 0; p++)
                        printf(" (0x%02x)", *p);
                    printf("\n");
                } else if (rdlen < 0) {
                    //printf("Error from read: %d: %s\n", rdlen, strerror(errno));
                    break;
                } else {  // rdlen == 0
                    //printf("Timeout from read\n");
                    break;
                }
                /* repeat read to get full message */
            } while (loop++ < 500);

            // Sleep 5 characters between messages
            usleep(sleep_msg/10);
        }
    }
}
