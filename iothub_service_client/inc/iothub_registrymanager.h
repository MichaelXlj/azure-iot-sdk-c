// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// This file is under development and it is subject to change

#ifndef IOTHUB_REGISTRYMANAGER_H
#define IOTHUB_REGISTRYMANAGER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "azure_c_shared_utility/macro_utils.h"
#include "azure_c_shared_utility/umock_c_prod.h"
#include "azure_c_shared_utility/crt_abstractions.h"
#include "azure_c_shared_utility/singlylinkedlist.h"
#include "azure_c_shared_utility/map.h"
#include "iothub_service_client_auth.h"

#define IOTHUB_REGISTRYMANAGER_RESULT_VALUES        \
    IOTHUB_REGISTRYMANAGER_OK,                      \
    IOTHUB_REGISTRYMANAGER_INVALID_ARG,             \
    IOTHUB_REGISTRYMANAGER_ERROR,                   \
    IOTHUB_REGISTRYMANAGER_JSON_ERROR,              \
    IOTHUB_REGISTRYMANAGER_HTTPAPI_ERROR,           \
    IOTHUB_REGISTRYMANAGER_HTTP_STATUS_ERROR,       \
    IOTHUB_REGISTRYMANAGER_DEVICE_EXIST,            \
    IOTHUB_REGISTRYMANAGER_DEVICE_NOT_EXIST,        \
    IOTHUB_REGISTRYMANAGER_CALLBACK_NOT_SET,        \
    IOTHUB_REGISTRYMANAGER_INVALID_VERSION          \

DEFINE_ENUM(IOTHUB_REGISTRYMANAGER_RESULT, IOTHUB_REGISTRYMANAGER_RESULT_VALUES);

#define IOTHUB_REGISTRYMANAGER_AUTH_METHOD_VALUES           \
    IOTHUB_REGISTRYMANAGER_AUTH_SPK,                        \
    IOTHUB_REGISTRYMANAGER_AUTH_X509_THUMBPRINT,            \
    IOTHUB_REGISTRYMANAGER_AUTH_X509_CERTIFICATE_AUTHORITY, \
    IOTHUB_REGISTRYMANAGER_AUTH_NONE,                       \
    IOTHUB_REGISTRYMANAGER_AUTH_UNKNOWN                     \
    

DEFINE_ENUM(IOTHUB_REGISTRYMANAGER_AUTH_METHOD, IOTHUB_REGISTRYMANAGER_AUTH_METHOD_VALUES);

#define IOTHUB_DEVICE_EX_VERSION_1 1
typedef struct IOTHUB_DEVICE_EX_TAG
{
    int version;
    const char* deviceId;                           //version 1+
    const char* primaryKey;                         //version 1+
    const char* secondaryKey;                       //version 1+
    const char* generationId;                       //version 1+
    const char* eTag;                               //version 1+
    IOTHUB_DEVICE_CONNECTION_STATE connectionState; //version 1+
    const char* connectionStateUpdatedTime;         //version 1+
    IOTHUB_DEVICE_STATUS status;                    //version 1+
    const char* statusReason;                       //version 1+
    const char* statusUpdatedTime;                  //version 1+
    const char* lastActivityTime;                   //version 1+
    size_t cloudToDeviceMessageCount;               //version 1+

    bool isManaged;                                 //version 1+
    const char* configuration;                      //version 1+
    const char* deviceProperties;                   //version 1+
    const char* serviceProperties;                  //version 1+
    IOTHUB_REGISTRYMANAGER_AUTH_METHOD authMethod;  //version 1+

    bool iotEdge_capable;                           //version 1+
} IOTHUB_DEVICE_EX;

/**
* @brief    Free members of the IOTHUB_DEVICE_EX structure (NOT the structure itself)
*
* @param    deviceInfo      The structure to have its members freed.
*/
extern void IoTHubRegistryManager_FreeDeviceExMembers(IOTHUB_DEVICE_EX* deviceInfo);

