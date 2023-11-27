#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>

#include <dcgm_agent.h>
#include <dcgm_errors.h>

#include "profiler.h"

dcgmReturn_t ret;
dcgmHandle_t pDcgmHandle;
dcgmOperationMode_t opMode;
unsigned int gpuIdList[DCGM_MAX_NUM_DEVICES];
int dev_count;
dcgmDeviceAttributes_t *pDcgmAttr;

// void profile_init()
// {
//     ret = DCGM_ST_OK;
//     ret = dcgmInit();
//     if (ret != DCGM_ST_OK)
//     {
//         dlp(); dp("dcgm initialization error, exit\n");
//         exit(0);
//     }
//     else{
//         dp("dcgm initialization\n");
//     }

//     opMode = DCGM_OPERATION_MODE_AUTO;
//     ret = dcgmStartEmbedded(opMode, &pDcgmHandle);
//     if (ret != DCGM_ST_OK)
//     {
//         dlp(); dp("dcgmStartEmbedded error, exit\n");
//         exit(0);
//     }

//     ret = dcgmGetAllDevices(pDcgmHandle, gpuIdList, &dev_count);
//     if (ret != DCGM_ST_OK)
//     {
//         dlp(); dp("dcgmGetAllDevices error, exit\n");
//         exit(0);
//     }

//     pDcgmAttr = (dcgmDeviceAttributes_t *)malloc(sizeof(dcgmDeviceAttributes_t) * dev_count);
//     for (int i = 0; i < dev_count; i++){
//         dp("%d gpu found %u \n", i, gpuIdList[i]);
        
//         pDcgmAttr[i].version = dcgmDeviceAttributes_version;
//         ret = dcgmGetDeviceAttributes(pDcgmHandle, gpuIdList[i], &(pDcgmAttr[i]));
//         if (ret != DCGM_ST_OK)
//         {
//             dlp(); dp("dcgmGetDeviceAttributes %d error\n", (int)ret);
//             exit(0);
//         }
//         dp("gpu deviceName is %s\n", (pDcgmAttr[i].identifiers.deviceName));
//         dp("gpu UUID is %s\n", (pDcgmAttr[i].identifiers.uuid));
//     }
// }

// void profiler_get_gpu()
// {
//     dcgmMigHierarchy_v2 hierarchy;
//     hierarchy.version = dcgmMigHierarchy_version2;
//     ret = dcgmGetGpuInstanceHierarchy(pDcgmHandle, &hierarchy);
//     if (ret != DCGM_ST_OK)
//     {
//         dlp(); dp("dcgmGetGpuInstanceHierarchy %d error\n", (int)ret);
//         exit(0);
//     }
//     for (unsigned int i = 0; i < hierarchy.count; i++){
//         dp("%d mig found\n", i);
//         dp("mig's gpu instance/compute instance is %d/%d\n", hierarchy.entityList[i].info.nvmlInstanceId, hierarchy.entityList[i].info.nvmlComputeInstanceId);
//         dp("entity information %d/%d\n",  hierarchy.entityList[i].entity.entityGroupId, hierarchy.entityList[i].entity.entityId);
//     }

//     dp("\n");

//     // dcgmGroupType_t type = DCGM_GROUP_DEFAULT_EVERYTHING;
//     dcgmGroupType_t type = DCGM_GROUP_EMPTY;
//     const char* group_name = "mig_group";
//     dcgmGpuGrp_t pDcgmGrpId;
//     ret = dcgmGroupCreate(pDcgmHandle, type, (char *)group_name, &pDcgmGrpId);
//     if (ret != DCGM_ST_OK)
//     {
//         dlp(); dp("dcgmGroupCreate error, exit\n");
//         exit(0);
//     }
//     else{
//         dp("group %ld created\n", pDcgmGrpId);
//     }

//     for (unsigned int i = 0; i < hierarchy.count; i++){
//         ret = dcgmGroupAddEntity(pDcgmHandle, pDcgmGrpId, hierarchy.entityList[i].entity.entityGroupId, hierarchy.entityList[i].entity.entityId);
//         if (ret != DCGM_ST_OK)
//         {
//             dlp(); dp("dcgmGroupAddEntity error %d\n", ret);
//             exit(0);
//         }
//     }

