#ifndef FLIGHT_MODE_H
#define FLIGHT_MODE_H

#include "ttauav_node/flightByOffset.h"
#include "ttauav_node/flightByVel.h"
#include "ttauav_node/gimbalControl.h"
#include "ttauav_node/takeoffOrLanding.h"

bool flightByOffset(float targetYaw, float offsetZ, float yawThreshold, float posThreshold);
bool flightByVel(float velN, float velE, float velD, float targetYaw, int flyTime);
bool gimbalControl(float pitch);
bool takeoffAndLanding(int takeoffOrLanding); // 1: takeoff, 2: landing

#endif  // FLIGHT_MODE_H
