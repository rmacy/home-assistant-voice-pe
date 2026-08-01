#pragma once

namespace esphome::voice_assistant {

// The continuous server-side wake pipeline is the device's real idle state.
// It is safe to reconcile a stale visual phase only when every state-machine
// signal agrees that no foreground conversation owns the microphone.
constexpr bool is_idle_wake_stream_state(bool state_streaming, bool desired_streaming, bool continuous,
                                         bool use_wake_word, bool conversation_active) {
  return state_streaming && desired_streaming && continuous && use_wake_word && !conversation_active;
}

constexpr bool should_reconcile_idle_phase(bool initialized, bool api_connected, bool server_wake_selected,
                                           bool phase_is_idle, bool idle_wake_streaming, bool media_announcing,
                                           bool timer_ringing) {
  return initialized && api_connected && server_wake_selected && !phase_is_idle && idle_wake_streaming &&
         !media_announcing && !timer_ringing;
}

}  // namespace esphome::voice_assistant
