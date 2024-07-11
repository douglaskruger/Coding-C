#include <stdio.h>
#include <stdlib.h>
#include <modbus.h>

#define NUM_REGISTERS 10
#define NUM_COILS 10

// Function to read holding registers
void read_registers(modbus_t *ctx) {
    uint16_t tab_reg[32];
    int rc;
    int i;
    
    // Read 10 registers starting from address 0
    rc = modbus_read_registers(ctx, 0, NUM_REGISTERS, tab_reg);
    if (rc == -1) {
        fprintf(stderr, "Reading registers failed: %s\n", modbus_strerror(errno));
        return;
    }

    // Print the values of the registers
    for (i = 0; i < rc; i++) {
        printf("Register %d: %d\n", i, tab_reg[i]);
    }
}

// Function to write a value to a holding register
void write_register(modbus_t *ctx) {
    int addr, value;
    printf("Enter register address: ");
    scanf("%d", &addr);
    printf("Enter value to write: ");
    scanf("%d", &value);

    if (modbus_write_register(ctx, addr, value) == -1) {
        fprintf(stderr, "Writing register failed: %s\n", modbus_strerror(errno));
    } else {
        printf("Successfully wrote %d to register %d\n", value, addr);
    }
}

// Function to read coils
void read_coils(modbus_t *ctx) {
    uint8_t tab_coils[32];
    int rc;
    int i;
    
    // Read 10 coils starting from address 0
    rc = modbus_read_bits(ctx, 0, NUM_COILS, tab_coils);
    if (rc == -1) {
        fprintf(stderr, "Reading coils failed: %s\n", modbus_strerror(errno));
        return;
    }

    // Print the values of the coils
    for (i = 0; i < rc; i++) {
        printf("Coil %d: %d\n", i, tab_coils[i]);
    }
}

// Function to write a value to a coil
void write_coil(modbus_t *ctx) {
    int addr, value;
    printf("Enter coil address: ");
    scanf("%d", &addr);
    printf("Enter value to write (0 or 1): ");
    scanf("%d", &value);

    if (value != 0 && value != 1) {
        fprintf(stderr, "Invalid value for coil. Must be 0 or 1.\n");
        return;
    }

    if (modbus_write_bit(ctx, addr, value) == -1) {
        fprintf(stderr, "Writing coil failed: %s\n", modbus_strerror(errno));
    } else {
        printf("Successfully wrote %d to coil %d\n", value, addr);
    }
}

// Function to read discrete inputs
void read_discrete_inputs(modbus_t *ctx) {
    uint8_t tab_inputs[32];
    int rc;
    int i;

    // Read 10 discrete inputs starting from address 0
    rc = modbus_read_input_bits(ctx, 0, NUM_COILS, tab_inputs);
    if (rc == -1) {
        fprintf(stderr, "Reading discrete inputs failed: %s\n", modbus_strerror(errno));
        return;
    }

    // Print the values of the inputs
    for (i = 0; i < rc; i++) {
        printf("Discrete input %d: %d\n", i, tab_inputs[i]);
    }
}

// Function to read input registers
void read_input_registers(modbus_t *ctx) {
    uint16_t tab_input_regs[32];
    int rc;
    int i;

    // Read 10 input registers starting from address 0
    rc = modbus_read_input_registers(ctx, 0, NUM_REGISTERS, tab_input_regs);
    if (rc == -1) {
        fprintf(stderr, "Reading input registers failed: %s\n", modbus_strerror(errno));
        return;
    }

    // Print the values of the input registers
    for (i = 0; i < rc; i++) {
        printf("Input register %d: %d\n", i, tab_input_regs[i]);
    }
}

// Function to write multiple registers
void write_multiple_registers(modbus_t *ctx) {
    int addr, num;
    printf("Enter starting register address: ");
    scanf("%d", &addr);
    printf("Enter number of registers to write: ");
    scanf("%d", &num);

    uint16_t values[num];
    for (int i = 0; i < num; i++) {
        printf("Enter value for register %d: ", addr + i);
        scanf("%hu", &values[i]);
    }

    if (modbus_write_registers(ctx, addr, num, values) == -1) {
        fprintf(stderr, "Writing multiple registers failed: %s\n", modbus_strerror(errno));
    } else {
        printf("Successfully wrote %d registers starting from %d\n", num, addr);
    }
}

// Function to write multiple coils
void write_multiple_coils(modbus_t *ctx) {
    int addr, num;
    printf("Enter starting coil address: ");
    scanf("%d", &addr);
    printf("Enter number of coils to write: ");
    scanf("%d", &num);

    uint8_t values[num];
    for (int i = 0; i < num; i++) {
        printf("Enter value for coil %d (0 or 1): ", addr + i);
        scanf("%hhu", &values[i]);
    }

    if (modbus_write_bits(ctx, addr, num, values) == -1) {
        fprintf(stderr, "Writing multiple coils failed: %s\n", modbus_strerror(errno));
    } else {
        printf("Successfully wrote %d coils starting from %d\n", num, addr);
    }
}

