set(BINARY_TOOLS_LIST)

set(TMP_PACKAGING_DIR "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/M2SL-Binaries-")
file(MAKE_DIRECTORY ${TMP_PACKAGING_DIR})

if (NOT WIN32)
  foreach(binary_file ${BINARY_TOOLS_LIST})
    file(COPY "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/bin/${binary_file}" DESTINATION "${TMP_PACKAGING_DIR}")
  endforeach()

  execute_process(
    WORKING_DIRECTORY /home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP
    COMMAND zip -r M2SL-Binaries-.zip M2SL-Binaries-)
else()
  foreach(binary_file ${BINARY_TOOLS_LIST})
    file(COPY "/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/bin/Release/${binary_file}.exe" DESTINATION "${TMP_PACKAGING_DIR}")
  endforeach()
endif()
