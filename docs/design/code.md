# 源码实现

本软件参考 QGIS 实现大多数功能，但在 QGIS 基础上做到增强，下面便是核心算法实现与
QGIS 实现对比。

## 矢量读取

使用内存和显存同时存储矢量信息，显存通过 GLSL 渲染界面。

```glsl
layout(location = 0) in vec2 inVertex;
gl_Position = matrix * vec4(inVertex, 0.0f, 1.0f);
```
