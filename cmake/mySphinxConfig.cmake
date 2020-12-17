

add_sphinx_doc(
        SOURCE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/docs
        BUILD_DIR
        ${CMAKE_CURRENT_BINARY_DIR}/_build
        CACHE_DIR
        ${CMAKE_CURRENT_BINARY_DIR}/_doctrees
        HTML_DIR
        ${CMAKE_CURRENT_BINARY_DIR}/sphinx_html
        CONF_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/docs/conf.py.in
        TARGET_NAME
        sphinx_docs
        COMMENT
        "HTML documentation"
)