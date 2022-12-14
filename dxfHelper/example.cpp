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