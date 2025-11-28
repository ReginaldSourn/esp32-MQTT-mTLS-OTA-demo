/**
 * Dummy certificates for illustration. Replace with your CA, device certificate,
 * and private key. Keep the BEGIN/END lines and newline escapes intact.
 */
#include "certs.h"

const char mqtt_server_root_cert_pem[] =
        "-----BEGIN CERTIFICATE-----\n"
        "REPLACE_WITH_MQTT_BROKER_CA_CERT\n"
        "-----END CERTIFICATE-----\n";

const char mqtt_client_cert_pem[] =
        "-----BEGIN CERTIFICATE-----\n"
        "REPLACE_WITH_DEVICE_CERT\n"
        "-----END CERTIFICATE-----\n";

const char mqtt_client_key_pem[] =
        "-----BEGIN PRIVATE KEY-----\n"
        "REPLACE_WITH_DEVICE_KEY\n"
        "-----END PRIVATE KEY-----\n";

const char ota_server_root_cert_pem[] =
        "-----BEGIN CERTIFICATE-----\n"
        "REPLACE_WITH_OTA_SERVER_CA_CERT\n"
        "-----END CERTIFICATE-----\n";
