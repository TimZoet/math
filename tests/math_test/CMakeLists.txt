set(NAME math_test)
set(TYPE test)
set(INCLUDE_DIR "include/math_test")
set(SRC_DIR "src")

set(HEADERS
    ${INCLUDE_DIR}/vector_add.h
    ${INCLUDE_DIR}/vector_div.h
    ${INCLUDE_DIR}/vector_mul.h
    ${INCLUDE_DIR}/vector_sub.h
)

set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/vector_add.cpp
    ${SRC_DIR}/vector_div.cpp
    ${SRC_DIR}/vector_mul.cpp
    ${SRC_DIR}/vector_sub.cpp
)

set(DEPS_PRIVATE
    bettertest
	math
)

make_target(
    TYPE ${TYPE}
    NAME ${NAME}
    OUTDIR "tests"
    # WARNINGS WERROR
    STARTUP
    HEADERS "${HEADERS}"
    SOURCES "${SOURCES}"
    DEPS_PRIVATE "${DEPS_PRIVATE}"
)
