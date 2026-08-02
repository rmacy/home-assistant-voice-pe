#pragma once

#include <string_view>

namespace esphome::voice_assistant {

constexpr bool is_foreground_voice_effect(std::string_view effect_name) {
  return effect_name == "Waiting for Command" || effect_name == "Listening For Command" ||
         effect_name == "Thinking" || effect_name == "Replying" || effect_name == "Error";
}

// A stale addressable effect can keep rendering after ESPHome has lost its
// effect name. Treat an unnamed internal light as stale only when neither the
// user-facing idle light nor another persistent presentation owns the ring.
constexpr bool is_unowned_idle_illumination(bool internal_led_on, bool idle_led_requested,
                                            std::string_view effect_name, bool timer_active,
                                            bool muted_or_silent) {
  return internal_led_on && !idle_led_requested && effect_name.empty() && !timer_active &&
         !muted_or_silent;
}

// The continuous server-side wake pipeline is the device's real idle state.
// It is safe to reconcile a stale visual phase only when every state-machine
// signal agrees that no foreground conversation owns the microphone.
constexpr bool is_idle_wake_stream_state(bool state_streaming, bool desired_streaming, bool continuous,
                                         bool use_wake_word, bool conversation_active) {
  return state_streaming && desired_streaming && continuous && use_wake_word && !conversation_active;
}

constexpr bool should_reconcile_idle_phase(bool initialized, bool api_connected, bool server_wake_selected,
                                           bool phase_is_idle, bool foreground_presentation_active,
                                           bool idle_wake_streaming, bool media_announcing, bool timer_ringing) {
  return initialized && api_connected && server_wake_selected &&
         (!phase_is_idle || foreground_presentation_active) && idle_wake_streaming && !media_announcing &&
         !timer_ringing;
}

// Stopping an addressable effect and committing its off state happen on
// separate component-loop edges. If the effect writes one final frame between
// those edges, LightState can correctly report off/effect-inactive while the
// physical strip retains that last frame. Permit one delayed black-frame
// commit only when every independent presentation owner still agrees on idle.
constexpr bool should_commit_idle_black_frame(bool initialized, bool api_connected, bool server_wake_selected,
                                              bool phase_is_idle, bool idle_wake_streaming, bool voice_light_on,
                                              bool voice_effect_active, bool user_light_on, bool media_announcing,
                                              bool timer_active) {
  return initialized && api_connected && server_wake_selected && phase_is_idle && idle_wake_streaming &&
         !voice_light_on && !voice_effect_active && !user_light_on && !media_announcing && !timer_active;
}

}  // namespace esphome::voice_assistant