#define IOTHUB_REGISTRY_DEVICE_CREATE_EX_VERSION_1 1
typedef struct IOTHUB_REGISTRY_DEVICE_CREATE_EX_TAG
{
    int version;
    const char* deviceId;                           //version 1+
    const char* primaryKey;                         //version 1+
    const char* secondaryKey;                       //version 1+
    IOTHUB_REGISTRYMANAGER_AUTH_METHOD authMethod;  //version 1+
    bool iotEdge_capable;                           //version 1+
} IOTHUB_REGISTRY_DEVICE_CREATE_EX;

#define IOTHUB_REGISTRY_DEVICE_UPDATE_EX_VERSION_1 1
typedef struct IOTHUB_REGISTRY_DEVICE_UPDATE_EX_TAG
{
    int version;
    const char* deviceId;                           //version 1+
    const char* primaryKey;                         //version 1+
    const char* secondaryKey;                       //version 1+
    IOTHUB_DEVICE_STATUS status;                    //version 1+
    IOTHUB_REGISTRYMANAGER_AUTH_METHOD authMethod;  //version 1+
    bool iotEdge_capable;                           //version 1+
} IOTHUB_REGISTRY_DEVICE_UPDATE_EX;

typedef struct IOTHUB_REGISTRY_STATISTIC_TAG
{
    size_t totalDeviceCount;
    size_t enabledDeviceCount;
    size_t disabledDeviceCount;
} IOTHUB_REGISTRY_STATISTICS;

#define IOTHUB_MODULE_VERSION_1 1
typedef struct IOTHUB_MODULE_TAG
{
    int version;
    const char* deviceId;
    const char* primaryKey;
    const char* secondaryKey;
    const char* generationId;
    const char* eTag;
    IOTHUB_DEVICE_CONNECTION_STATE connectionState;
    const char* connectionStateUpdatedTime;
    IOTHUB_DEVICE_STATUS status;
    const char* statusReason;
    const char* statusUpdatedTime;
    const char* lastActivityTime;
    size_t cloudToDeviceMessageCount;

    bool isManaged;
    const char* configuration;
    const char* deviceProperties;
    const char* serviceProperties;
    IOTHUB_REGISTRYMANAGER_AUTH_METHOD authMethod;

    const char* moduleId;
} IOTHUB_MODULE;

/**
* @brief    Free members of the IOTHUB_MODULE structure (NOT the structure itself)
*
* @param    moduleInfo      The structure to have its members freed.
*/
extern void IoTHubRegistryManager_FreeModuleMembers(IOTHUB_MODULE* moduleInfo);


#define IOTHUB_REGISTRY_MODULE_CREATE_VERSION_1 1
typedef struct IOTHUB_REGISTRY_MODULE_CREATE_TAG
{
    int version;
    const char* deviceId;                           //version 1+
    const char* primaryKey;                         //version 1+
    const char* secondaryKey;                       //version 1+
    IOTHUB_REGISTRYMANAGER_AUTH_METHOD authMethod;  //version 1+
    const char* moduleId;                           //version 1+
} IOTHUB_REGISTRY_MODULE_CREATE;

#define IOTHUB_REGISTRY_MODULE_UPDATE_VERSION_1 1
typedef struct IOTHUB_REGISTRY_MODULE_UPDATE_TAG
{
    int version;
    const char* deviceId;                           //version 1+
    const char* primaryKey;                         //version 1+
    const char* secondaryKey;                       //version 1+
    IOTHUB_DEVICE_STATUS status;                    //version 1+
    IOTHUB_REGISTRYMANAGER_AUTH_METHOD authMethod;  //version 1+
    const char* moduleId;                           //version 1+
} IOTHUB_REGISTRY_MODULE_UPDATE;

#define IOTHUB_CONFIGURATION_CONTENT_VERSION_1 1
typedef struct IOTHUB_REGISTRY_CONFIGURATION_CONTENT_TAG
{
    const char* deviceContent;                    //version 1+
    const char* moduleContent;                    //version 1+

} IOTHUB_REGISTRY_CONFIGURATION_CONTENT;

#define IOTHUB_CONFIGURATION_METRICS_VERSION_1 1
typedef struct IOTHUB_REGISTRY_CONFIGURATION_METRICS_TAG
{
    MAP_HANDLE results;                          //version 1+
    MAP_HANDLE queries;                          //version 1+

} IOTHUB_REGISTRY_CONFIGURATION_METRICS;

