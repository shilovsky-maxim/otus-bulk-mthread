cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED ENV{GITHUB_RUN_NUMBER})
    set(ENV{GITHUB_RUN_NUMBER} 1)
endif()

project(bulk VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
add_executable(bulk bulk.cpp 
                    command.cpp 
                    base_block.cpp
                    static_block.cpp 
                    dynamic_block.cpp
                    default_block_factory.cpp
                    standard_printer.cpp
                    file_printer.cpp
                    composite_printer.cpp)

set_target_properties(bulk PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(bulk PRIVAT-E
        /W4
    )
else ()
    target_compile_options(bulk PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT max-in-3d@ngs.ru)

include(CPack)


