# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

# THE VERSION NUMBER
SET (MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION 2)
SET (MCUXPRESSO_CMAKE_FORMAT_MINOR_VERSION 0)

if(CMAKE_SCRIPT_MODE_FILE)
  message("${MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION}")
  return()
endif()


# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/../02_OUTPUT/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${ProjDirPath}/../02_OUTPUT/${CMAKE_BUILD_TYPE})

project(payexp_m33 C ASM)

set(MCUX_BUILD_TYPES debug release)

set(MCUX_SDK_PROJECT_NAME payexp_m33.elf)

if (NOT DEFINED SdkRootDirPath)
    SET(SdkRootDirPath ${ProjDirPath}/../../../../..)
endif()

set(SDK_ROOT_PATH "${SdkRootDirPath}" CACHE INTERNAL "Path to SDK root")

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

# target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
#     ${ProjDirPath}/..
#     ${ProjDirPath}/../01_DEV/M5_Utils
# )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ProjDirPath}/../02_OUTPUT/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ProjDirPath}/../02_OUTPUT/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ProjDirPath}/../02_OUTPUT/${CMAKE_BUILD_TYPE})

# ----------------------------------------
# SOURCE FILES
# ----------------------------------------
add_executable(${MCUX_SDK_PROJECT_NAME}
    ${ProjDirPath}/../Core/Src/main.c
    ${ProjDirPath}/../Core/Src/MIMX9352cm33_it.c
    ${ProjDirPath}/../Core/Src/board.c
    ${ProjDirPath}/../Core/Src/clock_config.c
    ${ProjDirPath}/../Core/Src/pin_mux.c
    ${ProjDirPath}/../Core/Src/FreeRTOSConfig.h
)

# ----------------------------------------
# INCLUDE PATHS
# ----------------------------------------
target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/../Core/Inc
    ${ProjDirPath}/../Core/Src
    ${ProjDirPath}/..
)

# ----------------------------------------
# SDK + SUBMODULES
# ----------------------------------------

set_source_files_properties("${ProjDirPath}/../FreeRTOSConfig.h" PROPERTIES COMPONENT_CONFIG_FILE "middleware_freertos-kernel_template")

include(${SdkRootDirPath}/devices/MIMX9352/all_lib_device.cmake)

include(${ProjDirPath}/../cmake/exp_sdk_common.cmake)

set(PROJECT_SDK_INCLUDE_DIRS

    ${SdkRootDirPath}/rtos/freertos/freertos-kernel/include
    ${SdkRootDirPath}/rtos/freertos/freertos-kernel/portable/GCC/ARM_CM33_NTZ/non_secure

    ${ProjDirPath}/../Core/src        
)

set(PROJECT_GLOBAL_INCLUDE_DIRS
    ${ProjDirPath}/../01_DEV/M1_SysApp
    ${ProjDirPath}/../01_DEV/M5_Utils
    ${PROJECT_SDK_INCLUDE_DIRS} 
)

add_subdirectory(${ProjDirPath}/../01_DEV/M0_App        ${CMAKE_BINARY_DIR}/M0_App)
add_subdirectory(${ProjDirPath}/../01_DEV/M1_SysApp     ${CMAKE_BINARY_DIR}/M1_SysApp)
add_subdirectory(${ProjDirPath}/../01_DEV/M2_BSP        ${CMAKE_BINARY_DIR}/M2_BSP)
add_subdirectory(${ProjDirPath}/../01_DEV/M3_Devices    ${CMAKE_BINARY_DIR}/M3_Devices)
add_subdirectory(${ProjDirPath}/../01_DEV/M4_Middlewares ${CMAKE_BINARY_DIR}/M4_Middlewares)
add_subdirectory(${ProjDirPath}/../01_DEV/M5_Utils      ${CMAKE_BINARY_DIR}/M5_Utils)
add_subdirectory(${ProjDirPath}/../01_DEV/M6_Tools      ${CMAKE_BINARY_DIR}/M6_Tools)
add_subdirectory(${ProjDirPath}/../01_DEV/M7_Tests      ${CMAKE_BINARY_DIR}/M7_Tests)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
    M0_App
    M1_SysApp
    M2_BSP
    M3_Devices
    M4_Middlewares
    M5_Utils
    M6_Tools
    M7_Tests
)

# ----------------------------------------
# LINKER SETTINGS
# ----------------------------------------

IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)  
    SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")  
ENDIF()  

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

# ----------------------------------------
# POST-BUILD: CREATE .BIN FILE
# ----------------------------------------

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/payexp_m33.bin)

# add_custom_command(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_OBJCOPY} -Obinary
#     # ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${MCUX_SDK_PROJECT_NAME}.elf
#     ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${MCUX_SDK_PROJECT_NAME}.bin
#     COMMENT "Converting ELF to BIN..."
# )
