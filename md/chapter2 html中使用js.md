## script标签 元素属性
- type (可选，可以不填，默认就是text/javascript):脚本语言的内容类型，
    或称为MINE类型，可以使用text/javascript 和application/javascript（非IE）application/ecmascript （非IE）
- src:外部文件地址
- 延迟脚本：defer  html5规定了只能对外部脚本进行延时 ，同时下载js和文档， 是在文档解析完成后再执行脚本使用方法:**
 ```javascript
    <script defer="defer"></script>
 ```
- 异步脚本 ：async 使浏览器不等待脚本的下载和执行 ，先让浏览器下载文件，但一定会在页面的load事件前执行使用 ，也就是说异步的执行脚本的下载和文档的解析，脚本下载完了之后理解就就执行脚本：(但都用了async的script加载顺序却不定，也只能适用于外部脚本)
```javascript
    <script async src="script.js"></script>
    <script async="async" src = "script.js"></script> //xhtml文档中
```
- 任何地方使用</script>都会被影响除非加转义字符'\'
        如：
        ```javascript
            <script>
            alert('</script>');//应该修改为<\/script>
            </script>
        ```
##解析顺序
*所有标签自上而下*

##在XHTML中的用法
- XHTML（Extensible HyperText Markup Language）,是将HTML作为XML的应用重新定义的标准
<号被当做标签开头来解析，且后面不能跟空格看，不然会报错，，解决的方法，
    ①加&lt;替换＜号， 变成if（a &lt; b）
    ②加CData片段，CData片段是文档中的一个特殊区域，这个区域中可以包括不需要解析的任意格式的文本内容。代码如下：
    ```javascript
    <script type='text/javascript' >
        <![CDATA[
            function compare(a,b){
                if(a < b){
                    ....;
                }
            }
        ]]>         //是这样的格式 <![CDATA[...]]>
    </script>
    ```
- 在不兼容XHTML的浏览器中只需要用
``` javascript
<script>
//<!CDATA[
    var a=100;
    var b=50;
    function compare(a,b){
        if(a > b){
            alert(a+b);
        }

    }
    compare(a,b);
//  ]]>
</script>
```
就可以注释掉相应CDATA
- 不过这一切都不会在外部script中发生
##文档模式
针对浏览器
- 混杂模式会让 IE的行为和包含非标准特性的IE5相同
- 标准模式使得IE的行为更接近标准行为
- 准标准模式（almost standards mode ），很多特性符合标准，但在处理图片间隙等的时候不一致
- 如果文档开始出没有发现规定的相应版本的文档声明：<!DOCTYPE>等，就会开启混杂模式，不同浏览器在其中的差异非常大。
- 一般说的标准包括了除混杂模式外的的模式

##noscript标签
- 针对不支持js的浏览器可以显示<noscript>问页面需要浏览器支持js</noscript>>
- 