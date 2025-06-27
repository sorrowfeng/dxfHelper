# 📐 `dxf_reader` - 全新封装的 DXF 解析库

> ✅ **项目地址：** [GitHub - sorrowfeng/dxf_reader](https://github.com/sorrowfeng/dxf_reader)  
> 💡 一个更加直观、清晰、易用的 DXF 文件解析库，专为 Qt/C++ 项目打造。

---

# 📐 `dxfHelper` - Qt 中的 DXF 文件解析工具

基于 [dxflib](https://github.com/sorrowfeng/dxf_reader) 的现代化封装，为 CAD 数据处理提供**简洁高效**的解决方案。

<div align="center">
  <img src="https://img-blog.csdnimg.cn/direct/37826cdb9fc141a1b3b2803be55ca081.png" width="45%" alt="原始DXF文件"/>
  <img src="https://img-blog.csdnimg.cn/direct/1512fb7adeb54fb59682212b0a2b3c7d.png" width="45%" alt="解析后效果"/>
</div>

---

## 🔧 主要特性

| ✅ 特性 | 📝 描述 |
|--------|---------|
| **统一实体接口** | 所有图形实体继承自 `DL_Entity` 基类，支持多态操作 |
| **完整属性支持** | 提供图层、线型、颜色、线宽等完整属性访问 |
| **结构化数据** | 优化多段线和样条曲线的数据结构，便于访问与处理 |
| **高性能解析** | 使用智能指针管理内存，支持大文件快速加载 |
| **扩展性强** | 易于添加新的实体类型和自定义属性 |

---

## 📦 开源协议

该项目采用 **[Apache-2.0 许可证](https://opensource.org/licenses/Apache-2.0)**，允许自由用于商业及非商业用途。

---

## 🚀 使用示例

```cpp
#include "dxfhelper.h"

int main()
{
    DxfHelper dxfHelper;

    if (dxfHelper.generateDxf("test.dxf")) {
        dxfHelper.getDxfPaths();         // 获取所有图形点集
        dxfHelper.generateDXFImage();    // 获取预览图像
    }

    return 0;
}
```

---

## 📁 项目依赖（Qt `.pro` 配置）

```qmake
QT += core
INCLUDEPATH += $$PWD/dxflib
DEPENDPATH += $$PWD/dxflib

SOURCES += \
    $$PWD/dxflib/dl_dxf.cpp \
    $$PWD/dxflib/dl_creationadapter.cpp \
    $$PWD/dxfreader.cpp

HEADERS += \
    $$PWD/dxflib/dl_dxf.h \
    $$PWD/dxflib/dl_creationadapter.h \
    $$PWD/dxfreader.h
```

---

## ⚙️ CMake 配置（适用于 C++ 项目）

```cmake
add_subdirectory(dxflib)
target_link_libraries(your_target PRIVATE dxflib)
```

---

# 📉 样条曲线解析库 - `spline_library`

用于将控制点转换为平滑的 `QPainterPath`，适用于样条曲线渲染。

---

## 🧱 示例代码

```cpp
#include "splinehelper.h"

int main()
{
    std::vector<QVector2D> pointList; // 输入控制点列表
    SplineHelper spline(pointList, TypeCubicBSpline); // 构造样条对象
    QPainterPath path = spline.getSplinePath(); // 获取绘制路径
    return 0;
}
```

---

## 📌 支持的样条类型

- `TypeLinearInterpolation`：线性插值
- `TypeCubicBSpline`：三次 B 样条
- `TypeCatmullRom`：Catmull-Rom 样条
- 更多样条类型持续更新中...

---

## 📎 GitHub 地址

- 📂 **DXF 解析库**: [dxf_reader](https://github.com/sorrowfeng/dxf_reader)
- 📂 **样条曲线库**: [spline_library](https://github.com/sorrowfeng/spline_library)
