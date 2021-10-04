#include "SensorFuzzer_Bridge.h"

GyroBridge::GyroBridge()
{
    // todo : 나중엔 값을 conf 파일에서 읽어오는 형식으로 변경하자
    shmWriteKey     = 32300;
    shmReadKey      = 31340;
    shmSize         = 100;
}

void GyroBridge::sendSensorValue(Vector3f originGyroData)
{
    void *shmAddr = getShmAddr(shmWriteKey, shmSize);

    struct gyroBridgeStruct *setGyroData = (struct gyroBridgeStruct *)shmAddr;
    setGyroData->type= 1;
    setGyroData->count = 1;
    setGyroData->x = originGyroData.x;
    setGyroData->y = originGyroData.y;
    setGyroData->z = originGyroData.z;
    printf("%f %f %f\n", setGyroData->x, setGyroData->y, setGyroData->z);
    
    shmdt(shmAddr);
}

Vector3f GyroBridge::recvSensorValue()
{
    void *shmAddr = getShmAddr(shmReadKey, shmSize);

    struct gyroBridgeStruct *getGyroData = (struct gyroBridgeStruct *)shmAddr;
    Vector3f gyroData;
    if(getGyroData->count > 0 && getGyroData->type == 1){
        gyroData.x = getGyroData->x;
        gyroData.y = getGyroData->y;
        gyroData.z = getGyroData->z;
        printf("%d %f %f %f\n", getGyroData->count, getGyroData->x, getGyroData->y, getGyroData->z);
        getGyroData->count--;
    }

    shmdt(shmAddr);

    return gyroData;
}

void * GyroBridge::getShmAddr(int key, int size)
{
    int shmid = shmget(key, size, IPC_CREAT|0666);
    void *memory_segment=NULL;
    
    memory_segment = shmat(shmid, NULL, 0);
    if(memory_segment == (void *)-1)
    {
        printf("memory segment error\n");
        exit(0);
    }
    return memory_segment;
}




    /*
    int shmid = shmget(31340, 100, IPC_CREAT|0666);
    void *memory_segment=NULL;
    
    memory_segment = shmat(shmid, NULL, 0);
    if(memory_segment == (void *)-1)
    {
        printf("memory segment error\n");
        exit(0);
    }

    struct gyroMutateValue *amv = (struct gyroMutateValue *)memory_segment;
    */


    // ks : get mean sensor value
    /*
    if(amv->count != -1)
    {
        amv->x *= (float)amv->count;
        amv->x += gyro_accum.x;
        amv->x /= (float)(amv->count)+1;
        amv->y *= (float)amv->count;
        amv->y += gyro_accum.y;
        amv->y /= (float)(amv->count)+1;
        amv->z *= (float)amv->count;
        amv->z += gyro_accum.z;
        amv->z /= (float)(amv->count)+1;
        (amv->count)++;
        if(amv->count % 1000 == 0){
            printf("val : %f %f %f\n", gyro_accum.x, gyro_accum.y, gyro_accum.z);
            printf("avg : %f %f %f\n", amv->x, amv->y, amv->z);
        }
    }
    */
    
    /*
    if(amv->count > 0 && amv->type == 1){
        gyro_accum.x = amv->x;
        gyro_accum.y = amv->y;
        gyro_accum.z = amv->z;
        printf("%d %f %f %f\n", amv->count, amv->x, amv->y, amv->z);
        //printf("%d %f %f %f\n", amv->count, gyro_accum.x, gyro_accum.y, gyro_accum.z);
        amv->count--;
    }
    shmdt(memory_segment);
    */

/////////////////////////////////////////////////////////////////
    // ks : send sensor data to shm
    //int writeId = shmget(32300, 100, IPC_CREAT|0666);
    //void *writeSegment=NULL;
    
    //writeSegment = shmat(writeId, NULL, 0);
    //if(writeSegment == (void *)-1)
    //{
    //    printf("memory segment error\n");
    //    exit(0);
    //}

    //struct gyroMutateValue *gyroVlaue = (struct gyroMutateValue *)writeSegment;
    //gyroVlaue->type= 1;
    //gyroVlaue->count = 1;
    //gyroVlaue->x = gyro_accum.x;
    //gyroVlaue->y = gyro_accum.y;
    //gyroVlaue->z = gyro_accum.z;
    
    //printf("%f %f %f\n", gyroVlaue->x, gyroVlaue->y, gyroVlaue->z);
    
    //shmdt(writeSegment);
/////////////////////////////////////////////////////////////////