/************************************************
 *  @file     : rtos_task.c
 *  @author   : CAO HIEU
 *-----------------------------------------------
 *  Description :
 *    [-]
 ************************************************/
#include "rtos_tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Define/define.h"
#include "Services/cmdline.h"
#include "Interface/SimpleShell/simple_shell.h"
#include "fsl_debug_console.h"

#define CREATE_TASK(task_func, task_name, stack, param, priority, handle) \
    if (xTaskCreate(task_func, task_name, stack, param, priority, handle) != pdPASS) { \
        return E_ERROR; \
    }

#define MIN_STACK_SIZE	configMINIMAL_STACK_SIZE
#define ROOT_PRIORITY   1
#define ROOT_STACK_SIZE (configMINIMAL_STACK_SIZE * 5)

static StackType_t root_stack[ROOT_STACK_SIZE];
static StaticTask_t root_tcb;

Std_ReturnType EXP_AppInit(void);

/*************************************************
 *               TASK DEFINE                     *
 *************************************************/
void EXP_RootTask(void *pvParameters);
static void Shell_Task(void *pvParameters);

/*************************************************
 *               	Root Task	                 *
 *************************************************/
void EXP_RootTask(void *pvParameters)
{
    PRINTF("===== i.MX93 Shell started =====\r\n");

    if (EXP_AppInit() != E_OK)
    {

    }

    vTaskDelete(NULL);
    while(1){

    }
}

void EXP_RootGrowUp(void)
{
    TaskHandle_t task_handle = xTaskCreateStatic(
        EXP_RootTask,
        "EXP_RootTask",
        ROOT_STACK_SIZE,
        NULL,
        ROOT_PRIORITY,
        root_stack,
        &root_tcb
    );

    if (task_handle == NULL)
    {
        while (1);
    }

    vTaskStartScheduler();
}

/*************************************************
 *               	TASK INIT	                 *
 *************************************************/

Std_ReturnType EXP_AppInit(void)
{

	Std_ReturnType ret = E_ERROR;

    CREATE_TASK(Shell_Task, 		"ShellTask", 		MIN_STACK_SIZE * 5, 	NULL, 	1, NULL);

    ret = E_OK;
    return ret;
}

/*************************************************
 *               TASK LIST                       *
 *************************************************/
static void Shell_Task(void *pvParameters)
{
    setup_dynamic_shell();

    while (1)
    {
        char c = GETCHAR();     
        Shell_ReceiveChar(c);      
    }
}