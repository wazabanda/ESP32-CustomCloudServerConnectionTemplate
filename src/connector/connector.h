#ifndef CONNECTOR_H_INCLUDE
#define CONNECTOR_H_INCLUDE

#include <Arduino.h> // Include Arduino header for the String class

extern char* serverUrl;
extern char* deviceId;

void setServerUrl(const char* url);
void setDeviceId(const char* id);
void clearServerUrl();
void clearDeviceId();

struct LogData {
    float value;
    String data_label;
};

String createJsonPayload(const LogData* logs, size_t logCount);
void makeHttpPostRequest(String payload, String extra_url);


#endif