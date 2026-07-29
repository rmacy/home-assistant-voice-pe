# Server-side “Hey Nova” wake word

This branch adds the upstream experimental streaming wake-word implementation
to Home Assistant Voice Preview Edition firmware and makes **In Home Assistant**
the initial engine selection. The device streams mono microphone audio only to
the configured Home Assistant instance over its encrypted ESPHome API. Home
Assistant runs the wake-word model and sends the normal Assist request only
after detection.

## Required Home Assistant configuration

1. Install and start a local Wyoming-compatible openWakeWord service.
2. Add its Wyoming integration to Home Assistant.
3. Install the `hey_nova` ONNX model in that service and select it as the
   streaming wake word for the **Gemma Home Assistant** assistant.
4. Compile and install this firmware. The device exposes **Wake word engine
   location**; retain **On device** as the break-glass fallback.

The wake-word service and model must remain private to the LAN. This branch
does not send audio to a cloud provider.

## Safety and recovery

Do not remove the on-device `micro_wake_word` block: it supplies the local
`stop` word during timers and replies, and its **On device** selector gives a
recoverable fallback if Home Assistant or the wake-word service is unavailable.

Before OTA flashing, take a full Home Assistant backup and retain the previous
firmware build artifact. Validate with the device in the same room where it
will be used, then tune only the server-side model threshold; do not alter the
device audio pipeline merely to compensate for a weak model.
