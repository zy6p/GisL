//
// Created by km on 6/11/21.
//

#ifndef GISL_MULTIPOLYGONVS_H
#define GISL_MULTIPOLYGONVS_H

#include <string>

const std::string MultiPolygonVS =
    "#version 330 core\n"
    "layout(location = 0) in vec2 inVertex;\n"
    "uniform mediump mat4 matrix;\n"
    "uniform vec4 inColor;\n"
    "out vec4 ourColor;\n"
    "void main() {\n"
    "ourColor = inColor;\n"
    "gl_Position = matrix * vec4(inVertex, 0.0f, 1.0f);\n"
    "}\n";

#endif // GISL_MULTIPOLYGONVS_H
