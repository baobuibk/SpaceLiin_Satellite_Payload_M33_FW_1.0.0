/************************************************
 *  @file     : cmdline.c
 *  @date     : October 2025
 *  @author   : CAO HIEU
 *  @version  : 1.0.0
 *-----------------------------------------------
 *  Description :
 *    [-]
 ************************************************/

#include "cmdline.h"
#include "fsl_debug_console.h"
#include <stdio.h>

/*External Include -----------------------------------------------------------*/
#include "Interface/SimpleShell/simple_shell.h"
#include "DateTime/date_time.h"

static void writeCharShell(char c)
{
    PUTCHAR(c); 
}
/*******************************************************************************
 * SimpleShell command
 ******************************************************************************/
static void CMD_a55_sleep(int argc, char *argv[]) 
{
    Shell_WriteString("A55 entering sleep mode...\r\n");
    /* Add code to put A55 into sleep mode here */
}

static void CMD_a55_wake(int argc, char *argv[]) 
{
    Shell_WriteString("A55 waking up from sleep mode...\r\n");
    MU1_MUA->GCR |= MU_GCR_GIR1_MASK;
}

static void CMD_cls(int argc, char *argv[]) 
{
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "\33[2J");
    Shell_WriteString(buffer);  
}

static void CMD_date(int argc, char *argv[])
{
    s_DateTime dt;
    Utils_GetRTC(&dt);
    Shell_WriteString("-> Current DateTime: ");
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%02u/%02u/20%02u %02u:%02u:%02u\r\n", dt.day, dt.month, dt.year, dt.hour, dt.minute, dt.second);
    Shell_WriteString(buffer);  

    uint8_t days;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    Utils_GetWorkingTime((uint32_t *)&days, &hours, &minutes, &seconds);
    Shell_WriteString("-> Up Time: ");
    snprintf(buffer, sizeof(buffer), "%u days, %02u:%02u:%02u\r\n", days, hours, minutes, seconds);
    Shell_WriteString(buffer);

}

static void CMD_hello(int argc, char *argv[])
{
    Shell_WriteString("Hello from i.MX93!\r\n");
}

void setup_dynamic_shell(void)
{   
    Shell_Init(writeCharShell);
    Shell_AddCommand("cls",             CMD_cls,            "Clear screen");
    Shell_AddCommand("hello",           CMD_hello,          "Print hello");
    Shell_AddCommand("date",            CMD_date,           "Print date time");
    Shell_AddCommand("a55_sleep",       CMD_a55_sleep,      "A55 enter sleep mode");
    Shell_AddCommand("a55_wake",        CMD_a55_wake,       "A55 wake up from sleep mode");
}
