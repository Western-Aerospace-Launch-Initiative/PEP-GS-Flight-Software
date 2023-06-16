// stub functions for hardware and platform specific functions:
// send & receive comms messages
// delay
#include <cubeadcs.h>

bool SendCommand(uint8_t* msg, uint16_t len)
{
	// todo: provide an implementation for this
	return true;
}
bool RequestTelemetry(uint8_t tlmId, uint8_t* msgBuffer, uint16_t len)
{
	// todo: provide an implementation for this
	return true;
}

void Delay(uint16_t ms)
{
	// todo: provide an implementation for this
}

uint32_t GetMsTick()
{
	// todo: provide an implementation for this
	return 0;
}

int printf(const char *format, ... )
{
	return 0;
}






