# Install script for directory: /home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/wallace/Coding/EventsBus/get_Started/build/third_party/EventBUs/lib/libEventBus.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/EventBus" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES
    "/home/wallace/Coding/EventsBus/get_Started/build/third_party/EventBUs/lib/generated/EventBusConfig.cmake"
    "/home/wallace/Coding/EventsBus/get_Started/build/third_party/EventBUs/lib/generated/EventBusConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/EventBus/EventBusTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/EventBus/EventBusTargets.cmake"
         "/home/wallace/Coding/EventsBus/get_Started/build/third_party/EventBUs/lib/CMakeFiles/Export/lib/cmake/EventBus/EventBusTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/EventBus/EventBusTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/EventBus/EventBusTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/EventBus" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/build/third_party/EventBUs/lib/CMakeFiles/Export/lib/cmake/EventBus/EventBusTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/EventBus" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/build/third_party/EventBUs/lib/CMakeFiles/Export/lib/cmake/EventBus/EventBusTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/EventBus.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/Bus.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus/internal" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/internal/event_id.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus/internal" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/internal/listener_traits.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus/internal" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/internal/ListenerAttorney.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/Listener.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus/perk" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/perk/PassPerk.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus/perk" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/perk/Perk.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus/perk" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/perk/PerkEventBus.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus/perk" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/perk/TagPerk.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus/perk" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/perk/WaitPerk.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus/permission" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/permission/PostponeBus.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus/stream" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/stream/EventStream.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dexode/eventbus/stream" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_READ FILES "/home/wallace/Coding/EventsBus/get_Started/third_party/EventBUs/lib/src/dexode/eventbus/stream/ProtectedEventStream.hpp")
endif()

