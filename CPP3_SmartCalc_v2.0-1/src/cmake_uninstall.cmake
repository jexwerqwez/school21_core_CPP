if(NOT EXISTS "/home/jexwerqwez/Desktop/CPP3_SmartCalc_v2.0-1/src/install_manifest.txt")
    message(FATAL_ERROR "Файл install_manifest.txt не найден.")
endif()

file(READ "/home/jexwerqwez/Desktop/CPP3_SmartCalc_v2.0-1/src/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
    message(STATUS "Удаляется файл: ${file}")
    if(EXISTS "${file}")
        file(REMOVE "${file}")
    endif()
endforeach()
