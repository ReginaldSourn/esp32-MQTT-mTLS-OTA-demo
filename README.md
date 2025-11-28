# ESP32 MQTT mTLS + OTA Demo (ESP-IDF)

This sample shows how to connect an ESP32 to Wi-Fi, establish an mTLS-secured MQTT session with x.509 certificates, and fetch firmware updates over HTTPS OTA. The project targets an 8 MB flash layout with dual OTA slots.

## Project Layout
- `CMakeLists.txt`: ESP-IDF project entry.
- `partitions.csv`: 8 MB layout with factory + two OTA slots + SPIFFS.
- `main/`: Application sources.
  - `main.c`: Wi-Fi bring-up, MQTT client, and OTA logic.
  - `certs.c/h`: PEM placeholders for CA, client certificate, and private key.
  - `Kconfig.projbuild`: Menuconfig options for Wi-Fi, MQTT, and OTA.

## Prerequisites
- ESP-IDF v5+ with the ESP32 toolchain installed and exported.
- An MQTT broker that accepts mTLS (broker root CA, device cert/key).
- HTTPS server hosting OTA firmware (with known root CA).

## Configure
1. Put your certificates/keys in `main/certs.c` (CA for MQTT, device cert/key, and OTA server CA).
2. Run menuconfig to set credentials and endpoints:
   ```bash
   idf.py menuconfig
   ```
   - `MQTT mTLS OTA Demo Configuration` → set Wi-Fi SSID/password.
   - Set `MQTT broker URI` (use `mqtts://host:port`), client ID, username (optional), topics.
   - Set `HTTPS OTA image URL` and choose whether OTA runs automatically on boot.
3. (Optional) Adjust flash layout by editing `partitions.csv`.

## Build & Flash
```bash
idf.py set-target esp32
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

## OTA Flow
- On boot, the app connects to Wi-Fi, starts the mTLS MQTT client, and (if enabled) triggers `esp_https_ota` against `CONFIG_OTA_UPDATE_URL`.
- After a successful download the device reboots into the new OTA slot (`CONFIG_OTA_REBOOT_ON_UPDATE`).

## Partition Table (8 MB)
- `factory`: 1 MB factory image.
- `ota_0`/`ota_1`: 2 × 0x1E0000 (~1.9 MB) OTA slots.
- `storage`: 2 MB SPIFFS.
- Standard `nvs`, `otadata`, and `phy_init` data partitions.

## Notes
- The demo publishes once to `CONFIG_MQTT_PUB_TOPIC` on connect and subscribes to `CONFIG_MQTT_SUB_TOPIC`.
- Update certificate strings carefully—newline escapes must remain intact.
- If Wi-Fi fails `CONFIG_WIFI_MAXIMUM_RETRY` times, the app stops retrying until reset.
