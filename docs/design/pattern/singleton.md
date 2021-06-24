# GisL 中的设计模式

软件开发中设计模式很重要。

## 单例模式

单例模式是最常见的设计模式，在本程序中也使用颇多。

### LayerTree

图层树是管理所有图层以及数据提供者的类，在一个软件中只存在一个目录树。

```c++
// src/core/layer/layertree.h
class LayerTree {
public:
  void append(int fid, VectorLayer* p);
  void append(int fid, RasterBand* p);
  void append(int fid, RasterProvider* p);
  void append(int fid, VectorProvider* p);

  static LayerTree* getLayerTree();
  [[nodiscard]] const LayerMap& getLayerMap() const noexcept;
  [[nodiscard]] const ProviderMap& getProviderMap() const noexcept;
  [[nodiscard]] const LayerClassifyMap& getLayerClassifyMap() const;
  [[nodiscard]] const ProviderClassifyMap& getProviderClassifyMap() const;

  Layer* getLayer(int fid);
  DataProvider* getProvider(int fid);
  ~LayerTree();

private:
  LayerTree() = default;

  LayerClassifyMap layerClassifyMap;
  ProviderClassifyMap providerClassifyMap;
  LayerMap layerMap;
  ProviderMap providerMap;

  static LayerTree* _layerTree;
}
```

```c++
// src/core/layer/layertree.cpp
gisl::LayerTree* gisl::LayerTree::_layerTree = nullptr;

void gisl::LayerTree::append(int fid, gisl::VectorLayer* p) {
  this->layerClassifyMap.insert(std::make_pair(fid, p));
  this->layerMap[fid] = p;
}
void gisl::LayerTree::append(int fid, gisl::RasterBand* p) {
  this->layerClassifyMap.insert(std::make_pair(fid, p));
  this->layerMap[fid] = p;
}
void gisl::LayerTree::append(int fid, gisl::RasterProvider* p) {
  this->providerClassifyMap.insert(std::make_pair(fid, p));
  gisl::LayerTree::providerMap[fid] = p;
}
void gisl::LayerTree::append(int fid, gisl::VectorProvider* p) {
  this->providerClassifyMap.insert(std::make_pair(fid, p));
  gisl::LayerTree::providerMap[fid] = p;
}

gisl::LayerTree* gisl::LayerTree::getLayerTree() {
  if (nullptr == gisl::LayerTree::_layerTree) {
    gisl::LayerTree::_layerTree = new gisl::LayerTree;
  }
  return gisl::LayerTree::_layerTree;
}

gisl::Layer* gisl::LayerTree::getLayer(int fid) { return layerMap[fid]; }

gisl::LayerTree::~LayerTree() {}

gisl::DataProvider* gisl::LayerTree::getProvider(int fid) {
  return providerMap[fid];
}
const gisl::LayerMap& gisl::LayerTree::getLayerMap() const noexcept {
  return this->layerMap;
}
const gisl::ProviderMap& gisl::LayerTree::getProviderMap() const noexcept {
  return this->providerMap;
}
const gisl::LayerClassifyMap& gisl::LayerTree::getLayerClassifyMap() const {
  return layerClassifyMap;
}
```

此处使用懒加载，在第一次调用时进行初始化。

### Analysis

在 GUI 下的 `mainwindow.cpp` 中存在唯一 Analysis 类的实例，这个实例负责注册算法
并进行信号槽绑定。由于 `mainwindow.cpp` 中仅实例化一次，所以 Analysis 无需完全遵
循单例模式的写法。CLI 程序无需实例化 Analysis 类。

```c++
#ifdef WITH_ANALYSIS
  this->registerAnalysis();
#endif
```

同时此处还使用宏，做到按模块加载。

参考 QGIS 中Analysis 模块实现如下：

```cmake
if (WITH_ANALYSIS)
  add_subdirectory(analysis)
endif()
```
