// todo : 

// 정해진 비율로만 쭉 퍼징하게 할 지, 아니면 서버에서 계속 보내줄건지... 이건 일단 서버에서 준 값으로 해보고, 정 안되면 정해진 비율로
// 특정 주파수율로 센서값을 읽어오는게 맞는지 확인하기

//void GyroBridge::mutate(Vector3f originGyroData)
//{

//}
//gyroBridge.mutate(gyro_accum);


#include "SensorFuzzer_Bridge.h"

GyroBridge::GyroBridge()
{
    // todo : 나중엔 값을 conf 파일에서 읽어오는 형식으로 변경하자
    shmWriteKey     = 32300;
    shmReadKey      = 31340;
    shmSize         = 100;
}


Vector3f GyroBridge::ratioMutate(Vector3f gyroData)
{
    void *shmAddr = getShmAddr(shmReadKey, shmSize);

    struct gyroBridgeStruct *getGyroData = (struct gyroBridgeStruct *)shmAddr;
    if(getGyroData->count > 0 && getGyroData->type == 2){
        printf("hit! %d\n", getGyroData->count);
        gyroData.x *= getGyroData->x;
        gyroData.y *= getGyroData->y;
        gyroData.z *= getGyroData->z;
        getGyroData->count--;
    }

    shmdt(shmAddr);

    return gyroData;
}

void GyroBridge::sendSensorValue(Vector3f originGyroData)
{
    void *shmAddr = getShmAddr(shmWriteKey, shmSize);

    struct gyroBridgeStruct *setGyroData = (struct gyroBridgeStruct *)shmAddr;
    setGyroData->type = 1;
    setGyroData->count = 1;
    setGyroData->x = originGyroData.x;
    setGyroData->y = originGyroData.y;
    setGyroData->z = originGyroData.z;
    
    shmdt(shmAddr);
}

Vector3f GyroBridge::recvSensorValue(Vector3f gyroData)
{
    void *shmAddr = getShmAddr(shmReadKey, shmSize);

    struct gyroBridgeStruct *getGyroData = (struct gyroBridgeStruct *)shmAddr;
    if(getGyroData->count > 0 && getGyroData->type == 1){
        gyroData.x = getGyroData->x;
        gyroData.y = getGyroData->y;
        gyroData.z = getGyroData->z;
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