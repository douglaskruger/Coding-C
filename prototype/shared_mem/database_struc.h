/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
// *****************************************************************************
// Description:
//   This is the database definition header file for the real time database 
//   engine for the Multi String Controller
// *****************************************************************************

//  Choice
typedef struct choice
{
    char   tag[25];
    int    value;
} choice_alias;

//  Device Information
typedef struct device
{
    char   tag[25];
    int    device_type;
    int    device_address;
    char   software_ver[25];
    char   software_update[25];
    char   config_ver[25];
    char   config_update[25];
} device_alias;
     

// Analog Input
typedef struct analog_in
{
    char   tag[25];
    int    input_type;
    int    input_address;
    double value;
    double low_limit;
    double high_limit;
    double critical_limit;
} analog_in_alias;
    
