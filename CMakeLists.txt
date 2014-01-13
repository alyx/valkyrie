CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#SET(INCLUDE_PLAT /usr/local/include)
#connection.c  io.c  logger.c  main.c  match.c  object.c  sharedheap.c
#sourceinfo.c  strshare.c
SET(VALKYRIE_SRCS src/connection.c src/datastream.c src/logger.c src/main.c
    src/match.c src/object.c src/sharedheap.c src/sourceinfo.c src/strshare.c
    src/users.c)
#SET(VALKYRIE_SRCS src/io.c src/logger.c src/main.c src/match.c src/object.c
    #src/sharedheap.c src/strshare.c)
SET(CMAKE_C_COMPILER "icc")
SET(CMAKE_C_FLAGS "-w3")
INCLUDE_DIRECTORIES(include ${INCLUDE_PLAT})
ADD_EXECUTABLE(valkyrie ${VALKYRIE_SRCS})
TARGET_LINK_LIBRARIES(valkyrie mowgli-2)
