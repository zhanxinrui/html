##DOM拓展

DOM作为API已经非常完善了，但为了实现更多功能，主要两个拓展是selectors API 和HTML5

###选择符API 
selectorAPILevel 1的核心是两个方法：querySelector()和querySelectorAll()
- querySelector方法接受一个css选择符，返回的是与该模式匹配的第一个元素，如果没有找到匹配的元素，则返回null.

var body = document.querySelector("body");
var myDiv = document.querySelector("#myDiv");//取得ID为myDiv的元素
var img =  document.body.querySelector("img.button");

- querySelectorAll()方法接收的参数与querySelector()方法一样，都是一个css选择符。但返回的是一个NodeList的实例。


- matchesSelector()方法 接收一个参数，css选择符，如果调用元素和该选择符匹配，返回true，否则false。
如： if (document.body.matchesSelector("body.page1")){//true}
//截止2011年，还没有支持的浏览器，但是可以通过mozMatchesSelector()支持该方法。
###元素遍历
- 对于元素的空格，ie9之前的版本不会返回文本结点，而其他会，这样就导致了再使用childNod 
es和firstChild等属性时的行为不一致。为此新定义了一组属性： 
childElementCount:返回子元素的个数
firstElementChild:指向第一个子元素
lastElementChild:指向最后一个元素
previousELementSibling:指向前一个同辈元素
nextElementSibiling:指向后一个同辈元素

过去需要检验child.nodeType == 1，现在只用nextElementSibiling就可以了，不包括空白文本结点

###HTML5
- 对于传统HMTL，H5是一个叛逆，所有之前的版本对JS接口的描述主要在定义标记，而H5  
则定义了大量的js api，其中以写和DOM重合，定义了浏览器应该支持的DOM拓展
####与类想过的扩充
增加了getElementsByClassName(),还有classList属性，className属性是一个字符串，需要切割，而classList是一个数组，可以使用item()方法也可以中括号，还可以add() contains() remove() toggle()  ：如果列表中已经存在给定的值，删除它，如果列表中没有给定的值，添加它

####焦点管理，
- 元素获得焦点的方式有页面加载，用户输入(通常是Tab键)和代码中使用focus方法
var button = document.getElementById("myButton");
button.focus();
alert(document.activeElement === button);// true 使用activeElement可以获取焦点所 
在，也可以通过hasFocus()来判断是否具有。

####HTMLDocument的变化
- HTMLDocument是继承自Document类型，
1.readyState属性，分为loading，正在加载文档，complete已经加载完文档。
2.兼容模式： 标准模式下，document.compatMode的值是CSS1Compat在混杂模式下document.  
compatMode的值等于BackCompat
3.head属性： 可以引用head元素，可以作为一种后备方法。
####字符集属性
就是charset属性表示文档中实际使用的字符集

####自定义数据属性
可以在标签内加入 data-somename(自定义的) 来添加属性。然后 可以通过 元素.dataset.s  
omename来表示。
####插入标记
1.innerHTML
在读模式下，返回的是所有子节点的HTML标记，写模式则会创建新的DOM树 ，但是添加的字符串 
如标签名解析后，与innerHTML设置的值大不相同。而且<script>并不会执行。因为script元素是 
无作用域的元素。可以在前面加入一个文本节点，或者一个有作用域的元素，或者空白的input， 
```<input type=\"hidden\" >,除了input其他的都要删除，```
大数浏览器都支持直观的方式插入<style>元素，但在ie8及更早版本也需要前置有作用域的元素
- 只要使用innerHTML从外部插入HTML，都应该首先以可靠的方式处理，window.toStaticHTML()
可以返回一个无害处理后的版本--删除所有多脚本节点和事件处理程序属性
2.outerHTML属性
读模式下返回它和所有的子，写模式下回创建新的DOM树，然后完全替换调用它的元素。
div.outerHTML = "<p>This is a paragraph</p>";
相当于
var p = document.createElement("p");
p.appendChild(document.createTextNode("This is a paragraph"));
div.parentNode.replaceChild(p,div);

3.insertAdjacentHTML方法
接受两个参数，插入位置和插入文本或标签。 插入位置有beforebegin开始标签之前,afterbegin,beforeend结束标签之前 afterend，对于文本也是一样，相对于文本的标签
4.性能问题
因为innerHTML创建会创建HMTL解析器，所以不应该多次创建。

####scrollIntoView方法
可以在所有HTML元素上调用，通过滚动浏览器窗口或某个容器元素，调用元素可以出现在视口  
之中，如果给这个方法传入true或者不穿就会让调用元素的顶部和视口的顶部尽可能平齐，如果传入false调用元素底部会和视口顶部平齐
document.forms[0].scrollIntoView()
###专有拓展
####文档模式
决定了可以使用什么功能，通过<meta http-equiv = "x-ua-Compatible" content = "IE= IEVersion>判断
####children属性
children属性和childNodes基本没有什么区别。 
####contains()方法
compareDocumentPosition()可以确定结点间的关系，documentElement指向html元素
var result = document.documentElement.compareDocumentPosition(document.body)可以得到html和body的关系的掩码值，1是无关，2是body居前，4是居后，8是包含，16是被包含
####插入位置和插入文本或标签
- innerText属性：并没有被H5纳入规范。读时它可以获得元素中包含的所有'文本'内容，并凭借，写时则会删除元素的所有子节点，插入包含相应文本值的文本节点，同样也会解析后不一致，可以通过div.innerText = div.innerText来去掉标签。，有些浏览器支持textContent属性。
- outerText在读模式时返回的和inner相同，写模式则设置的是替换该节点和其下的所有元素
 var text = document.createTextNode("Hello World");
 div.parentNode.replaceChild(text,div);

####滚动
- 除了 纳入规范的scrollIntoView()还有几个专用方法
- 1.scrollIntoViewIfNeeded(alignCenter):只有在当前元素在视口中不可见的情况下，才课件，
2.scrollByLines(lineCount):将元素的内容滚动指定的行高
3.scrollByPages(pageCount):将元素的内容滚动指定的页面高度