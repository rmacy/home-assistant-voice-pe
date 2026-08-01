#pragma once

#include <cstdint>

namespace esphome::voice_assistant {

constexpr uint32_t FOREGROUND_PHASE_MAX_MS = 30000;

constexpr bool foreground_phase_changed(int previous_phase, int current_phase) {
  return previous_phase != current_phase;
}

// A foreground phase that cannot make progress must never leave the unit
// spinning forever. Media playback and timers have their own lifecycle and
// are deliberately excluded. Unsigned subtraction keeps the deadline correct
// across the millis() wrap.
constexpr bool should_abort_stale_foreground_phase(
    bool initialized, bool api_connected, bool server_wake_selected,
    bool phase_is_idle, bool media_announcing, bool timer_ringing,
    bool phase_timer_valid, uint32_t now_ms, uint32_t phase_started_at_ms,
    uint32_t timeout_ms = FOREGROUND_PHASE_MAX_MS) {
  return timeout_ms > 0 && initialized && api_connected && server_wake_selected &&
         !phase_is_idle && !media_announcing && !timer_ringing &&
         phase_timer_valid &&
         static_cast<uint32_t>(now_ms - phase_started_at_ms) >= timeout_ms;
}

}  // namespace esphome::voice_assistant