// Function to read exception status (function code 7)
void read_exception_status(modbus_t *ctx) {
    uint8_t status;
    if (modbus_report_slave_id(ctx, &status) == -1) {
        fprintf(stderr, "Reading exception status failed: %s\n", modbus_strerror(errno));
    } else {
        printf("Exception status: 0x%X\n", status);
    }
}

// Function to run diagnostics (function code 8)
void run_diagnostics(modbus_t *ctx) {
    uint16_t diag_code, data;
    printf("Enter diagnostics sub-function code: ");
    scanf("%hu", &diag_code);
    printf("Enter data to send: ");
    scanf("%hu", &data);

    uint16_t tab_rq_data[2] = {diag_code, data};
    uint16_t tab_rsp_data[2];

    if (modbus_send_raw_request(ctx, (uint8_t *)tab_rq_data, sizeof(tab_rq_data)) == -1 ||
        modbus_receive_confirmation(ctx, (uint8_t *)tab_rsp_data) == -1) {
        fprintf(stderr, "Diagnostics failed: %s\n", modbus_strerror(errno));
    } else {
        printf("Diagnostics response: %d %d\n", tab_rsp_data[0], tab_rsp_data[1]);
    }
}

// Function to get comm event counter (function code 11)
void get_comm_event_counter(modbus_t *ctx) {
    uint16_t status[2];
    if (modbus_get_comm_event_counter(ctx, status) == -1) {
        fprintf(stderr, "Getting comm event counter failed: %s\n", modbus_strerror(errno));
    } else {
        printf("Status: 0x%X, Event Count: %d\n", status[0], status[1]);
    }
}

// Function to get comm event log (function code 12)
void get_comm_event_log(modbus_t *ctx) {
    uint8_t status[256];
    int rc = modbus_get_comm_event_log(ctx, status);
    if (rc == -1) {
        fprintf(stderr, "Getting comm event log failed: %s\n", modbus_strerror(errno));
    } else {
        printf("Comm Event Log: ");
        for (int i = 0; i < rc; i++) {
            printf("0x%X ", status[i]);
        }
        printf("\n");
    }
}

// Function to report server ID (function code 17)
void report_server_id(modbus_t *ctx) {
    uint8_t server_id[256];
    int rc = modbus_report_slave_id(ctx, server_id);
    if (rc == -1) {
        fprintf(stderr, "Reporting server ID failed: %s\n", modbus_strerror(errno));
    } else {
        printf("Server ID: ");
        for (int i = 0; i < rc; i++) {
            printf("0x%X ", server_id[i]);
        }
        printf("\n");
    }
}

int main() {
    modbus_t *ctx;
    int choice;

    // Create a new Modbus TCP context
    ctx = modbus_new_tcp("127.0.0.1", 502);
    if (ctx == NULL) {
        fprintf(stderr, "Unable to allocate libmodbus context\n");
        return -1;
    }

    // Connect to the Modbus server
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    do {
        printf("\nModbus Client Menu\n");
        printf("1. Read Registers\n");
        printf("2. Write Register\n");
        printf("3. Read Coils\n");
        printf("4. Write Coil\n");
        printf("5. Read Discrete Inputs\n");
        printf("6. Read Input Registers\n");
        printf("7. Write Multiple Registers\n");
        printf("8. Write Multiple Coils\n");
        printf("9. Read Exception Status\n");
        printf("10. Run Diagnostics\n");
        printf("11. Get Comm Event Counter\n");
        printf("12. Get Comm Event Log\n");
        printf("13. Report Server ID\n");
        printf("14. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                read_registers(ctx);
                break;
            case 2:
                write_register(ctx);
                break;
            case 3:
                read_coils(ctx);
                break;
            case 4:
                write_coil(ctx);
                break;
            case 5:
                read_discrete_inputs(ctx);
                break;
            case 6:
                read_input_registers(ctx);
                break;
            case 7:
                write_multiple_registers(ctx);
                break;
            case 8:
                write_multiple_coils(ctx);
                break;
            case 9:
                read_exception_status(ctx);
                break;
            case 10:
                run_diagnostics(ctx);
                break;
            case 11:
                get_comm_event_counter(ctx);
                break;
            case 12:
                get_comm_event_log(ctx);
                break;
            case 13:
                report_server_id(ctx);
                break;
            case 14:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 14);

    // Close the connection and free the context
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
