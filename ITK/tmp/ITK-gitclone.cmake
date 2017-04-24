if("origin/release" STREQUAL "")
  message(FATAL_ERROR "Tag for git checkout should not be empty.")
endif()

set(run 0)

if("/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK/src/ITK-stamp/ITK-gitinfo.txt" IS_NEWER_THAN "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK/src/ITK-stamp/ITK-gitclone-lastrun.txt")
  set(run 1)
endif()

if(NOT run)
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK/src/ITK-stamp/ITK-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK'")
endif()

# try the clone 3 times incase there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git" clone --origin "origin" "https://github.com/InsightSoftwareConsortium/ITK.git" "ITK"
    WORKING_DIRECTORY "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/InsightSoftwareConsortium/ITK.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git" checkout origin/release
  WORKING_DIRECTORY "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'origin/release'")
endif()

execute_process(
  COMMAND "/usr/bin/git" submodule init 
  WORKING_DIRECTORY "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to init submodules in: '/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK'")
endif()

execute_process(
  COMMAND "/usr/bin/git" submodule update --recursive 
  WORKING_DIRECTORY "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK/src/ITK-stamp/ITK-gitinfo.txt"
    "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK/src/ITK-stamp/ITK-gitclone-lastrun.txt"
  WORKING_DIRECTORY "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/External-Projects/ITK/src/ITK-stamp/ITK-gitclone-lastrun.txt'")
endif()

