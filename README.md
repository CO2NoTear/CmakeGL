# LearnGL Code Repository

notes are in my own repo: [Github:LearnGL](https://github.com/CO2NoTear/LearnOpenGL)

# 各实验分支说明：

你目前处于的分支是： **main**

该分支主要实现**实验1, 实验2, 实验3,**：


## 实验1和2

1. 渲染了三个立方体,一个巨大的人物模型
2. wasd, lshift, space移动相机，方向键上下左右、+、-对人物模型进行操纵，esc退出程序。
3. 天空盒
4. 立方体折射效果
5. 立方体自动旋转

请使用Cmake构建代码，并选择**Scene**目标进行bulid和运行。

## 实验3

1. 实现鼠标选点的贝塞尔曲线绘制
2. 控制点随机移动并实时绘制另一条贝塞尔曲线

请使用Cmake构建代码，并选择**Bezier**目标进行bulid和运行。

需要更改的环境集中在CMakeList.txt的11，13，16行，GLFW、GLAD、OpenGL路径设置，以及glad_dependency/CMakeList.txt的3行，GLFW路径。