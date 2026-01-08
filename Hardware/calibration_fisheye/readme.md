# MATLAB矫正鱼眼镜头
2025/10/29 submit by 郑高星

#### 鱼眼镜头

鱼眼镜头的焦距极短，视角可达到180度甚至更大。鱼眼镜头的设计灵感来源于鱼类的视野，能够捕捉到广阔的场景。其成像原理与普通相机不同，鱼眼相机通常采用等距投影或正距投影，这种投影方式可以将更大的视场压缩到二维图像上，避免传统透视投影的失真。

![image](quote/01.jpg)

#### 准备相机图片数据

![image](quote/02.png)

注意事项：

1.要清晰的拍摄棋盘，注意光照

2.不要只在标定板平行面拍摄，最好多个角度

3.可以多拍摄一些，然后效果不太好的可以根据误差剔除

#### MATLAB矫正

打开MATLAB中APP一栏点击下拉框

![image](quote/03.png)

下滑找到图像处理和计算机视觉一栏，点击Camera Calibrator

![image](quote/04.png)

从文件中导入，可以选择images文件夹，或是自己拍摄

![image](quote/05.png)

全选导入即可

<img src="quote/06.png" alt="06" style="zoom:50%;" />

图案选择棋盘格，棋盘格大小根据实际填写，images文件中的棋盘格大小为20毫米

<img src="quote/07.png" alt="07" style="zoom:50%;" />

等待导入完成

<img src="quote/08.png" alt="08" style="zoom:75%;" />

直接点击确定

<img src="quote/09.png" alt="09" style="zoom:75%;" />

选择Fisheye，勾选Options，点击Calibrate

![image](quote/10.png)

删除一些误差较大的

![image](quote/10.png)

![image](quote/11.png)

导出参数

![image](quote/12.png)

返回MATLAB主界面，发现工作区已经获得了参数

![image](quote/13.png)

运行下列代码，即可矫正图像

```
img = imread("images\01.jpg");

% 使用获得参数进行矫正
intrinsics =cameraParams.Intrinsics;
% intrinsics = cameraIntrinsics(cameraParams.Intrinsics);
%intrinsics = calibrationSession.CameraParameters.Intrinsics;
%result = undistortFisheyeImage(img, intrinsics);
result = undistortFisheyeImage(img, intrinsics, 'OutputView', 'same');

% 显示结果
subplot(1,2,1); imshow(img); title('鱼眼图像')
subplot(1,2,2); imshow(result); title('校正图像') 

% 更改显示比例
set(gcf,'Visible','off')
set(gcf,'units','normalized','outerposition',[0 0 1 1]);
set(gcf,'Visible','on')
```

<img src="quote\14.png" alt="14" style="zoom:200%;" />

可以右键保存参数

![image](quote/15.png)

在下一次想要矫正时不用重新导入图片，直接双击即可导入这些参数

![image](quote/16.png)