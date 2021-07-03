# 源码实现

本软件参考 QGIS 实现大多数功能，但在 QGIS 基础上做到增强，下面便是核心算法实现与
QGIS 实现对比。

## 矢量渲染

使用内存和显存同时存储矢量信息，显存通过 GLSL 渲染界面。UI 渲染与后台逻辑分离互
不干扰，让用户体验更流畅。相比 QGIS，其使用一帧一渲染，每次绘制时都会产生巨大了
传输开销，从内存到显存，并且从 double 到 float32 损失了部分精度。

1. GisL 实现
<pre><code class="glsl">layout(location = 0) in vec2 inVertex;
gl_Position = matrix * vec4(inVertex, 0.0f, 1.0f);
</code></pre>

2. QGIS 实现

```c++
void QgsPoint::draw( QPainter &p ) const
{
  p.drawRect( QRectF( mX - 2, mY - 2, 4, 4 ) );
}
```

## 栅格读取

本软件一次性将栅格数据全部读到内存之中，再进行下一步处理与绘制。做到一次读取，重
复使用。而 QGIS 则采取随用随读，按需读取，虽然能减少内存使用，但频繁进行磁盘 IO
操作、频繁对内存进行分配与销毁，造成处理低效，经常掉帧。

1. GisL 实现

```c++
T* rowBuff = (T*)CPLMalloc(nbytes * xSize * ySize);
if (1 != pmRasterBand->RasterIO( GF_Read, 0, 0, xSize, ySize, rowBuff, xSize, ySize, t, 0, 0)) {
  this->mErr = LayerErr::DataErr;
}

for (int row = 0; row < ySize; ++row) {
  for (int col = 0; col < xSize; col++) { // iterate through columns
    fData(row, col) = (float)rowBuff[row * xSize + col];
  }
}
CPLFree(rowBuff);
```

2. QGIS 实现

```c++
CPLErr QgsGdalProviderBase::gdalRasterIO( GDALRasterBandH hBand, GDALRWFlag eRWFlag, int nXOff, int nYOff, int nXSize, int nYSize, void *pData, int nBufXSize, int nBufYSize, GDALDataType eBufType, int nPixelSpace, int nLineSpace, QgsRasterBlockFeedback *feedback )
{
  GDALRasterIOExtraArg extra;
  INIT_RASTERIO_EXTRA_ARG( extra );
  if ( false && feedback )  // disabled!
  {
    extra.pfnProgress = _gdalProgressFnWithFeedback;
    extra.pProgressData = ( void * ) feedback;
  }
  CPLErr err = GDALRasterIOEx( hBand, eRWFlag, nXOff, nYOff, nXSize, nYSize, pData, nBufXSize, nBufYSize, eBufType, nPixelSpace, nLineSpace, &extra );
  return err;
}
```

## 模块化

使用 CMake 作为构建系统，引入大量宏，做到模块分离解耦合。如 GUI 模块，完全可以舍
去，在纯命令行下运行，方便进行单元测试。再如空间分析模块，仅在需要时构建。再如工
具模块，包含有指针、字符串等工具，完全可以单独拎出来在外部其他程序中使用，做到代
码复用。

具体实现与 QGIS 别无二致，优秀的代码总是殊途同归。

```c++
#ifdef WITH_ANALYSIS
  std::shared_ptr<gisl::Analysis> pAnalysis = gisl::Analysis::instance();
  void registerAnalysis();
#endif
```
