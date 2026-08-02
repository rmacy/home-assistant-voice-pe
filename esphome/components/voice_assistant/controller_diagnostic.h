#pragma once

#include <cstdio>
#include <string>
#include <string_view>

namespace esphome::voice_assistant {

struct ControllerDiagnosticSnapshot {
  int phase;
  int state;
  int desired_state;
  bool running;
  bool continuous;
  bool conversation_active;
  bool idle_wake_streaming;
  std::string_view effect_name;
  bool voice_output_effect_active;
  int animation_index;
  bool voice_led_on;
  bool user_led_on;
  int media_state;
  bool timer_ringing;
  bool api_connected;
};

inline std::string format_controller_diagnostic(const ControllerDiagnosticSnapshot &snapshot) {
  char buffer[240];
  snprintf(buffer, sizeof(buffer),
           "p=%d;s=%d;d=%d;run=%d;cont=%d;conv=%d;iws=%d;fx=%.*s;voe=%d;ai=%d;vl=%d;ul=%d;media=%d;timer=%d;api=%d",
           snapshot.phase, snapshot.state, snapshot.desired_state, snapshot.running, snapshot.continuous,
           snapshot.conversation_active, snapshot.idle_wake_streaming, static_cast<int>(snapshot.effect_name.size()),
           snapshot.effect_name.data(), snapshot.voice_output_effect_active, snapshot.animation_index,
           snapshot.voice_led_on, snapshot.user_led_on, snapshot.media_state, snapshot.timer_ringing,
           snapshot.api_connected);
  return std::string(buffer);
}

}  // namespace esphome::voice_assistant
