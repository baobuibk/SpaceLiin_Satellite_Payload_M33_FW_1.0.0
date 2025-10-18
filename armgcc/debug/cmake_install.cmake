# Install script for directory: F:/F00_Workspace/03_SATEXP_IMX93/A04_Project/AF_IPCDEV/payexp/armgcc

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Users/CAO HIEU/.mcuxpressotools/arm-gnu-toolchain-14.2.rel1-mingw-w64-x86_64-arm-none-eabi/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("F:/F00_Workspace/03_SATEXP_IMX93/A04_Project/AF_IPCDEV/payexp/armgcc/debug/M0_App/cmake_install.cmake")
  include("F:/F00_Workspace/03_SATEXP_IMX93/A04_Project/AF_IPCDEV/payexp/armgcc/debug/M1_SysApp/cmake_install.cmake")
  include("F:/F00_Workspace/03_SATEXP_IMX93/A04_Project/AF_IPCDEV/payexp/armgcc/debug/M2_BSP/cmake_install.cmake")
  include("F:/F00_Workspace/03_SATEXP_IMX93/A04_Project/AF_IPCDEV/payexp/armgcc/debug/M3_Devices/cmake_install.cmake")
  include("F:/F00_Workspace/03_SATEXP_IMX93/A04_Project/AF_IPCDEV/payexp/armgcc/debug/M4_Middlewares/cmake_install.cmake")
  include("F:/F00_Workspace/03_SATEXP_IMX93/A04_Project/AF_IPCDEV/payexp/armgcc/debug/M5_Utils/cmake_install.cmake")
  include("F:/F00_Workspace/03_SATEXP_IMX93/A04_Project/AF_IPCDEV/payexp/armgcc/debug/M6_Tools/cmake_install.cmake")
  include("F:/F00_Workspace/03_SATEXP_IMX93/A04_Project/AF_IPCDEV/payexp/armgcc/debug/M7_Tests/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "F:/F00_Workspace/03_SATEXP_IMX93/A04_Project/AF_IPCDEV/payexp/armgcc/debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
