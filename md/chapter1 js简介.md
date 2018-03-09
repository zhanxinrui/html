


##history:
*1995年诞生，主要是处理一些输入验证操作，它的出现主要是为了解决，用户填表单的时候是否有填错的，无效的值(在当年网速很慢的时代，提交表单的延时是无法估量的)，后来有了与浏览器窗口及其内容等方面交互的能力，现在甚至有了闭包，匿名（'lambda'）,甚至元编程等特性
*netscape的 Brend Eich布兰登艾奇，为了报java这个很热名词的大腿，于是把本来叫livescript改为javascript。

*javascript 1.0的成功导致了微软也加入了开发，于是，有了两个版本， 一个是Netscape navigator的JavaScript ,另一个是IE的Jscript，由于没有标准所以人们开始操心标准化，

*ECMA（European Computer  Manufaturers Association）,欧洲计算机制造协会，制定了39号技术委员会去标准化，TC39来自各个公司的程序员，他们最终定义了 ECMAScript 标准 ，第二年ISO/IEC(international organization for standardization and international Electrotechinical commission)国际标准化组织和国际电工委员会也采用了这个标准，浏览器也将此作为基础。
*浏览器只是ecmascript实现的宿主之一，还有Node和adobeFlash都可以，ecmascript主要规定了 js的语法，类型，语句。。。浏览器除了提供宿主，还提供了更多功能以实现针对环境的操作，如dom，

##DOM（DOCUMENT OBJECT MODEL）
*DOM是一个接口 ,能把网页结构映像成一个树的结构，结点就是网页中的元素，通过对这些结点对象进行操作来控制页面，也是由于jscript和JavaScript两极分化导致了代码无法同时兼容两个语言，所以就出现了dom这个接口，无需关心其中的不同，在更高的层次进行操作， 
*DOM的分类： 
'DOM1级' ：分为DOM Core 和DOM HTML ，dom core主要规定对XML文档结构的映射，DOMHTML则规定了对HTML的对象和方法。
'DOM2级'：扩充了鼠标和用户界面事件，范围，遍历的支持，
'DOM3级':引入了统一方式加载和保存文档的方法，，验证文档的方法，支持XML规范
'DOM0级'：是不存在的标准，指的是IE4和NN4最初支持的DHTML

##BOM(Browser Object Model)
*IE3和NN3就可以支持访问和操作浏览器的浏览器对象模型，根本上，是只处理浏览器窗口和框架的接口，一般不算js,但人们习惯上把所有针对浏览器的js扩展算作Js的一部分，如移动，缩放关闭浏览器窗口，cookies的支持，XMLHttpRequset等自定义对象，HTML致力于BOM的规范化