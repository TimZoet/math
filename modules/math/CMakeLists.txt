set(NAME math)
set(TYPE module)
set(INCLUDE_DIR "include/math")
set(SRC_DIR "src")

set(HEADERS
    ${INCLUDE_DIR}/compilation_info.h
    ${INCLUDE_DIR}/constants.h
    ${INCLUDE_DIR}/foldpoly.h
    ${INCLUDE_DIR}/include_all.h
    ${INCLUDE_DIR}/math_functions.h
    ${INCLUDE_DIR}/math_type_traits.h
    ${INCLUDE_DIR}/space_conversion.h
    
    ${INCLUDE_DIR}/aabb/aabb.h
    ${INCLUDE_DIR}/aabb/aabb2.h
    ${INCLUDE_DIR}/aabb/aabb3.h
    
    ${INCLUDE_DIR}/matrix/mat4x4.h
    ${INCLUDE_DIR}/matrix/matrix.h
    
    ${INCLUDE_DIR}/matrix/simd/mat4x4fa.h
    
    ${INCLUDE_DIR}/vector/vec2.h
    ${INCLUDE_DIR}/vector/vec3.h
    ${INCLUDE_DIR}/vector/vec4.h
    ${INCLUDE_DIR}/vector/vec8.h
    ${INCLUDE_DIR}/vector/vector.h
    ${INCLUDE_DIR}/vector/vector_type_traits.h
    
    ${INCLUDE_DIR}/vector/simd/vec3ba.h
    ${INCLUDE_DIR}/vector/simd/vec3fa.h
    ${INCLUDE_DIR}/vector/simd/vec3ia.h
    ${INCLUDE_DIR}/vector/simd/vec4ba.h
    ${INCLUDE_DIR}/vector/simd/vec4fa.h
    ${INCLUDE_DIR}/vector/simd/vec4ia.h
    ${INCLUDE_DIR}/vector/simd/vec8ba.h
    ${INCLUDE_DIR}/vector/simd/vec8fa.h
    ${INCLUDE_DIR}/vector/simd/vec8ia.h
 )

set(SOURCES
    ${SRC_DIR}/liboutput.cpp
)

make_target(
    NAME ${NAME}
    TYPE ${TYPE}
    VERSION ${MATH_VERSION}
    HEADERS "${HEADERS}"
    SOURCES "${SOURCES}"
)

install_target(
    NAME ${NAME}
    TYPE ${TYPE}
    VERSION ${MATH_VERSION}
    HEADERS "${HEADERS}"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${NAME} PUBLIC "-march=native")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${NAME} PUBLIC "-march=native")
endif()