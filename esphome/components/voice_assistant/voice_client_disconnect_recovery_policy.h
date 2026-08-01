#pragma once

#include <cstdint>

namespace esphome::voice_assistant {

constexpr uint32_t VOICE_CLIENT_DISCONNECT_RECOVERY_MS = 10000U;

// A transient Home Assistant/API disconnect is expected to reconnect without
// intervention. If an observed voice-client disconnect remains unresolved,
// one device restart forces a fresh ESPHome discovery/subscription handshake.
// The caller clears disconnect_seen before restarting, and the flag is not
// restored across boot, so an unavailable Home Assistant cannot cause a loop.
constexpr bool should_restart_after_voice_client_disconnect(bool disconnect_seen, bool voice_client_connected,
                                                            bool wifi_connected, bool playback_active,
                                                            bool timer_active, uint32_t now, uint32_t disconnected_at,
                                                            uint32_t timeout_ms = VOICE_CLIENT_DISCONNECT_RECOVERY_MS) {
  return timeout_ms > 0U && disconnect_seen && !voice_client_connected && wifi_connected && !playback_active &&
         !timer_active && static_cast<uint32_t>(now - disconnected_at) >= timeout_ms;
}

}  // namespace esphome::voice_assistant
