# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Covek-samo-srcem-dobro-vidi_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Covek-samo-srcem-dobro-vidi_autogen.dir/ParseCache.txt"
  "Covek-samo-srcem-dobro-vidi_autogen"
  )
endif()
