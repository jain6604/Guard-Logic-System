#include <iostream>
#include <string>
#include <map>
#include <functional>

// ─────────────────────────────────────────────
//  Domain types
// ─────────────────────────────────────────────

enum class DoorOutcome {
    SafeExit,
    Trap,
    StartingPoint
};

struct Conditions {
    bool hasValidKeycard;
    bool alarmTriggered;
    bool motionDetected;
};

struct Door {
    int              id;
    std::string      label;
    DoorOutcome      outcome;
};

// ─────────────────────────────────────────────
//  Guard logic
// ─────────────────────────────────────────────

/**
 * Selects which door to open based on the current facility conditions.
 *
 * Rules (evaluated in priority order):
 *  1. Alarm triggered  → Door 2 (Trap)   — lock down; no one leaves safely.
 *  2. Valid keycard    → Door 1 (Exit)   — authorised personnel may exit.
 *  3. Motion detected  → Door 3 (Start)  — send intruder back to the beginning.
 *  4. Default          → Door 3 (Start)  — unknown state; safest fallback.
 */
Door selectDoor(const Conditions& cond, const std::map<int, Door>& doors) {
    if (cond.alarmTriggered)   return doors.at(2); // highest priority: lockdown
    if (cond.hasValidKeycard)  return doors.at(1); // authorised exit
    if (cond.motionDetected)   return doors.at(3); // redirect intruder
    return doors.at(3);                            // safe default
}

// ─────────────────────────────────────────────
//  Helpers
// ─────────────────────────────────────────────

std::string outcomeToString(DoorOutcome o) {
    switch (o) {
        case DoorOutcome::SafeExit:      return "Safe Exit";
        case DoorOutcome::Trap:          return "Trap";
        case DoorOutcome::StartingPoint: return "Starting Point";
    }
    return "Unknown";
}

void printResult(const Conditions& cond, const Door& chosen) {
    std::cout << "\n--- Guard Decision ---\n"
              << "  Keycard : " << (cond.hasValidKeycard ? "YES" : "NO")  << "\n"
              << "  Alarm   : " << (cond.alarmTriggered  ? "YES" : "NO")  << "\n"
              << "  Motion  : " << (cond.motionDetected  ? "YES" : "NO")  << "\n"
              << "  → Door " << chosen.id
              << " [" << chosen.label << "] — " << outcomeToString(chosen.outcome) << "\n";
}

// ─────────────────────────────────────────────
//  Entry point – demo scenarios
// ─────────────────────────────────────────────

int main() {
    // Define the three doors
    const std::map<int, Door> doors = {
        {1, {1, "Green Door",  DoorOutcome::SafeExit}},
        {2, {2, "Red Door",    DoorOutcome::Trap}},
        {3, {3, "Yellow Door", DoorOutcome::StartingPoint}},
    };

    // Test every meaningful scenario
    //                              keycard  alarm   motion
    std::vector<Conditions> scenarios = {
        {true,  false, false},   // authorised, quiet   → Exit
        {true,  true,  false},   // alarm overrides keycard → Trap
        {false, false, true},    // intruder, no alarm  → Start
        {false, false, false},   // nothing detected    → Start (default)
        {false, true,  true},    // alarm + motion      → Trap (alarm wins)
    };

    for (const auto& cond : scenarios) {
        Door chosen = selectDoor(cond, doors);
        printResult(cond, chosen);
    }

    return 0;
}