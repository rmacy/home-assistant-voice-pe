#pragma once

namespace esphome::speaker_source {

constexpr bool should_report_announcing(bool source_playing, bool audio_started) {
  return source_playing && audio_started;
}

}  // namespace esphome::speaker_source