#define IOTHUB_CONFIGURATION_SCHEMA_VERSION_1 "1.0"
typedef struct IOTHUB_CONFIGURATION_TAG
{
    const char* schemaVersion;                                      //version 1+
    const char* configurationId;                                    //version 1+
    const char* targetCondition;                                    //version 1+
    const char* eTag;                                               //version 1+
    int priority;                                                   //version 1+

    IOTHUB_REGISTRY_CONFIGURATION_CONTENT content;                  //version 1+
    MAP_HANDLE labels;                                              //version 1+

    const char* contentType;                                        //version 1+
    const char* createdTimeUtc;
    const char* lastUpdatedTimeUtc;

    IOTHUB_REGISTRY_CONFIGURATION_METRICS metrics;                  //version 1+
    IOTHUB_REGISTRY_CONFIGURATION_METRICS systemMetrics;            //version 1+

} IOTHUB_CONFIGURATION;

typedef struct IOTHUB_REGISTRY_CONFIGURATION_CREATE_TAG
{
    const char* schemaVersion;                                      //version 1+
    const char* configurationId;                                    //version 1+
    const char* targetCondition;                                    //version 1+
    int priority;                                                   //version 1+

    IOTHUB_REGISTRY_CONFIGURATION_CONTENT configurationContent;     //version 1+
    MAP_HANDLE configurationLabels;                                 //version 1+

    IOTHUB_REGISTRY_CONFIGURATION_METRICS metrics;                  //version 1+
    IOTHUB_REGISTRY_CONFIGURATION_METRICS systemMetrics;            //version 1+
    
} IOTHUB_REGISTRY_CONFIGURATION_CREATE;

typedef struct IOTHUB_REGISTRY_CONFIGURATION_UPDATE_TAG
{
    const char* schemaVersion;                                      //version 1+
    const char* configurationId;                                    //version 1+
    const char* targetCondition;                                    //version 1+
    int priority;                                                   //version 1+

    MAP_HANDLE configurationLabels;                                 //version 1+

    IOTHUB_REGISTRY_CONFIGURATION_METRICS metrics;                  //version 1+
    IOTHUB_REGISTRY_CONFIGURATION_METRICS systemMetrics;            //version 1+

} IOTHUB_REGISTRY_CONFIGURATION_UPDATE;

/** @brief Structure to store IoTHub authentication information
*/
typedef struct IOTHUB_REGISTRYMANAGER_TAG
{
    char* hostname;
    char* iothubName;
    char* iothubSuffix;
    char* sharedAccessKey;
    char* keyName;
    char* deviceId;
} IOTHUB_REGISTRYMANAGER;

/** @brief Handle to hide struct and use it in consequent APIs
*/
typedef struct IOTHUB_REGISTRYMANAGER_TAG* IOTHUB_REGISTRYMANAGER_HANDLE;

/**
* @brief    Creates a IoT Hub Registry Manager handle for use it
*           in consequent APIs.
*
* @param    serviceClientHandle     Service client handle.
*
* @return   A non-NULL @c IOTHUB_REGISTRYMANAGER_HANDLE value that is used when
*           invoking other functions for IoT Hub REgistry Manager and @c NULL on failure.
*/
extern IOTHUB_REGISTRYMANAGER_HANDLE IoTHubRegistryManager_Create(IOTHUB_SERVICE_CLIENT_AUTH_HANDLE serviceClientHandle);

/**
* @brief    Disposes of resources allocated by the IoT Hub Registry Manager.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
*/
extern void IoTHubRegistryManager_Destroy(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle);

