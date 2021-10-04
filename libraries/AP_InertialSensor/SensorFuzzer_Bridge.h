#pragma once

#include <AP_Math/AP_Math.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>

struct accelBridgeStruct {
    int type;
    int count;
    int x;
    int y;
    int z;
};

struct temperatureBridgeStruct {
    int type;
    int count;
    int temp;
};

struct gyroBridgeStruct {
    int type;
    int count;
    float x;
    float y;
    float z;
};

class GyroBridge
{
public:
    GyroBridge();
    void sendSensorValue(Vector3f gyroValue);
    Vector3f recvSensorValue();

private:
    int shmWriteKey;
    int shmReadKey;
    int shmSize;
    void * getShmAddr(int key, int size);
};