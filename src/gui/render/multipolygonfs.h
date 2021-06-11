//
// Created by km on 6/11/21.
//

#ifndef GISL_MULTIPOLYGONFS_H
#define GISL_MULTIPOLYGONFS_H

#include <string>

const std::string MultiPolygonFS = "#version 330 core\n"
                                   "in vec4 ourColor;\n"
                                   "out vec4 fColor;\n"
                                   "void main() {\n"
                                   "fColor = vec4(ourColor);\n"
                                   "}\n";

#endif // GISL_MULTIPOLYGONFS_H
