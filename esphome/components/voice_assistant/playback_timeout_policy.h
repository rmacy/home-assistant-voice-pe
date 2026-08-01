#pragma once

namespace esphome::voice_assistant {

enum class PlaybackTimeoutAction {
  PLAYBACK_FAILED,
  PLAYBACK_FINISHED,
};

constexpr PlaybackTimeoutAction classify_playback_timeout(bool has_media_player, bool url_pending,
                                                           bool playback_active) {
  if (has_media_player && (url_pending || playback_active)) {
    return PlaybackTimeoutAction::PLAYBACK_FAILED;
  }
  return PlaybackTimeoutAction::PLAYBACK_FINISHED;
}

}  // namespace esphome::voice_assistant
