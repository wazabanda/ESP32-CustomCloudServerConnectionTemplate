#include "connector.h"
#include <string.h> 
#include <stdlib.h> 
#include <Arduino.h>
#include "WiFi.h"
#include <HTTPClient.h>

// Definition of extern variables
char* serverUrl = NULL;
char* deviceId = NULL;

// Function implementations
void setServerUrl(const char* url) {
    if (serverUrl) {
        free(serverUrl); // Free the previous string if it exists
        serverUrl = NULL;
    }
    if (url) {
        serverUrl = strdup(url); // Duplicate the string and assign it
    }
}

void setDeviceId(const char* id) {
    if (deviceId) {
        free(deviceId); // Free the previous string if it exists
        deviceId = NULL;
    }
    if (id) {
        deviceId = strdup(id); // Duplicate the string and assign it
    }
}

void clearServerUrl() {
    if (serverUrl) {
        free(serverUrl);
        serverUrl = NULL;
    }
}

void clearDeviceId() {
    if (deviceId) {
        free(deviceId);
        deviceId = NULL;
    }
}

String createJsonPayload(const LogData* logs, size_t logCount) {
    String payload = "{\"logs\":[";
    for (size_t i = 0; i < logCount; ++i) {
        payload += "{\"value\":" + String(logs[i].value) + ",\"data_label\":\"" + logs[i].data_label + "\"}";
        if (i < logCount - 1) {
            payload += ",";
        }
    }
    payload += "]}";
    return payload;
}

void makeHttpPostRequest(String payload, String extra_url) {
  HTTPClient http;

  // Set the target URL
  http.begin(String("http://") + serverUrl + extra_url + deviceId);

  // Set the content type
  http.addHeader("Content-Type", "application/json");

  // Print the payload for debugging
  Serial.println(payload);

  // Make the POST request
  int httpResponseCode = http.POST(payload);

  // Check for a successful request
  if (httpResponseCode > 0) {
    Serial.print("HTTP POST Request Success. Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("HTTP POST Request failed. Response code: ");
    Serial.println(httpResponseCode);
  }

  // Close the connection
  http.end();
}
