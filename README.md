# DesignPatternInC
C语言实现设计模式

```
1.C语言实现的设计模式，但有不足之处，请各位读者一定指正，我的邮箱taoxing2113@foxmail.com，期待您的来信。
2.实现时，使用了类库Apache Portable Runtime，版本为1.6.5，不过不使用这一类库也可以实现，思路是一致的。
3._INCLUDE文件夹中，apr_ext是我自己写的一个实用宏，方便实现环（环形双向链表）。
4.使用的Apache Portable Runtime是我自己编译得到的，读者可以直接使用，当然也可以自己下载源码，然后编译使用。
5.项目中代码，申请内存没有作判断，读者请注意！
6.代码编译环境，win10 Visual Studio 2017。
7.初步写成这样，后面将在优化。
8.其中一些设计模式没有实现，后面将添加。
9.设计模式的C实现代码参考了 刘伟 老师的C#设计模式的代码。在此表示感谢！

10.visual studio 2017 项目配置
	注意项目和解决方案的区别，解决方案下面有多个项目。
	& 右键项目--> C/C++ --> 常规 --> 附加包含目录 --> 输入框右边 下 箭头 --> 编辑 --> $(SolutionDir)_INCLUDE\apr_ext  和  $(SolutionDir)_INCLUDE\x86
	& 右键项目--> 链接器 --> 常规 --> 附加库目录 --> $(SolutionDir)_LIB\x86
	& 右键项目--> 链接器 --> 输入 --> libapr-1.lib
	& 右键项目--> 生成事件 -->生成后事件 --> 命令行 --> xcopy $(SolutionDir)_DLL\x86 /V /E /Y $(TargetDir)


```
