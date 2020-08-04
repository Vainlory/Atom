该文件记录我在学习、使用Qt中遇到的一些坑

---



```c++
this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
this->setAttribute(Qt::WA_TranslucentBackground,true);
```

对于设置了以上属性的widget，当在窗口中使用qtextbrowser时，鼠标左键消息会无法触发，无论使用` eventFilter(QObject*,QEvent*)` 还是重载` mousePressEvent(QEvent*)` 鼠标左键的消息都是无法触发的，鼠标右键正常，因此这里不可以使用qtextbrowser，我后来改成qlabel之后正常可以实现窗口拖动

后来将qtextbrower的setAttribute(Qt::WA_transparentformouseevent) 即可使得窗口捕获鼠标事件。

---

设置了以上属性的窗口是无法移动、放缩大小的，需要自定义 按钮来实现功能

---

对于单个函数内的标志作用的布尔变量，可以使用static声明一个局部静态变量来代替一个类的变量来来实现双态变化（三态、多态也可遵照此例）

