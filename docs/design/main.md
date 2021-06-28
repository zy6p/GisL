# GisL 设计思路

GisL 是一个 GIS 桌面软件，设计思路模仿 [QGIS](https://github.com/qgis/QGIS)，是
GIS 编程的一种实践。

## 技术选型

- [x] 整体设计和细节实现全部依照 QGIS
- [x] 界面使用 Qt
- [x] 底层地理数据读写使用 GDAL/OGR
- [x] 矢量图形绘制使用 OpenGL 和 QPainter
- [x] 部分地图绘制使用 GMT
- [x] 图表绘制使用 QWT
- [x] 计算机视觉部分使用 OpenCV
- [x] 文档生成使用 Doxygen 和 Sphinx
- [x] C++ 底层使用 absl
- [x] 单元测试使用 Catch2
- [x] 矩阵库使用 Eigen

## 整体架构

- 主程序分为 4 个模块，分别是 `core`(包括 `gui`), `ui`, `codecvt`, `utils`,
  `analysis`
- `core` 模块包含 `geometry`, `provider`, `layer`, `vector`, `raster`
- `gui` 模块包括 `gui`, `command`, `render`, `painter`, `symbolizer`
- GUI 和 CLI 均支持，程序可以在脱离 GUI 情况下运行
- `codecvt` 模块能实现读写自定义二进制数据
- `utils` 模块包括一些可复用工具
- `analysis` 模块包括一些栅格分析算法
