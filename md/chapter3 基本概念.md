##基本概念
###以下针对ECMAscript3

###语法
`借鉴了c和其他类c的语言`
####区分大小写

####标识(shi)符
 *就是 变量，函数，属性的名字，参数。
- 要求第一个字符必须是字母，下划线或者一个美元符号
- 字母可以包括unicode中的字符
- 书写格式，按照惯例，第一个字母小写，剩下的每个单词字母大写 如 kingJames sortFuc
- 不能把关键字，保留字当做标识符

####注释
- 单行注释//
- 多行注释/**/

####严格模式
- 在所有代码前加入  `"use strict"`就是整个脚本都采用严格模式，在函数体的第一行加入就是函数采用严格模式。
- 这样可以使一些不确定的行为得到处理，不安全的操作会抛出错误

####语句
- 由分号结束，如果省略，则解析器确定语句的结尾，多数情况下也是有效的，但是不推荐
- 代码块以{}包括起来
-


###保留字和关键字

- 关键字，用于执行特定的操作
- 第五版的关键字：
`break do instanceof typeof case else new var catch
 finally return void cotinue for switch while default 
 if throw with this function debugger delete in try `

 -保留字，未来有可能被用作关键字（第三版）

 `abstract enum int short boolean export interface static 
 byte final native synchronized class float package throws 
 const goto private transient debugger implements protected 
 volatile double import public`
 - 非严格模式下运行的关键字有所缩减
 

###变量
- 变量是松散模式的，可以用来保存任何的数据类型，定义时使用 var `变量名`
-  var在函数体定义的变量在函数结束后悔被销毁，是局部变量
-  如果省略var定义变量就是一个全局变量 ，但不推荐，因为比较难维护，
 
###数据类型
- ECMAscript有五种基本类型，Undefined未定义 ,Null空(被认为是空object指针，也是object),Boolean布尔值,Number数值 和String字符串,
- 还有一种复杂数据类型 Object，本质是复杂的无需名值对组成的，ECMAScript不支持任何自定义类型，
####typeof 操作符
- 用来检测类型 返回值除了6种类型，还有function，
```javascript 
  <script> alert(typeof null);
  </script>

```

- Undefined :不管是未声明 如alert(name);还是未定义var name ;alert (name);都会产生undefined
- undefined == null,值相等，但用途不同，undefined派生自null,对象初始化前最好=null，
- boolean ,boolean 和0,1并不相等，但是，可以通过boolean(),把类型转成boolean如boolean(字符串)就变成了true
- Boolean只认小写

-Number类型 ：
1.十进制，八进制（前导0），16进制（前导0x），如果超过了8进制的范围就被认为是10进制，如果是严格模式下，八进制是无效的
2.浮点数：不要去测试特定的浮点数值，如（0.1+0.2)!=0.3
3.NaN：not a number 非数值，有两个特点，一是 涉及到任何NAN的运算都会返回NaN（NaN/10）,二是NaN与任何数都不等包括自己(NaN==NaN)//false,相应的判断函数 （isNaN()）只要能转换成数值就不是NaN如Boolean(true or false)
对象也可以被isNaN判断
4.数值转换 :Number(),parseInt( ),parseFloat()可以把非数值转换为数值，number可以将任何非数值转换成数值，后两个仅适用于字符串，
- number的作用规则：如果是字符串前导零会被省略，如果是对象就先调用valueOf()方法，然后依据值得规则进行转换，如果是NaN,则调用toString再进行判断，
- parseInt()对于空字符串返回NaN，Number()则返回1，parseInt对于空格会跳过，对`1234abcd`，就会忽略abcd，而Number()就NaN,070在ECMA3中是八进制，在5中是十进制，所以再加一个参数
parseInt("AF",16)//以16进制转换，此时可以不带AF前的0x
- parseFloat(),特点对于22.34.5只取第一个小数点，22.34（parseInt会22返回），16进制数会被解析成0，只解析10进制，忽略前导零

- string类型
1.字符串字面量： \n \t \r回车 \f换页符 \\斜杠 \unnnm用16进制数表示一个Unicode字符 \xnn表示16进制数表示一个ascii字符，
2.字符串是不可变的，要改，只是变量名字指向另一个，原来的被销毁了。
3.转换为字符串，toString(2)//表示转换成2进制字符串，null和undefined值没有这个方法，可以借助String方法实现，它会判断是不是能调用，不能调用就返回相应的Null和undefined。

- Object 类型
 ECMA的对象其实就是数据和功能的集合，创建对象`var 0 = new Object()`,在不构造函数传递参数的情况下，（）可以省略，但不建议。
```javascript
 var O = {
 valueOf:function(){
    return -1;//值就是-1
    }
 }
```
###操作符 
- 与c语言类似，不再赘述
- 加性操作符 会自动类型转换 如var message = "The sum of 5 and 10 is "+ (num1+num2)
- 全等`===`和不全等`==`，全等指的是在未转换时两操作数的值相等，除此之外再无差别，如null==undefined ,null!===undefined，因为类型不同
- 逗号操作符，可以表示多个操作，如果用于对同一个变量赋值，表示的是最后的赋值 如a = (1,2,3)，//a =3，

###语句 
- for in，是一种精准的迭代，
```javascript
    for(a in b){

    }
```
- label语句，如start:for{
                            ...
                            if()
                            break start;//这样break就会就会返回到 指定的label start那去了，一般用于多重嵌套的跳出           
                        }
- with语句，不建议使用

###函数
-理解参数： ECMAscript不在乎传过来的参数有多少，因为内部实现的时候就是一个参数数组，函数只用它用的参数就可以了，
- arguments   一个类似数组的对象，可以用[]去检索，相应的参数，.length可以获取长度
- 不能把函数命名为 eval和 arguments
- 函数参数的长度是由传入的参数数量决定的，所以传一个参数时，再函数内部arguments[1]= 10，并不会增加参数，
- 没有重载，，如果定义了两次只取后面的一次，