/**
* @brief    Creates a device on IoT Hub.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    deviceCreate            IOTHUB_REGISTRY_DEVICE_CREATE_EX structure containing
*                                   the new device Id, primaryKey (optional) and secondaryKey (optional)
* @param    device                  Input parameter, if it is not NULL will contain the created device info structure
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_CreateDevice_Ex(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const IOTHUB_REGISTRY_DEVICE_CREATE_EX* deviceCreate, IOTHUB_DEVICE_EX* device);

/**
* @brief    Gets device info for a given device.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    deviceId                The Id of the requested device.
* @param    device                  Input parameter, if it is not NULL will contain the requested device info structure
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_GetDevice_Ex(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const char* deviceId, IOTHUB_DEVICE_EX* device);

/**
* @brief    Updates a device on IoT Hub.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    deviceUpdate            IOTHUB_REGISTRY_DEVICE_UPDATE_EX structure containing
*                                   the new device Id, primaryKey (optional), secondaryKey (optional),
*                                   authentication method, and status
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_UpdateDevice_Ex(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, IOTHUB_REGISTRY_DEVICE_UPDATE_EX* deviceUpdate);

/**
* @brief    Deletes a given device.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    deviceId    The Id of the device to delete.
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_DeleteDevice(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const char* deviceId);

/**
* @brief    Gets the registry statistic info.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    registryStatistics      Input parameter, if it is not NULL will contain the requested registry info.
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_GetStatistics(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, IOTHUB_REGISTRY_STATISTICS* registryStatistics);

/**
* @brief    Creates a module on IoT Hub.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    moduleCreate            IOTHUB_REGISTRY_MODULE_CREATE structure containing
*                                   the existing deviceID, new module Id, primaryKey (optional) and secondaryKey (optional)
* @param    module                  Input parameter, if it is not NULL will contain the created module info structure
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_CreateModule(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const IOTHUB_REGISTRY_MODULE_CREATE* moduleCreate, IOTHUB_MODULE* module);

/**
* @brief    Gets module info for a given module.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    deviceId                The Id of the requested device.
* @param    moduleId                The Id of the requested module.
* @param    module                  Input parameter, if it is not NULL will contain the requested module info structure
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_GetModule(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const char* deviceId, const char* moduleId, IOTHUB_MODULE* module);

/**
* @brief    Updates a module on IoT Hub.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    moduleUpdate            IOTHUB_REGISTRY_MODULE_UPDATE structure containing
*                                   the new module Id, primaryKey (optional), secondaryKey (optional),
*                                   authentication method, and status
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_UpdateModule(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, IOTHUB_REGISTRY_MODULE_UPDATE* moduleUpdate);

/**
* @brief    Deletes a given module.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    deviceId                The Id of the device containing module to delete.
* @param    moduleId                The Id of the module to delete.
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_DeleteModule(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const char* deviceId, const char* moduleId);

/**
* @brief    Gets a list of modules registered on the specified device.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    deviceId                The device to get a list of modules from
* @param    moduleList              The linked list structure to hold the returned modules
* @param    module_version          The version of the module structure to return
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_GetModuleList(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const char* deviceId, SINGLYLINKEDLIST_HANDLE moduleList, int module_version);

/**
* @brief	Creates a configuration on IoT Hub.
*
* @param	registryManagerHandle   The handle created by a call to the create function.
* @param    configurationCreate     IOTHUB_REGISTRY_CONFIGURATION_CREATE structure containing
*                                   the new configuration Id and other optional parameters
* @param    configuration           Input parameter, if it is not NULL will contain the created configuration info structure
*
* @return	IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_CreateConfiguration(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const IOTHUB_REGISTRY_CONFIGURATION_CREATE* configurationCreate, IOTHUB_CONFIGURATION* configuration);

/**
* @brief    Gets configuration info for a given configuration.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    configurationId         The Id of the requested configuration.
* @param    configuration           Input parameter, if it is not NULL will contain the requested configuration info structure
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_GetConfiguration(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const char* configurationId, IOTHUB_CONFIGURATION* configuration);

/**
* @brief    Updates a configuration on IoT Hub.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    configurationUpdate     IOTHUB_REGISTRY_CONFIGURATION_UPDATE structure containing
*                                   the new configuration info. Note that configurationContent cannot be updated.
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_UpdateConfiguration(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, IOTHUB_REGISTRY_CONFIGURATION_UPDATE* configurationUpdate);

/**
* @brief    Deletes a given configuration.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    configurationId    The Id of the configuration to delete.
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_DeleteConfiguration(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const char* configurationId);


/* DEPRECATED: THE FOLLOWING APIS ARE DEPRECATED, AND ARE ONLY BEING KEPT FOR BACK COMPAT. PLEASE USE _EX EQUIVALENT ABOVE */
/* DEPRECATED: THE FOLLOWING APIS ARE DEPRECATED, AND ARE ONLY BEING KEPT FOR BACK COMPAT. PLEASE USE _EX EQUIVALENT ABOVE */
/* DEPRECATED: THE FOLLOWING APIS ARE DEPRECATED, AND ARE ONLY BEING KEPT FOR BACK COMPAT. PLEASE USE _EX EQUIVALENT ABOVE */

