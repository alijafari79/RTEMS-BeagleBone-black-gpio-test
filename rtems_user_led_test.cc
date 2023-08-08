#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include <rtems.h>
#include <libcpu/am335x.h>
#include <bsp/beagleboneblack.h>
#include <bsp/bbb-gpio.h>
#include <bsp/gpio.h>

const char rtems_test_name[] = "LIBGPIO_TEST";

static void Init(rtems_task_argument arg)
{

    rtems_status_code sc;

    printf("Starting Gpio Testing\n");

    /* Initializes the GPIO API */
    rtems_gpio_initialize();

    sc = rtems_gpio_request_pin(BBB_LED_USR0, DIGITAL_OUTPUT, false, false, NULL);
    assert(sc == RTEMS_SUCCESSFUL);

    sc = rtems_gpio_request_pin(BBB_LED_USR1, BBB_DIGITAL_OUT, false, false, NULL);
    assert(sc == RTEMS_SUCCESSFUL);

    sc = rtems_gpio_request_pin(BBB_LED_USR2, BBB_DIGITAL_OUT, false, false, NULL);
    assert(sc == RTEMS_SUCCESSFUL);

    sc = rtems_gpio_request_pin(BBB_LED_USR3, BBB_DIGITAL_OUT, false, false, NULL);
    assert(sc == RTEMS_SUCCESSFUL);

    // Now with a general GPIO pin instead of one of the user leds
    sc = rtems_gpio_request_pin(BBB_P9_12, BBB_DIGITAL_OUT, false, false, NULL);
    assert(sc == RTEMS_SUCCESSFUL);

    /* Pattern Generation using User Leds */

    /* USER LED 0 */
    rtems_gpio_set (BBB_LED_USR0);
    sleep(1);
    rtems_gpio_clear(BBB_LED_USR0);
    sleep(1);
    rtems_gpio_release_pin(BBB_LED_USR0);

    /* USER LED 1 */
    rtems_gpio_set (BBB_LED_USR1);
    sleep(1);
    rtems_gpio_clear(BBB_LED_USR1);
    sleep(1);
    rtems_gpio_release_pin(BBB_LED_USR1);

    /* USER LED 2 */
    rtems_gpio_set (BBB_LED_USR2);
    sleep(1);
    rtems_gpio_clear(BBB_LED_USR2);
    sleep(1);
    rtems_gpio_release_pin(BBB_LED_USR2);

    /* USER LED 3 */
    rtems_gpio_set (BBB_LED_USR3);
    sleep(1);
    rtems_gpio_clear(BBB_LED_USR3);
    sleep(1);
    rtems_gpio_release_pin(BBB_LED_USR3);

    /* flash the led on pin P9_12 20 times */
    uint32_t i = 0;
    while(++i < 20) {
        rtems_gpio_set (BBB_P9_12);
        usleep(500000);
        rtems_gpio_clear(BBB_P9_12);
        usleep(500000);
    }
    rtems_gpio_release_pin(BBB_P9_12);
}

#define CONFIGURE_MICROSECONDS_PER_TICK 1000

#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 10
#define CONFIGURE_UNLIMITED_OBJECTS
#define CONFIGURE_UNIFIED_WORK_AREAS

#define CONFIGURE_USE_IMFS_AS_BASE_FILESYSTEM

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_INIT

#include <rtems/confdefs.h>
