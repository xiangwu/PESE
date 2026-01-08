img = imread("C:\Users\16803\Desktop\quanjing\image\01.jpg");

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