/* Please use IOTHUB_DEVICE_EX instead */
typedef struct IOTHUB_DEVICE_TAG
{
    const char* deviceId;
    const char* primaryKey;
    const char* secondaryKey;
    const char* generationId;
    const char* eTag;
    IOTHUB_DEVICE_CONNECTION_STATE connectionState;
    const char* connectionStateUpdatedTime;
    IOTHUB_DEVICE_STATUS status;
    const char* statusReason;
    const char* statusUpdatedTime;
    const char* lastActivityTime;
    size_t cloudToDeviceMessageCount;

    bool isManaged;
    const char* configuration;
    const char* deviceProperties;
    const char* serviceProperties;
    IOTHUB_REGISTRYMANAGER_AUTH_METHOD authMethod;
} IOTHUB_DEVICE;

/* Please use IOTHUB_REGISTRY_DEVICE_CREATE_EX instead */
typedef struct IOTHUB_REGISTRY_DEVICE_CREATE_TAG
{
    const char* deviceId;
    const char* primaryKey;
    const char* secondaryKey;
    IOTHUB_REGISTRYMANAGER_AUTH_METHOD authMethod;
} IOTHUB_REGISTRY_DEVICE_CREATE;

/* Please use IOTHUB_REGISTRY_DEVICE_UPDATED_EX instead */
typedef struct IOTHUB_REGISTRY_DEVICE_UPDATE_TAG
{
    const char* deviceId;
    const char* primaryKey;
    const char* secondaryKey;
    IOTHUB_DEVICE_STATUS status;
    IOTHUB_REGISTRYMANAGER_AUTH_METHOD authMethod;
} IOTHUB_REGISTRY_DEVICE_UPDATE;

/** DEPRECATED:: Use IoTHubRegistryManager_CreateDevice_Ex instead
* @brief    Creates a device on IoT Hub.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    deviceCreate            IOTHUB_REGISTRY_DEVICE_CREATE structure containing
*                                   the new device Id, primaryKey (optional) and secondaryKey (optional)
* @param    device                  Input parameter, if it is not NULL will contain the created device info structure
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_CreateDevice(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const IOTHUB_REGISTRY_DEVICE_CREATE* deviceCreate, IOTHUB_DEVICE* device);

/** DEPRECATED:: Use IoTHubRegistryManager_GetDevice_Ex instead
* @brief    Gets device info for a given device.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    deviceId                The Id of the requested device.
* @param    device                  Input parameter, if it is not NULL will contain the requested device info structure
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_GetDevice(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, const char* deviceId, IOTHUB_DEVICE* device);

/** DEPRECATED:: Use IoTHubRegistryManager_UpdateDevice_Ex instead
* @brief    Updates a device on IoT Hub.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    deviceUpdate            IOTHUB_REGISTRY_DEVICE_UPDATE structure containing
*                                   the new device Id, primaryKey (optional), secondaryKey (optional),
*                                   authentication method, and status
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_UpdateDevice(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, IOTHUB_REGISTRY_DEVICE_UPDATE* deviceUpdate);

/* *DEPRECATED:: IoTHubRegistryManager_GetDeviceList is deprecated and may be removed from a future release.
* @brief    Gets device a list of devices registered on the IoTHUb.
*
* @param    registryManagerHandle   The handle created by a call to the create function.
* @param    numberOfDevices         Number of devices requested.
* @param    deviceList              Input parameter, if it is not NULL will contain the requested list of devices.
*
* @return   IOTHUB_REGISTRYMANAGER_RESULT_OK upon success or an error code upon failure.
*/
extern IOTHUB_REGISTRYMANAGER_RESULT IoTHubRegistryManager_GetDeviceList(IOTHUB_REGISTRYMANAGER_HANDLE registryManagerHandle, size_t numberOfDevices, SINGLYLINKEDLIST_HANDLE deviceList);

#ifdef __cplusplus
}
#endif

#endif // IOTHUB_REGISTRYMANAGER_H
