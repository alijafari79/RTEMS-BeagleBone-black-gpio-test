#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include <rtems.h>
#include <bsp/bbb-pwm.h>


static void
Init(rtems_task_argument arg)
{
    printf("Starting PWM Testing\n");

    rtems_status_code sc;
    bool success;

    /*Initialize GPIO pins in BBB*/
    rtems_gpio_initialize();

    // Configure both channels of PWM instance 0 to run at 10 Hz, 50% duty cycle
    BBB_PWMSS pwmss_id = BBB_PWMSS0;
    float pwm_freq = 1;
    float duty_a = 0.5;
    float duty_b = 0.5;

    /* Set P9 Header , 21 Pin number , PWM B channel and 0 PWM instance to generate frequency*/
    beagle_pwm_pinmux_setup(BBB_P9_21_0B, BBB_PWMSS0);

    // Initialise the pwm module
    success = beagle_pwm_init(BBB_PWMSS0);
    assert(success == true);

    /* check clock is running */
    bool is_running = beagle_pwmss_is_running(pwmss_id);
    printf("clock is running %s\n", is_running ? "true" : "false");

    // Configure the PWM module for a 10Hz output at 50% duty cycle
    beagle_pwm_configure(pwmss_id, pwm_freq, duty_a, duty_b);

    printf("PWM  enable for 10s ....\n");
    // Enable the pwm output
    beagle_pwm_enable(pwmss_id);
    sleep(10);

    /*freeze the counter and disable pwm module*/
    beagle_pwm_disable(pwmss_id);
    printf("PWM disabled. Test finished.\n");
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
