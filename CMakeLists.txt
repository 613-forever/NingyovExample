macro(addExampleScene NAME)
    add_executable(Example${NAME}Scene EXCLUDE_FROM_ALL "${PROJECT_SOURCE_DIR}/examples/src/Example${NAME}Scene.cpp")
    target_link_libraries(Example${NAME}Scene PRIVATE ${PROJECT_NAME})
    target_compile_definitions(Example${NAME}Scene PRIVATE
            "CLIP_DIR=${PROJECT_SOURCE_DIR}/examples/images/"
            "UNPACKED_DIR=${PROJECT_SOURCE_DIR}/examples/images/"
            "CACHE_ROOT_DIR=${PROJECT_SOURCE_DIR}/examples/generated/"
            "FONT_DIR=${FONT_DIR}"
            )
endmacro()

addExampleScene(Simple) # Static.
addExampleScene(Dialog) # Standing drawing with a moving mouth.
addExampleScene(DialogText) # Not only standing drawings but animated text.
addExampleScene(MultiShot) # Multiple shots.

macro(addAbstractionExampleScene NAME)
    add_executable(Example${NAME}Scene EXCLUDE_FROM_ALL "${PROJECT_SOURCE_DIR}/examples/src/Example${NAME}Scene.cpp")
    target_link_libraries(Example${NAME}Scene PRIVATE ${PROJECT_NAME} ${PROJECT_NAME}_FACADE)
    target_compile_definitions(Example${NAME}Scene PRIVATE
            "CLIP_DIR=${PROJECT_SOURCE_DIR}/examples/images/"
            "UNPACKED_DIR=${PROJECT_SOURCE_DIR}/examples/images/"
            "CACHE_ROOT_DIR=${PROJECT_SOURCE_DIR}/examples/generated/"
            "FONT_DIR=${FONT_DIR}"
            )
endmacro()

addAbstractionExampleScene(Character) # Character interface.
