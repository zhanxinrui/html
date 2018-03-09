
##CHAPTER 4 变量，作用域，内存问题
### 4.1 基本类型和引用类型
基本类型是简单的数据段，引用类型指的是那些可能由多个值构成的对象
string在ecmascript中是基本类型，不是对象。

####4.1.1 动态的属性
- 对象的属性可以添加eg:
```javascript
    var person = new Object();
    person.name = "Captain";
    alert(person.name);
```
- 对象的引用的修改属性会改变原先的对象的属性，基本类型的则是分离的（这里说的引用并不是c++中的引用（别名），而是相当于指针，）
####4.1.3-传递参数
在传参过程中，如果参数是一个对象，那么obj就访问的是对应的person，而当new一个Object用obj指向时，修改的内容便是new出来的地址的，其实obj是指向person的一个指针，就是说obj内容是person的地址，现在指向另一个地址，自然也修改不了Obj了。  （c++中的引用是把一个指针的值放成变量的地址，对于这个指针的值的操作就是对变量本身的修改，这和一般的指针没什么区别，只不过写成&a =b，而对于指针的引用，则是把指针的地址填成所引用的指针的地址，相当于二维指针，但是不用加那么多&，因为要实现对指针的值修改必须拥有指针的地址，所以多出来一个指针，而在下面代码中，obj仅是一个一维指针，它的地址仅是对象boject内容的地址，而不是person的地址，自然无法修改person了）  
```javascript
    <script> 
    function setName(obj){
        obj.name =' Nicholas' ;
        obj = new Object();
        obj.name = "Greg";

    }
    var person  = new Object();
    setName(person);
    alert(person.name);
    </script>  

```  

####4.1.4 检测类型
-  typeof
-  a instanceof b //检测a是不是b类型的*对象*，主要是为了对于对象的属性的类型的检测，b.name是什么
eg: alert(person instanceof Object);//变量person是Object吗，
```javascript
<script> 
    function setName(obj){
        obj.name =' Nicholas' ;

    }
        var person  = new Object();
    name = 'asdf';
    var name1 = new String("sdfsaf");
    setName(person);
    alert(typeof person.name);//string
    alert(person.name instanceof String);//false
    alert(name instanceof String);//false
    alert(name1 instanceof String);//true
</script>
```
-正则表达式的 typeof 结果是object

####作用域：
- 无块级作用域，最小的就是函数作用域也叫局部作用域，所以with语句内的变量很轻易被函数内  访问  
- 作用域链：执行环境产生的变量对象构成。   
-  作用域链是保证函数在执行时能够正确有序访问需要变量和函数;   

- 延长作用域链（作用对象变多）
    1.try-catch语句中的catch块
    2.with语句
    如：
   （1） 
``` javascript
<script> 
    var o={href:"sssss"};  
    var href="1111";  
    function buildUrl(){
    href="1234";  
    var qs="?debug=true";       
     with(o){  
          href="2222";  
          var url=href+qs;  
     }      
     return url;  
}  
    var result=buildUrl();  
    alert(result);  //2222?debug=true
    alert(href);   //1111
  <
```  

- 第二个alert返回1111说明with语句里面没有修改全局变量href只是修改了o对象的href属性，  说明了 
- 执行with语句时将创建buildUrl的执行环境，将buildUrl放到作用域链表的开头，但是由于在with中操作href变量时先访问的是o对象的href属性，因为with的特性使得href单独成一个变量了，但实际属于o，所以把o对象放到buildUrl对象之前，否则，buildUrl的href将和with中的href冲突。  
- with整个作用域链就是o->buildUrl->window
- 像if else这样的带{}的块却只能把对象函数域中。
（2）try-catch  
try{
    有可能出现错误的代码
}
catch(error){//error自己命名的错误对象
    
 alert(error.message);出现错误后去执行的代码
    
}
- 在catch中能获取到try的变量，和with语句类似，catch到一个对象，但这个对象并不是在这个try语句中产生的，只是捕获了，不属于这个函数，所以在执行try和catch语句的时候，作用域链的表头是这个error对象,然后才是函数对象，接着是全局window。相当于延长了作用域链


- 查询标识符：
- 某个环境中为了读取或写入而引用一个标识符时，先通过搜索确定该标识符到底代表了什么，搜索就是通过该作用域链，这也解释了上面相应的o对象和error对象为什么要是函数外的作用域且在前端，不然就会出现错误的引用，

- 作用域链的构建在没执行读取和写入操作时，就已经进行了，执行的时候会再次确认。
   作用域链分两种：①词法作用域链（静态的），就是由定义函数的位置和其他函数括号关系（包含）决定的，它是静态的，未执行就构建，
   ②动态作用域链：由栈的调用决定的，出现在函数嵌套函数时，找到不变量就到调用它的函数中去找，这是执行时才能明白谁调用了它，所以说，动态作用域链是执行时构建的
   作用域链常常是两种的结合，即前面的是静态的，提前加载好的
- 作用域 在js中只有静态的，并且在函数声明时就已经全部决定了，作用域链之所以是结合的是因为调用的时候决定了作用域之间的连接，这些作用域本来都有了，只是连接没建立
###垃圾收集
- 对于没有用的局部变量经判断后自动回收内存
- 标记清除，对于声明变量时就给个`进入环境`的标记，当离开环境时就给`离开环境`标记，经过判断后将离开环境的变量和它引用的变量都标记为准备删除

-引用计数 不太常见的一种垃圾收集策略 ，，含义是跟踪变量被引用的次数，如果引用它的变量指向了另一个变量则减一相反加一，但是有个bug就是，两个对象相互引用时，就永远不会被清除 
####性能问题
- ie给的标准太小，容易使得垃圾收集器频繁运行 ，随后ie7中采用了动态修正临界值得方法，低于15%临界值翻倍，高于85%,则回归默认值
####内存管理
- 由于给系统害怕崩溃，所以给浏览器留的内存相对少， 所以对于变量我们要人工的解除引用 object a=null,对于函数中的并不需要，因为执行完会自动脱离环境，而对于全局变量则需要， 解除引用的目的在于，告诉垃圾收集器该变量脱离环境，下一次运行时就可以清除了。