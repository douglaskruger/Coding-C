/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: serial_modbus_humidity.c $";

/* =============================================================================
   Description:
    Code based on
    https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c

   **** NOTE: IMPORTANT  ****
   the ASAIR AF5485 humidity sensor FAILS to calculate the correct CRC16 for more than
   0x16 registers even though it will return all 0x1f registers. As a result, if you
   want a correct CRC16 from the device, you must request < 0x16 registers in the
   read 03 opcode.
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

#define TERMINAL    "/dev/ttyUSB2"
#define BAUDRATE    9600
#define BBAUDRATE   B9600
#define REG(X) (buf[1+2*X] * 256 + buf[2+2*X])
#define FLOATREG(X) ((float)(buf[1+2*X] * 256 + buf[2+2*X])/10.0)
#define LOW_REG(X) (buf[2+2*X])

typedef union CRC16
{
    unsigned char  val_uchar[2];
    unsigned short val_uint16;
} tuCRC16;

// Declare the local functions
unsigned short crc16(unsigned char *ptr, unsigned char len);
int set_interface_attribs(int fd, int speed);
void decode_msg(unsigned char * buf, int buf_len);

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

    tty.c_cflag |= (CLOCAL | CREAD);    // ignore modem controls
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         // 8-bit characters
    tty.c_cflag &= ~PARENB;     // no parity bit
    tty.c_cflag &= ~CSTOPB;     // only need 1 stop bit
    tty.c_cflag &= ~CRTSCTS;    // no hardware flowcontrol

    // setup for non-canonical mode
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    // fetch bytes as they become available
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

void
decode_msg(unsigned char * buf, int buf_len)
{
    if (buf_len < 0x1f)
        return;

    printf("Humidity and Temperature Sensor Data Decoded\n");
    printf("  Humidity:                         %.1f %%\n", FLOATREG(0x01));
    printf("  Temperature:                      %.1f C\n", FLOATREG(0x02));
    printf("  Reserved:                         %u\n", REG(0x03));
    printf("  Reserved:                         %u\n", REG(0x04));
    printf("  Reserved:                         %u\n", REG(0x05));
    printf("  Reserved:                         %u\n", REG(0x06));
    printf("  Reserved:                         %u\n", REG(0x07));
    printf("  DeviceType:                       %u\n", REG(0x08));
    printf("  Version:                          %u\n", LOW_REG(0x09));
    printf("  DeviceId_H:                       %u\n", REG(0x0a));
    printf("  DeviceId_L:                       %u\n", REG(0x0b));
    printf("  Temp Upper Alarm Limit:           %.1f C\n", FLOATREG(0x0c));
    printf("  Enabled Temp Upper Alarm Limit:   %.1f C\n", FLOATREG(0x0d));
    printf("  Temp Lower Alarm Limit:           %.1f C\n", FLOATREG(0x0e));
    printf("  Enabled Temp Lower Alarm Limit:   %.1f C\n", FLOATREG(0x0f));
    printf("  Humid Upper Alarm Limit:          %.1f %%\n", FLOATREG(0x10));
    printf("  Enabled Humid Upper Alarm Limit:  %.1f %%\n", FLOATREG(0x11));
    printf("  Humid Lower Alarm Limit:          %.1f %%\n", FLOATREG(0x12));
    printf("  Enabled Humid Lower Alarm Limit:  %.1f %%\n", FLOATREG(0x13));
    printf("  Reserved:                         %u\n", REG(0x14));
    printf("  Reserved:                         %u\n", REG(0x15));
    printf("  Reserved:                         %u\n", REG(0x16));
    printf("  Reserved:                         %u\n", REG(0x17));
    printf("  Reserved:                         %u\n", REG(0x18));
    printf("  Reserved:                         %u\n", REG(0x19));
    printf("  Reserved:                         %u\n", REG(0x1a));
    printf("  Reserved:                         %u\n", REG(0x1b));
    printf("  Reserved:                         %u\n", REG(0x1c));
    printf("  Temperature Correction:           %.1f C\n", FLOATREG(0x1d));
    printf("  Humid Correction:                 %.1f %%\n", FLOATREG(0x1e));
    printf("  Reserved:                         %u\n", REG(0x1f));
    printf("\n");
}

int main(int argC, char *argV[])
{
    char *portname = TERMINAL;
    unsigned char msg[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00};
    int xlen = 8;

    // Check for input parameters
    if (argC > 1)
    {
        if ((strcmp(argV[1], "?") == 0) || (strcmp(argV[1], "-?") == 0))
        {
            printf("serial_modbus_humidity {device}\nDefault: %s\n", portname);
            printf("This program uses baudrate 9600,8,No parity\n");
            printf("and modbus address %u\n", msg[0]);
            exit(1);
        }
        portname = argV[1];
    }

    int fd = open(portname, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
        printf("Error opening %s: %s. Try 'sudo' for permission errors.\n", portname, strerror(errno));
        return -1;
    }

    // Print info once.
    printf("\nDevice:%s Baudrate: %u Device Address: %u\n\n", portname, BAUDRATE, msg[0]);
    set_interface_attribs(fd, BBAUDRATE);

    // Request various number of registers
    for (int num_reg = 0; num_reg< 0x20; num_reg++)
    {
        // Set the number of registers to retrieve
        msg[5]=num_reg;

        // Calculate the CRC16 for the message
        tuCRC16 my_crc;
        my_crc.val_uint16  = crc16(msg, 6);
        // Swap the crc for the message
        msg[6] = my_crc.val_uchar[0];
        msg[7] = my_crc.val_uchar[1];

        // Print the message to the screen
        printf("*** Requested Registers: %u ***\n", num_reg);
        printf("Write %d bytes:", xlen);
        for (int i= 0; i< xlen; i++)
        {
            printf(" (0x%02x)", msg[i]);
        }
        printf("\n");

        // Write the message to the port
        int wlen = write(fd, &msg, xlen);
        if (wlen != xlen) {
            printf("Error from write: %d, %d\n", wlen, errno);
        }
        tcdrain(fd);    // delay for output

        // Sleep after we send the message to allow the device to process and response
        // Allow for 200 characters
        int sleep_msg = 2000 * 1000000 / BAUDRATE;
        usleep(sleep_msg);

        // simple noncanonical input
        int count=0;
        do {
            unsigned char buf[256];
            int rdlen;

            rdlen = read(fd, buf, sizeof(buf) - 1);
            if (rdlen > 0)
            {
                // Print Message
                int rdlen2=rdlen;
                printf("Read %d bytes:", rdlen);
                for (unsigned char *p = buf; rdlen2-- > 0; p++)
                    printf(" (0x%02x)", *p);
                printf("\n");

                // Print the CRC (calculated and received)
                my_crc.val_uint16  = crc16(buf, rdlen-2);
                printf("%s CRC    ReceiveMsg=<0x%0x><0x%0x> Calculated:<0x%0x><0x%0x> for %u bytes\n\n",
                    ((buf[rdlen-2]!=my_crc.val_uchar[0]) || (buf[rdlen-1]!=my_crc.val_uchar[1])) == 1 ? "Invalid" : "Valid",
                    buf[rdlen-2], buf[rdlen-1], my_crc.val_uchar[0], my_crc.val_uchar[1], rdlen-2);

                // Decode the message
                decode_msg(buf, rdlen);
            }
            // repeat read to get full message
        } while (count++ < 500);
        usleep(25000);
    }
}