//     ret = dcgmGroupAddDevice(pDcgmHandle, pDcgmGrpId, 1);
//     if (ret != DCGM_ST_OK)
//     {
//         dlp(); dp("dcgmGroupAddDevice error\n");
//     }
//     // dcgmGroupInfo_t pDcgmGroupInfo;
//     // pDcgmGroupInfo.version = dcgmGroupInfo_version2;
//     // ret = dcgmGroupGetInfo(pDcgmHandle, pDcgmGrpId, &pDcgmGroupInfo);
//     // if (ret != DCGM_ST_OK)
//     // {
//     //     dlp(); dp("dcgmGroupGetInfo error %d\n", ret);
//     // }
//     // for (int i = 0;i < pDcgmGroupInfo.count; i++)
//     // {
//     //     dp("%d/%d\n", pDcgmGroupInfo.entityList[i].entityGroupId, pDcgmGroupInfo.entityList[i].entityId);
//     // }

//     dp("\n");   

//     // int  numFieldIds = 5;
//     // unsigned short fieldIds[numFieldIds] = {DCGM_FI_PROF_GR_ENGINE_ACTIVE, DCGM_FI_PROF_SM_ACTIVE, DCGM_FI_PROF_DRAM_ACTIVE, DCGM_FI_PROF_PCIE_TX_BYTES, DCGM_FI_PROF_PCIE_RX_BYTES};
//     int  numFieldIds = 8;
//     unsigned short fieldIds[numFieldIds] = {DCGM_FI_PROF_GR_ENGINE_ACTIVE, DCGM_FI_PROF_SM_ACTIVE, DCGM_FI_PROF_SM_OCCUPANCY, DCGM_FI_PROF_PIPE_TENSOR_ACTIVE, DCGM_FI_PROF_PIPE_FP64_ACTIVE, DCGM_FI_PROF_PIPE_FP32_ACTIVE, DCGM_FI_PROF_PIPE_FP16_ACTIVE, DCGM_FI_PROF_DRAM_ACTIVE};
//     const char* fieldGroupName = "profiling";
//     dcgmFieldGrp_t dcgmFieldGroupId;
//     ret = dcgmFieldGroupCreate(pDcgmHandle, numFieldIds, fieldIds, (char *)fieldGroupName, &dcgmFieldGroupId);
//     if (ret != DCGM_ST_OK)
//     {
//         dlp(); dp("dcgmFieldGroupCreate %d error\n", (int)ret);
//         exit(0);
//     }
//     else{
//         dp("field group %ld created\n", dcgmFieldGroupId);
//     }
// }




int callback_func(dcgm_field_entity_group_t entityGroupId, dcgm_field_eid_t entityId, dcgmFieldValue_v1 *values, int numValues, void *userData)
{
    if (entityGroupId == 5) // gpu instance
    {
        // time_t ts;
        // time(&ts);
        // printw("%ld %ld || %d MIG %d value: %f\n", ts, values[0].ts, entityId, values[0].fieldId, values[0].value.dbl);
        printf("\r%ld || %d GPU instance %d value: %f\n", values[0].ts, entityId, values[0].fieldId, values[0].value.dbl);
        // dp("number of values: %d\n", numValues);
        // dp("print i64 values: %ld\n", values[0].value.i64);
        // dp("print double values: %f\n", values[0].value.dbl);
        // dp("print string values: %s\n", values[0].value.str);
        // dp("\n");
    }
    return 0;
}

