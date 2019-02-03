
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost REQUIRED COMPONENTS program_options)

if(Boost_FOUND)
  message(STATUS "Found boost program options")
else(Boost_FOUND)
  message(FATAL_ERROR "Could not find boost program options")
endif(Boost_FOUND)
