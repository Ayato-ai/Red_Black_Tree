set(target ${RED_BLACK_TREE_CUSTOM})

file(GLOB hdrs "*.h*")

add_custom_target(${target} SOURCES ${hdrs})