#pragma once

namespace esphome::voice_assistant {

enum class PlaybackTimeoutAction {
  STARTUP_FAILED,
  PLAYBACK_FINISHED,
};

constexpr PlaybackTimeoutAction classify_playback_timeout(bool has_media_player, bool url_pending) {
  if (has_media_player && url_pending) {
    return PlaybackTimeoutAction::STARTUP_FAILED;
  }
  return PlaybackTimeoutAction::PLAYBACK_FINISHED;
}

}  // namespace esphome::voice_assistant
