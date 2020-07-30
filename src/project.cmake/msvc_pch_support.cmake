## *** taken from http://stackoverflow.com/questions/148570/using-pre-compiled-headers-with-cmake    ***
## But slightly modified, so the PrecompiledSource file could be listed in the SourceVar already.
## That is helpful during the definition of source files and headers and if it's not a MSVS build,
## this source file (normally stdafx.cpp) is definitely needed in the sources.
##
## USAGE EXAMPLE:
##   SET(SOURCES main.cpp stdafx.cpp)
##   SET(HEADERS main.h stdafx.h)
##   ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" SOURCES)
##   ADD_EXECUTABLE(main ${SOURCES} ${HEADERS}
##
## Modified Version by John Luthgers, 20.03.2014
##
MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
    MESSAGE(STATUS "Setting up precompiler header support")
    GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    SET(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")
    SET(Sources ${${SourcesVar}})

    SET_SOURCE_FILES_PROPERTIES(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledBinary}\" /FI\"${PrecompiledBinary}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")

    SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")

    LIST(FIND ${SourcesVar} ${PrecompiledSource} PrecompiledSourceIndex)
    IF(${PrecompiledSourceIndex} EQUAL -1)
        LIST(APPEND ${SourcesVar} ${PrecompiledSource})
    ENDIF(${PrecompiledSourceIndex} EQUAL -1)
  ENDIF(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

