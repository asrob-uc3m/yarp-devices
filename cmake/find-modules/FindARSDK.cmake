# Find the ARSDK v3 libraries and headers.
#
# Sets the following variables:
#
# ARSDK_FOUND        - System has ARSDK
# ARSDK_INCLUDE_DIRS - ARSDK include directories
# ARSDK_LINK_DIRS    - ARSDK library paths
# ARSDK_LIBRARIES    - ARSDK libraries

if(UNIX)
    find_path(ARSDK_USR_DIR include/libARSAL/ARSAL.h
                            PATHS ENV ARSDK ENV ARSDK_DIR)

    set(ARSDK_INCLUDE_DIRS ${ARSDK_USR_DIR}/include)

    set(ARSDK_LINK_DIRS ${ARSDK_USR_DIR}/lib)
    set(ARSDK_LIBRARIES)

    set(ARSDK_LIBRARIES arcontroller
                        ardiscovery
                        arnetwork
                        arnetworkal
                        arsal
                        arstream
                        arstream2
                        armavlink
                        json
                        armedia
                        arutils
                        curl
                        ardatatransfer
                        mux
                        pomp
                        crypto
                        ssl
                        #z
                        sdp
                        rtsp
                        futils
                        ulog)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ARSDK DEFAULT_MSG ARSDK_USR_DIR)

mark_as_advanced(ARSDK_USR_DIR)