int main()
{
    dcgmReturn_t ret = DCGM_ST_OK;
    ret = dcgmInit();
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgm initialization error, exit\n");
        exit(0);
    }
    else{
        dp("dcgm initialization\n");
    }

    dcgmHandle_t pDcgmHandle;
    dcgmOperationMode_t opMode = DCGM_OPERATION_MODE_AUTO;
    ret = dcgmStartEmbedded(opMode, &pDcgmHandle);
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgmStartEmbedded error, exit\n");
        exit(0);
    }

    unsigned int gpuIdList[DCGM_MAX_NUM_DEVICES];
    int dev_count;
    ret = dcgmGetAllDevices(pDcgmHandle, gpuIdList, &dev_count);
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgmGetAllDevices error, exit\n");
        exit(0);
    }


    dcgmDeviceAttributes_t pDcgmAttr[dev_count];
    for (int i = 0; i < dev_count; i++){
        dp("%d gpu found %u \n", i, gpuIdList[i]);
        
        pDcgmAttr[i].version = dcgmDeviceAttributes_version3;
        ret = dcgmGetDeviceAttributes(pDcgmHandle, gpuIdList[i], &(pDcgmAttr[i]));
        if (ret != DCGM_ST_OK)
        {
            dlp(); dp("dcgmGetDeviceAttributes %d error\n", (int)ret);
        }
        dp("gpu deviceName is %s\n", (pDcgmAttr[i].identifiers.deviceName));
        dp("gpu UUID is %s\n", (pDcgmAttr[i].identifiers.uuid));
    }

    dp("\n");


    dcgmMigHierarchy_v2 hierarchy;
    hierarchy.version = dcgmMigHierarchy_version2;
    ret = dcgmGetGpuInstanceHierarchy(pDcgmHandle, &hierarchy);
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgmGetGpuInstanceHierarchy %d error\n", (int)ret);
    }
    for (unsigned int i = 0; i < hierarchy.count; i++){
        dp("%d mig found\n", i);
        dp("mig's gpu instance/compute instance is %d/%d\n", hierarchy.entityList[i].info.nvmlInstanceId, hierarchy.entityList[i].info.nvmlComputeInstanceId);
        dp("entity information %d/%d\n",  hierarchy.entityList[i].entity.entityGroupId, hierarchy.entityList[i].entity.entityId);
    }

    dp("\n");

    // dcgmGroupType_t type = DCGM_GROUP_DEFAULT_EVERYTHING;
    dcgmGroupType_t type = DCGM_GROUP_EMPTY;
    const char* group_name = "mig_group";
    dcgmGpuGrp_t pDcgmGrpId;
    ret = dcgmGroupCreate(pDcgmHandle, type, (char *)group_name, &pDcgmGrpId);
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgmGroupCreate error, exit\n");
        exit(0);
    }
    else{
        dp("group %ld created\n", pDcgmGrpId);
    }

    for (unsigned int i = 0; i < hierarchy.count; i++){
        ret = dcgmGroupAddEntity(pDcgmHandle, pDcgmGrpId, hierarchy.entityList[i].entity.entityGroupId, hierarchy.entityList[i].entity.entityId);
        if (ret != DCGM_ST_OK)
        {
            dlp(); dp("dcgmGroupAddEntity error %d\n", ret);
        }
    }

    ret = dcgmGroupAddDevice(pDcgmHandle, pDcgmGrpId, 1);
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgmGroupAddDevice error\n");
    }
    // dcgmGroupInfo_t pDcgmGroupInfo;
    // pDcgmGroupInfo.version = dcgmGroupInfo_version2;
    // ret = dcgmGroupGetInfo(pDcgmHandle, pDcgmGrpId, &pDcgmGroupInfo);
    // if (ret != DCGM_ST_OK)
    // {
    //     dlp(); dp("dcgmGroupGetInfo error %d\n", ret);
    // }
    // for (int i = 0;i < pDcgmGroupInfo.count; i++)
    // {
    //     dp("%d/%d\n", pDcgmGroupInfo.entityList[i].entityGroupId, pDcgmGroupInfo.entityList[i].entityId);
    // }

    dp("\n");   

    // int  numFieldIds = 5;
    // unsigned short fieldIds[numFieldIds] = {DCGM_FI_PROF_GR_ENGINE_ACTIVE, DCGM_FI_PROF_SM_ACTIVE, DCGM_FI_PROF_DRAM_ACTIVE, DCGM_FI_PROF_PCIE_TX_BYTES, DCGM_FI_PROF_PCIE_RX_BYTES};
    int  numFieldIds = 3;
    unsigned short fieldIds[3] = {DCGM_FI_PROF_GR_ENGINE_ACTIVE, DCGM_FI_PROF_SM_ACTIVE, DCGM_FI_PROF_DRAM_ACTIVE};
    const char* fieldGroupName = "profiling";
    dcgmFieldGrp_t dcgmFieldGroupId;
    ret = dcgmFieldGroupCreate(pDcgmHandle, numFieldIds, fieldIds, (char *)fieldGroupName, &dcgmFieldGroupId);
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgmFieldGroupCreate %d error\n", (int)ret);
    }
    else{
        dp("field group %ld created\n", dcgmFieldGroupId);
    }

    dp("\n");

    long long updateFreq = 1000000; // 1sec
    double maxKeepAge = 1;
    int maxKeepSamples = 1;
    ret = dcgmWatchFields(pDcgmHandle, pDcgmGrpId, dcgmFieldGroupId, updateFreq, maxKeepAge, maxKeepSamples);
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgmWatchFields %d error\n", (int)ret);
    }
    // dcgmProfWatchFields_t watchFields;
    // watchFields.version = 1;
    // watchFields.groupId = pDcgmGrpId;
    // watchFields.updateFreq = updateFreq;
    // watchFields.maxKeepAge = maxKeepAge;
    // watchFields.maxKeepSamples = maxKeepSamples;
    // watchFields.numFieldIds = numFieldIds;
    // watchFields.fieldIds[0] = fieldIds[0];
    // watchFields.fieldIds[1] = fieldIds[1];

    // ret = dcgmProfWatchFields(pDcgmHandle, &watchFields);
    // if (ret != DCGM_ST_OK)
    // {
    //     dlp(); dp("dcgmProfWatchFields %d error\n", (int)ret);
    // }
    else{
        dp("dcgm watch fields\n");
    }

    void* userData = NULL;
    // dcgmPidInfo_t pidInfo;
    // pidInfo.version = dcgmPidInfo_version;
    // pidInfo.pid = 30335;

    // ret = dcgmWatchPidFields(pDcgmHandle, pDcgmGrpId, updateFreq, maxKeepAge, maxKeepSamples);
    // if (ret != DCGM_ST_OK)
    // {
    //     dlp(); dp("dcgmWatchPidFields %d error\n", (int)ret);
    // }

    dp("\n");

    // ret = dcgmGetPidInfo(pDcgmHandle, pDcgmGrpId, &pidInfo);
    // printf("%d pid: %d, pid numGPU %d, summary.gpuID: %d, aver utilization: %lld\n", ret, pidInfo.pid, pidInfo.numGpus, pidInfo.summary.gpuId, pidInfo.summary.smUtilization.average);

    ret = dcgmGetLatestValues_v2(pDcgmHandle, pDcgmGrpId, dcgmFieldGroupId, (dcgmFieldValueEntityEnumeration_f)(&callback_func), userData);
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgmGetLatestValues_v2 %d error\n", (int)ret);
    }

    // initscr();
    // while (true)
    // {
    //     move(0,0);
    //     ret = dcgmGetLatestValues_v2(pDcgmHandle, pDcgmGrpId, dcgmFieldGroupId, (dcgmFieldValueEntityEnumeration_f)(&callback_func), userData);
    //     if (ret != DCGM_ST_OK)
    //     {
    //         dlp(); dp("dcgmGetLatestValues_v2 %d error\n", (int)ret);
    //     }
    //     refresh();

    //     // dcgmUpdateAllFields(pDcgmHandle, 0);
    //     // ret = dcgmGetPidInfo(pDcgmHandle, pDcgmGrpId, &pidInfo);
    //     // printw("%d pid: %d, pid numGPU %d, summary.gpuID: %d, aver utilization: %lld\n", ret, pidInfo.pid, pidInfo.numGpus, pidInfo.summary.gpuId, pidInfo.summary.smUtilization.average);

    //     // dcgmProfPause(pDcgmHandle);
    //     // dcgmProfResume(pDcgmHandle);

    //     // dcgmUpdateAllFields(pDcgmHandle, 0);

    //     // usleep(updateFreq);
    //     sleep(1);
    // }
    // endwin();

    // dp("\n");

    // sleep(maxKeepAge);
    // dcgmProfUnwatchFields_t unwatchFields;
    // unwatchFields.version = 1;
    // unwatchFields.groupId = pDcgmGrpId;
    // ret = dcgmProfUnwatchFields(pDcgmHandle, &unwatchFields);
    // if (ret != DCGM_ST_OK)
    // {
    //     dlp(); dp("dcgmProfUnwatchFields %d error\n", (int)ret);
    // }
    ret = dcgmUnwatchFields(pDcgmHandle, pDcgmGrpId, dcgmFieldGroupId);
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgmUnwatchFields %d error\n", (int)ret);
    }
    else{
        dp("dcgm unwatch fields\n");
    }

    dp("\n");   

    ret = dcgmGroupDestroy(pDcgmHandle, pDcgmGrpId);
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgmGroupDestroy error, exit\n");
        exit(0);
    }
    else{
        dp("Successfully destroy %ld group\n", pDcgmGrpId);
    }

    dp("\n");   

    ret = dcgmShutdown();
    if (ret != DCGM_ST_OK)
    {
        dlp(); dp("dcgm shutdown error, exit\n");
        exit(0);
    }
    else{
        dp("dcgm shutdown\n");
    }

    return 0;
}
