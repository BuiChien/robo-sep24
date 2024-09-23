#ifndef __PLANNER__
#define __PLANNER__
// The number of linear motions that can be in the plan at any give time
#ifndef BLOCK_BUFFER_SIZE
#ifdef USE_LINE_NUMBERS
#define BLOCK_BUFFER_SIZE 15
#else
#define BLOCK_BUFFER_SIZE 16
#endif
#endif

// Returned status message from planner.
#define PLAN_OK true
#define PLAN_EMPTY_BLOCK false

// Define planner data condition flags. Used to denote running conditions of a block.
#define PL_COND_FLAG_RAPID_MOTION      bit(0)
#define PL_COND_FLAG_SYSTEM_MOTION     bit(1) // Single motion. Circumvents planner state. Used by home/park.
#define PL_COND_FLAG_NO_FEED_OVERRIDE  bit(2) // Motion does not honor feed override.
#define PL_COND_FLAG_INVERSE_TIME      bit(3) // Interprets feed rate value as inverse time when set.
#define PL_COND_FLAG_SPINDLE_CW        bit(4)
#define PL_COND_FLAG_SPINDLE_CCW       bit(5)
#define PL_COND_FLAG_COOLANT_FLOOD     bit(6)
#define PL_COND_FLAG_COOLANT_MIST      bit(7)
#define PL_COND_MOTION_MASK    (PL_COND_FLAG_RAPID_MOTION|PL_COND_FLAG_SYSTEM_MOTION|PL_COND_FLAG_NO_FEED_OVERRIDE)
#define PL_COND_SPINDLE_MASK   (PL_COND_FLAG_SPINDLE_CW|PL_COND_FLAG_SPINDLE_CCW)
#define PL_COND_ACCESSORY_MASK (PL_COND_FLAG_SPINDLE_CW|PL_COND_FLAG_SPINDLE_CCW|PL_COND_FLAG_COOLANT_FLOOD|PL_COND_FLAG_COOLANT_MIST)

// Planner data prototype. Must be used when passing new motions to the planner.
typedef struct {
	float feed_rate;          // Desired feed rate for line motion. Value is ignored, if rapid motion.
	float spindle_speed;      // Desired spindle speed through line motion.
	uint8_t condition;        // Bitflag variable to indicate planner conditions. See defines above.
	int32_t line_number;    // Desired line number to report when executing.
} plan_line_data_t;

class Planner
{
public:
	Planner();
	~Planner();
	void Reset();

private:
	/* data */
};

#endif //__PLANNER__