## 项目背景

某日脑子一抽，于是开始学习 qt 并着手写这个项目，没啥深层次原因 

## 安装

目前仅有Qt得源代码及工程还有项目所配套得图形库,如需查看效果请自行编译 

*有尝试过编译成release版，但是对于QT的文件的层次关系目前还不熟练，后续的release版会之后上传*

Qt环境是 Desktop Qt 5.12.9  Windows

## 使用

请根据日常生活中使用各类文本编辑器*(eg.  evernote , notepad )*得经验来使用他。

## 作者



## 联系方式

**邮箱**: 765228482@qq.com 

**QQ**:  *765228482*

或者可以通过github在该项目下留言 

## 更新日志

**2020/7/12**  *23: 21*

  创建仓库，上传了总体得框架，共计完成了一个编辑界面得主窗口，文件过滤器的系统托盘等功能

**2020/7/21**  *22: 26*  

以印象笔记为模板继续添加、完善notepad部分的功能，开始编写字体工具栏，尽量使得使用贴近日常正在使用的编辑器。目前尚且存在的bug， 当cursor从后向前选取文本时，cursor默认时读取前方字体的charfomat 导致此时点击加粗或者倾斜按钮时是在前方文本的基础上进行加粗或者倾斜操作。

**2020/7/28**  *22: 45*

基本完工文本编辑器方面的编写，对于文件路径就下一步的编写进行了微调，引入了locals文件夹用于存放用户所写的文本，当用户使用编辑器完成后，点击保存，文件将以标题栏中的字符串为文件名 .xml为后缀直接放入对应的文件夹中*如果标题栏为空，默认命名为uname.xml并且保存机制会检测是否有同名文件存在，若有则会添加(1) (2)这样类似的后缀，相关的内容完善需等到 filter 部分大体思路确定、框架形成后再行完善*   

**2020/7/29**  *23: 00*

添加了主窗口中的filter QTreeWidget 实例, 隐藏表头，添加了leaves 右键呼出菜单, override openFile函数，使得可以通过右键呼出菜单打开对应的文件夹下的文件。 重构了saveFile 函数，将title，最后修改时间等信息以"@#4."为分隔写入文件。 