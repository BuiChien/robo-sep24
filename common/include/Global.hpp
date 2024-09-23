#ifndef __GLOBAL__
#define __GLOBAL__
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "AppConf.hpp"
#include "MemoryPool.hpp"
#include "Utils.hpp"

#define STEP_CONTROL_NORMAL_OP            0  // Must be zero.
#define STEP_CONTROL_END_MOTION           bit(0)
#define STEP_CONTROL_EXECUTE_HOLD         bit(1)
#define STEP_CONTROL_EXECUTE_SYS_MOTION   bit(2)
#define STEP_CONTROL_UPDATE_SPINDLE_PWM   bit(3)
#define ACCELERATION_TICKS_PER_SECOND 100

typedef struct {
    uint8_t state;               // Tracks the current system state of Grbl.
    uint8_t abort;               // System abort flag. Forces exit back to main loop for reset.             
    uint8_t suspend;             // System suspend bitflag variable that manages holds, cancels, and safety door.
    uint8_t soft_limit;          // Tracks soft limit errors for the state machine. (boolean)
    uint8_t step_control;        // Governs the step segment generator depending on system state.
    uint8_t probe_succeeded;     // Tracks if last probing cycle was successful.
    uint8_t homing_axis_lock;    // Locks axes when limits engage. Used as an axis motion mask in the stepper ISR.
#ifdef ENABLE_DUAL_AXIS
    uint8_t homing_axis_lock_dual;
#endif
    uint8_t f_override;          // Feed rate override value in percent
    uint8_t r_override;          // Rapids override value in percent
    uint8_t spindle_speed_ovr;   // Spindle speed value in percent
    uint8_t spindle_stop_ovr;    // Tracks spindle stop override states
    uint8_t report_ovr_counter;  // Tracks when to add override data to status reports.
    uint8_t report_wco_counter;  // Tracks when to add work coordinate offset data to status reports.
#ifdef ENABLE_PARKING_OVERRIDE_CONTROL
    uint8_t override_ctrl;     // Tracks override control states.
#endif
#ifdef VARIABLE_SPINDLE
    float spindle_speed;
#endif
} system_t;

// Global persistent settings (Stored from byte EEPROM_ADDR_GLOBAL onwards)
typedef struct {
    // Axis settings
    float steps_per_mm[N_AXIS];
    float max_rate[N_AXIS];
    float acceleration[N_AXIS];
    float max_travel[N_AXIS];

    // Remaining Grbl settings
    uint8_t pulse_microseconds;
    uint8_t step_invert_mask;
    uint8_t dir_invert_mask;
    uint8_t stepper_idle_lock_time; // If max value 255, steppers do not disable.
    uint8_t status_report_mask; // Mask to indicate desired report data.
    float junction_deviation;
    float arc_tolerance;

    float rpm_max;
    float rpm_min;

    uint8_t flags;  // Contains default boolean settings

    uint8_t homing_dir_mask;
    float homing_feed_rate;
    float homing_seek_rate;
    uint16_t homing_debounce_delay;
    float homing_pulloff;
} settings_t;

typedef struct
{
    // Fields used by the bresenham algorithm for tracing the line
    // NOTE: Used by stepper algorithm to execute the block correctly. Do not alter these values.
    uint32_t steps[N_AXIS];    // Step count along each axis
    uint32_t step_event_count; // The maximum step axis count and number of steps required to complete this block.
    uint8_t direction_bits;    // The direction bit set for this block (refers to *_DIRECTION_BIT in config.h)

    // Block condition data to ensure correct execution depending on states and overrides.
    uint8_t condition;      // Block bitflag variable defining block run conditions. Copied from pl_line_data.
    int32_t line_number;  // Block line number for real-time reporting. Copied from pl_line_data.
    // Fields used by the motion planner to manage acceleration. Some of these values may be updated
    // by the stepper module during execution of special motion cases for replanning purposes.
    float entry_speed_sqr;     // The current planned entry speed at block junction in (mm/min)^2
    float max_entry_speed_sqr; // Maximum allowable entry speed based on the minimum of junction limit and
    //   neighboring nominal speeds with overrides in (mm/min)^2
    float acceleration;        // Axis-limit adjusted line acceleration in (mm/min^2). Does not change.
    float millimeters;         // The remaining distance for this block to be executed in (mm).
    // NOTE: This value may be altered by stepper algorithm during execution.
    // Stored rate limiting data used by planner when changes occur.
    float max_junction_speed_sqr; // Junction entry speed limit based on direction vectors in (mm/min)^2
    float rapid_rate;             // Axis-limit adjusted maximum rate for this block direction in (mm/min)
    float programmed_rate;        // Programmed rate of this block (mm/min).
} plan_block_t;

extern QueueHandle_t gPlannerQueueHandle;
extern MemoryPool* const gEventPool;
extern int32_t sys_position[N_AXIS];
extern settings_t settings;
extern system_t sys;

#endif
