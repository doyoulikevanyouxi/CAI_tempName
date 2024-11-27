# CAI_tempName
    从0开始的图形渲染框架搭建。
    CAI(Cpp Auto Interface Constructor)即c++ 界面自动构建工具。
    这是一款从0开始的项目，因此项目周期会比较长。
# Usage
   程序的调用如下：
   在MainWindow.hpp文件中，MainWindow的构造函数里，你需要为Winodw指定一个Content内容，在以下示例的最后一行操作。如果没有指定那么不会显示任何内容。
   不必按照该实例给出的操作，早期实例化每一个所需控件，你可以在任何主线程位置添加新的控件，在目前的渲染中使用的基于范围的for循环递归，如果多线程增加
   /删除，会导致迭代器失效，导致错误。当然你也可以实现多线程安全的操作，不采用迭代器，或者另外实现容器。但如果要实现多线程安全，请确保其迭代器不会失效。
   如果要实现自己的容器，请修改Datas/VisualCollection类，如果你的容器不支持基于范围的for，那么你需要修改所有使用了范围for的位置。

    MainWindow(int width = 800, int height = 600) noexcept :Window(width, height) {
        //初始化渲染组件，获取窗口
		InitializeComponent();
        //实例化一个Grid控件
		Grid* grid = new Grid();
        //设置Grid控件背景色
		grid->SetBackground(0xffffffff);
        //设置Grid控件网格数据，即每行每列的数据
        //添加了一列
		grid->addColumDefinition(ColumDefinition());
        //添加了一列，并且该列有固定宽度400px
		grid->addColumDefinition(ColumDefinition(400,true));
        //添加了一行
		grid->addRowDefinition(RowDefinition());
        //添加了一行，并且该行有固定高度300px
		grid->addRowDefinition(RowDefinition(300,true));
        //实例化一个TextBox控件
		TextBox* txtbox = new TextBox();
        //实例化了一个Bool动画
		BoolAnimation* animate = new BoolAnimation();
        //设置boo动画起始值为true
		animate->From = true;
        //设置boo动画终结值为false
		animate->To = false;
        //设置动画的目标属性为TextBox的Visible属性
		animate->Target = txtbox->GetVisible();
        //设置动画重复运行
		animate->Repeat = true;
        //设置动画执行时间为1s
		animate->duration.timeSpan = 1.0;
        //设置动画延迟执行时间为1s
		animate->delayDuration.timeSpan = 1.0;
        //将动画添加至TextBox的画板里
		txtbox->storybord.AddAnimation(animate);
        //开始动画，动画不一定在此处就开始，这只是一个演示
		txtbox->BeginAnimation();
        //设置TextBox的边框大小为10px
		txtbox->SetBorderSize(10);
        //设置TextBox的边框颜色为黄色
		txtbox->SetBorderBrush(0xffffff00);
        //设置TextBox的字体大小为20px
		txtbox->fontSize.set(20);
        //设置TextBox的背景色为蓝色
		txtbox->SetBackground(0xff0000ff);
        //设置TextBox的行列值，第0行第0列
		grid->setRC(txtbox, 0, 0);
        //设置TextBox的所占行数，TextBox会占据从其指定行算起，总计纵跨两行
		grid->setRowSpan(txtbox, 2);
        //实例化一个新的Grid布局容器
		Grid* gChild = new Grid();
        //设置该容器背景色为红色
		gChild->SetBackground(0xffff0000);
		grid->setRC(gChild, 0, 1);
        //实例化一个TextBlock控件
		TextBlock* tb = new TextBlock();
        //设置控件字体大小为20px
		tb->fontSize.set(20);
        //设置控件背景色为绿色
		tb->SetBackground(0xff00ff00);
		grid->setRC(tb, 1, 1);
        //添加实例化的TextBox控件至Grid控件
		grid->AddChild(txtbox);
        //添加实例化的Grid控件至Grid控件
		grid->AddChild(gChild);
        //添加实例化的TextBlock控件至Grid控件
		grid->AddChild(tb);
        //设置TextBlock的文字
		tb->text.set(L"你好啊,\r\n再见");
        //设置窗口的Content为Grid控件
		setContent(grid);
	}
