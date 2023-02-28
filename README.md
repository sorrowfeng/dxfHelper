# dxfHelper
在qt中用于解析dxf文件

# SPline
解析样条曲线的库在 [spline_library](https://github.com/sorrowfeng/spline_library)

# 使用示例
``` cpp
#include "dxfhelper.h"
int main()
{
	DxfHelper dxfHelper;
	if(dxfHelper.generateDxf("test.dxf")) {
		dxfHelper.getDxfPaths(); // 获取转换出来的dxf所有类型图形的点集
		dxfHelper.generateDXFImage(); // 获取预览图像
		// 更多详见dxfHelper.h
	}
	return 0;
}
```
