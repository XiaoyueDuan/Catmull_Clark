# Catmull-Clark细分曲面C++实现
---------------------------------------
### 实现功能
该程序实现了Catmull-Clark算法细分正方体。其中Catmull-Clark算法是一种通过表面细分得到光滑曲面的方法，在计算机图形学领域有着广泛应用。从下图就可以大致理解算法背后的philosophy（图片来自[wiki](https://en.wikipedia.org/wiki/Catmull%E2%80%93Clark_subdivision_surface)）。

![wiki_illustration](/readme_images/wiki_illustration.png)

通过给定的网格的控制顶点，Catmull-Clark算法可以通过计算面点（face point），边点（edge point），角点（vertex point）进行均匀B样条曲面计算，求出光滑表面。

### 算法
Catmull-Clark算法计算方法如下：
输入①要细分的深度和②一个任意多面体的网格，该网格中所有的点作为**原始点（original points）**。
* 对于网格中的每个面，计算该面**新面点（face point）**
	- 新面点是该面所有原始点的平均值
* 对于网格中的每条边，计算该边的**新边点（edge point）**
	- 新边点是该边两个顶点的中点，和该边邻接的两个面新面点的平均值
* 对网格中的每个原始点，计算**新角点（vertex point）**。新角点的计算方法：![formula](/readme_images/formula.png)

其中，
<ul>
<ul>
<li>F是该点所属的所有面的新面点的平均值</li>
<li>R是该点所属的所有边的中点的平均值</li>
<li>P是该原始点</li>
</ul>

<li>
连接新面点和该面上计算的新边点，同时连接新角点和该点所属的边的新边点。根据这些新生成的边，得到的封闭区域就是新的面。反复上述过程知道达到输入的细分的深度。
</li>
</ul>
下图就是Catmull-Clark算法的一个例子。

![algorithm_pipeline](/readme_images/algorithm_pipeline.png)

### 实验环境
win7，64bit

C++， Visual Studio 2015

想要下载我代码的小伙伴不用担心，只要是使用VS2015+且为64位系统，就可以直接在VS中选择x64编译生成可执行文件，我已将OpenGL的header，lib和dll库都配好。不过强烈安利使用[该方法（戳这里）](http://www.cs.uregina.ca/Links/class-info/315/WWW/Lab1/GLUT/windows.html)给自己的电脑配环境，这样就不用以后每写一个程序就配一次环境了~
### 使用方法
键盘控制方法：
* 按“f”物体以y轴正方向右手坐标系中逆时针旋转；
* 按“s”物体以y轴正方向右手坐标系中顺时针旋转；
* 按“e”物体以x轴正方向右手坐标系中逆时针旋转；
* 按“d”物体以x轴正方向右手坐标系中顺时针旋转。

### 实验结果
线框表示：

![result_grid](/readme_images/result_grid.png)

面片表示：

![result_face](/readme_images/result_face.png)