# 结构以及类说明
    ·没有找到合适的UML图工具，目前只能文字描述了。
        CAI目前的主体架构为：环境初始化---控件，架构非常的简单。对于环境初始化 Application类作为程序运行的一个全局监管，其主要用于初始化环境，监控特殊事件（特殊事件是指，事件需要进行二次处理后才能放入控件的事件流程中，或者直接指定事件的分发）。
    Application类目前只有RenderEngine类组合而成，RenderEngine类是图形渲染的基本，其负责渲染环境的初始化，包括Opengl上下文获取，窗口的创建，着色器程序的编译，渲染循环，控件所用到的渲染设备类的
    创建以及字体库加载。Application类的初始化环境中包括了调用RenderEngine的渲染环境的初始化。其他框架构成则是控件部分。
        PaintDevice：渲染设备句柄，该类由RenderEngine实例化，也由其删除。负责对顶点数据进行渲染
        一般控件的继承结构如下：Visual->UIElement->Control/Panel/ContetnControl->Button/Textbox/grid...Window。
        Visual：可视化控件的渲染部分，该类负责控件渲染数据的初步解析，并负责调用从RenderEngine获取的渲染设备类PaintDevice来渲染控件。Visual类具有控件渲染的基本属性：Width(控件宽度)，Height
    (控件高度)，Background(控件背景)，BoderSize(边框大小)，Corner(控件角，还未实装)，Visual类还实现了鼠标的点击测试和焦点属性。
        UIElement：继承至Visual，在其之上，增加了各个事件的处理，暂时预留了一个特殊的接口，在以往的版本中你可能会发现，UIElement类包含了一个ControlTemplate类型的数据，该类型的数据适用于覆写
    控件原有显示样式的数据。也就是说该接口运行你为其指定不一样的外观形式。
        Control：继承至UIElment，该类型进一步明确了控件的特性，Control类型增加了外边距，可以动态的调整控件位置。
        ContetnControl ：继承至Control，该类型明确表示其只能拥有一个子控件，也是每个独立控件的基类，button，Textbox等都继承此控件。
        Panel ：继承至Control，该类型可以包括多个子控件，其主要功能是对子控件进行布局。
        Grid ：继承至Panel，Grid类型为网格布局，所谓网格布局就是Grid控件会按照网格的形式，将其子控件根据设定的不同网格行列放置在不同的位置，如果可见网格，那么你会发现其子控件的位置在网格对应的
    格子内部。
        Window：继承至ContentControl，属于内容控件之一，但具有环境初始化的能力。完全的环境初始化需要获取一个窗体后，生成Opengl上下文在加载其他资源，但是窗体的创建和Window类又是两种完全不同的类型
    因此，将RenderEngine的初始化，延迟到第一个窗口创建是进行。第一个Window实例对象的会调用RenderEngine的环境初始化，并从中获取RenderEngine创建的抽口句柄，并将该类对象绑定到窗口部分事件回调上，主要
    事件为，鼠标移动事件和键盘事件，至于窗口大小调整由于进度问题需要后期制作。
# Notice
    ·程序开发IDE使用的是vs2022，字符编码为unicode。
    ·程序运行的所有依赖库已打包到仓库中，需要注意的是，请不要将resources/fonts/Windows里面的字体库用于商业开发，自己用来调试即可，fonts目录下的另一个Source_Han_Serif_SC_Light_Light.otf字体库可用于商业
    ·程序使用Opengl作为图形渲染基础。
# 开发日志图形渲染
[2024.10.9]

    ·搭建了基本的控件架构，还没有深入的实现，暂时没有对事件系统进行动工。
    ·先已经可以渲染图形了。
    
[2024.10.10]

    ·对控件的渲染进行了细致的开发，不过目前来所控件的渲染效率无法得到保障，所有的控件拥有独立的Opengl数据对象，当对象过多时可能会挤占渲染资源。鉴于大部分控件隶属于矩形渲染，会考虑将相识图形实例化。
    ·一般控件现可以直接简单继承并添加属性和重载部分功能即可。
    
[2024.10.11]

    ·优化了渲染部分的结构，现在控件的实例化更加的便捷明了了。
    ·将原有的控件移动公式由普通数学计算变更为矩阵运算了，添加了矩阵类，该类未对运算做优化，因此暂时不要使用大维度的矩阵。
    
[2024.10.12]

    ·开发了布局控件的基础，现在对于最重要的布局控件-网格布局已经开发的差不多了，该布局下的子控件可以正常的定位在相应位置。
    ·控件的裁剪问题一直没有得到良好的解决，主要是对裁剪矩阵没有直接感觉，暂时没有推理出裁减矩阵，资料很多把映射和裁剪搞一块，有点乱。
    
[2024.10.13]

    ·添加了文字渲染功能，使用的是FreeType库，上传文件里面包含了windows系统的字体库以及阿里的一个字体文件，你可以觉得那个好看用哪个。

[2024.10.16]

    ·重构了控件渲染逻辑，将矩阵运算移至GPU。
    ·新增控件textblock，该控件用来容纳文字。
    ·重构了grid布局控件，grid控件已经可以正常使用，设定值即使超出范围也会将其固定在1行1列中，同时如果不存在行列设置，那么加入的子控件会继承该grid的大小。
    ·新增z缓冲测试，现在可以对控件进行z值设定了，该设定决定控件的展示是否被掩盖或掩盖其他控件。设置的值越大，越在前面。实际z值和设置z值大小相反。
    ·需要注意的是裁剪算法仍未开发，所以出现内容超出部分可以先在片段或几何着色器中丢弃。

[2024.10.18]

    ·为所有继承至UIElement的控件添加了边框，边框原理是利用模板测试丢弃掉实际绘制区域。阴影效果同理（已测试可行），不过并没加上去。
    ·优化了顶点的数据结构，不同类型的数据现在是分开存储的：顶点坐标是一组，顶点颜色又是另外一组...。
    ·为Control控件添加了外边距Margin，现在控件可以相对的调整位置了。
    ·为Control控件添加了相对位置属性HorizontalAlignment和VerticalAlignment，能够将控件相对于父控件定位到Center，Left，Top，Right和Bottom上，且与Margin外边距有叠加计算。
    ·边框使用的作色器与其修饰的控件是同一个，因为边框与其修饰的控件具有相同类型的数据，只是数据不同。
    ·关于圆角，目前并没有开发，计算原理已有，同样利用模板测试，只是到底应该采用哪种数学计算还没有确定：是将圆角数据写入模板还是判定到中心点距离。
到此有关渲染控件的渲染整体结构已经完成，那么渲染将告一段落，近期都不在进行重构和优化。剩下的优化以及控件的添加将在xml文本解析后进行。
# 开发日志MVVM和文本解析

[2024.10.26]

    ·添加了事件系统，目前事件是由上往下的，没有分发。
    ·添加了日志系统，日志系统只是用来检测开发过程中的问题。
    ·为啥会先开发事件：MVVM模式其实除了采用观察者模式外也是可以使用事件系统来进行的，将数据的变化放入事件队列中，由对应的控件自行处理数据

[2024.11.8]

    ·由于近期有事，更新进度比较慢
    ·首先MVVM的开发需要往后延迟，主要涉及到泛型问题，考虑模板的缺点，暂时无法找出比较好的方法，由于c++目前只能开发简单的静态反射，这一块需要到后面再完成
    ·增加了一个新的控件TextBox,用来显示用户的文本输入。
    ·增加了一个新的事件大类，InputEvent来表示所有的用户输入事件---鼠标输入事件暂时除外
    ·需要重写文本渲染的着色器代码，加入深度测试后，原本的代码数据无法满足要求

[2024.11.16]

    ·完成了XML文本的解析工作，不过该工作再另一个项目中完成XMLInterpreter中。
    ·xml文本解析有两种架构，一种为预期值，这个只用一个类一个操作就可以完成，即限定输入字符的期望，并根据输入值决定接下来字符的期望，该架构对于字符的扩展支持性高，但不利于阶段控制。另一种是根据操作阶段的不同，对字符进行合法性验证，对特殊字符进行操作，该架构需要构建
    多个不同的阶段处理函数或类，对于阶段拓展性高，但是对于字符验证拓展性低。本项目采用了第二种操作，后期优化可能会将两种架构融合在一起。

[2024.11.23]

    ·调整了事件的文本结构，将不同类型的事件分开了
    ·调整了事件的发出方式，现统一由Apllication类管理
    ·修复了模板测试无效的bug
    ·修复了裁剪测试对于深度测试产生非良性影响的bug
    ·重写了裁剪测试的调用方式，现每个控件的渲染都有个Size clipSize 数据，用于限制控件的渲染范围
    ·增加了鼠标移动事件，现可以对控件使用mouseover，mouseenter，mouseleave以及mousePreOver等事件，该类事件建立在渲染树形结构下，并以z值辅助。没有z值会导致事件不准确。如果需要去掉z值，需要修改visual tree的子控件存储方式，将后加的控件放在前面
    ·增加了焦点，部分事件只对焦点目标起效，例如文本输入事件，只有焦点目标会收到该事件，其他控件不会收到
    ·新增文件夹Animation

接下来的工作是动画效果的开发，文本解析的深入开发以及，并入编译器的功能

[2024.11.26]

    ·优化了项目结构，将UIElement类由原先的即负责渲染又负责事件中分离了渲染，渲染被移至其父类Visual上了，奇特的是，原本启动需要的80M内存空间，同时被优化到只需要50M.可能在调整结构时优化了什么东西吧
    ·调整了窗口的获取时机，现窗口获取完全由window类管理，创建一个窗口后需要调用其Init函数，初始化渲染所需要的组件。
    ·修复了一个鼠标事件的bug，该bug在不知情下将范围index变成复数后，意外的通过了While循环的检查。
    ·将混合测试从文字渲染移动至全局了（平滑过度，消除抗锯齿除了多重采样外，在需要手动丢弃片段下，多重采样抗锯齿效果不能适用于此，需要利用透明度混合利用smoothstep获取平滑透明度）
    ·发现了新bug，字体渲染的高度似乎有问题，导致部分字体的图形高度不完整。
    ·增加了新的属性Visible，bool类型，控制控件的显示与消失。
    ·实装了一个动画：BoolAnimation,布尔值动画，该动画针对数据是bool的情况，在现有的代码中，如果拉取编译后，你会发现一个一段时间内闪烁的区域。
    ·在使用动画时，请注意，动画绑定的值需要被被渲染所利用，即值需要更新到渲染上。
    ·对于特殊形状的动画，需要开发glsl，目前对于矩形的圆角，圆已经完成。而曲线，需要研究一下贝塞尔曲线。