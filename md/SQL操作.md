##SQL操作
###数据库用户
1.建立数据库用户：
create user <用户名> identified by <密码>

2.更改数据库用户的口令
alter user <用户名> identified by <密码>

3.删除用户：
drop user <用户名>


###定义数据库
4.定义数据库
create database <数据库名>
use <数据库名> --要想在数据库中创建表就得首先使用该数据库
###定义数据表
5.创建表
主要包括：字段名，字段数据类型，字段的长度精度和小数位数，对于字符串，长度是字段能容纳下的字符的数目，对于数值类，binary,image等表示的是字节数。精度是指数中数字的位数，，所以只有数值类才有必要指定精度。
N代表长度，P代表精度，S代表小数位数。
CHAR(8) numeric(p,[s])如 numeric(8,3)
null值表示字段值为空，default表示某一字段的默认值。

建立一个学生表： 
CREATE TABLE 学生
(学号 CHAR(8) NOT NULL,
姓名 VARCHAR(20) UNIQUE,
性别 CHAR(2) DEFAULT '男'， 
出生日期 date,    --用来表示注释/*多行注释*/ date没有时间只有年月日，而datetime 有
班级 VARCHAR(20)
);

约束条件 ：not null,unique,primary key, foreign key ，check约束 
如果是两个主键则 多加一个： constraint 约束名 primary key(学号，课程号)；   //单独都要加constraint 后直接跟就不用
foreign key约束指定某一个列或一组列作为外部键，其中包含外部件的表称为从表，另一  
个叫主表，
如：
CREATE TABLE 选课
(学号 CHAR(8) NOT NULL FOREIGN KEY REFERENCES 学生(学号)，
课程号CHAR(5) NOT NULL FOREIGN KEY REFERENCES 课程(课程号)
成绩 NUMERIC(3),
PRIMARY KEY (SNO,CNO));

CHECK约束  ： 成绩 NUMERIC(3) CHECK(SCORE >= 0 AND SCORE <= 100);


综合范例，创建一个学生选课系统数据库，在该数据库中建立学生(学号，姓名，性别，出生年月，政治面貌，籍贯，班级编号)、成绩(学号、课程编号、成绩)，课程(课程编号，课程名称，学分，学时)并在三个表之间建立联系


create database 学生选课系统
 create table 学生
 (学号 varchar(10) not null primary key,
  姓名 nvarchar(5) ,
  性别 nvarchar(2) default '男'，
  出生年月 date,
  政治面貌 nvarchar(3),
  班级编号 varchar(7),
  籍贯   nvarchar(4),
  入学总分 int check (入学总分 >=550)
 )
create table 成绩
(
 学号 varchar(10) not null primary key,
 课程编号 nchar(8) not null foreign key references 课程编号,
 成绩 int not null default 0
)
create table 课程
(
课程编号 nchar(8) not null primary key,
课程名称 nchar(30),
学分 int check(学分>0),
学时 int default 32
)

###修改数据表
6.使用alter命令能够添加新的字段，修改已有的字段

格式：
alter table 表名
add 列名 数据类型 长度 约束等等
alter column 列名 数据类型 长度 约束等等  --修改
也可直接 alter table 学生 add 住址 nvarchar(255)
7.drop column 字段名         --删除字段
删除列必须先删除索引和约束
drop table 表名 --删除表

###定义索引
索引的作用可归纳如下： ①加快查询速度，②保证行的唯一性
8.create unique cluster index sci on 选课(学号，课程号)  --等于给他们建立了索引名为sci索引
9.删除索引
drop index  课程.sci

###数据查询
10.select 命令
select <查询项> from 查询表 where 满足数据表中指定条件的数据 group by <列名--按此进行分组> having<分组条件--用于限定分组必须满足的条件>  order by <列名2--对查询结果按照列名2进行排序>
举例：
select * from 学生   --选出表示学生表的全部列名
select 学号，姓名 from 学生
select 学号，姓名，出生年月 as出生日期 ，班级编号 as 班级号 from 学生  --使用as  
子句将指定列命名为一个新的名称

distinct去掉查询结果中的重复数据
select distinct 籍贯 from 学生
###条件查询
当要在表中找出满足某些条件的行时，需使用where子句，后面跟条件
select 学号，姓名，性别 from学生 where 籍贯='广东' AND 性别 = '女'
###使用特殊运算符查询
11. in 运算符，表示在某个集合中  
select 学号，姓名，性别 from学生 where 籍贯 in('广东','广西')
12. between and 
select 学号，姓名，性别 from学生 where 成绩 between 580 and 660 
13.  like
select 学号，姓名，性别 from学生 where 姓名 like '李%'
-- %匹配0 或多个字符串，_匹配任何单个字符 ，[]：匹配范围内单个[a-z]:a-z  
中任意 ，[^]：匹配任何不再范围内或集合内的单个字符   [^abc]：除了abc都匹配
14. not 
 ###统计查询
15. count 计数: select count(*) as 人数 from 学生 where 籍贯 ='湖北'
16. count(distinct<列名>) 去重复计数：select count(distinct 籍贯) as 籍贯种类 from 学生
17. max() min()sum() avg()
###分组查询
18. group by将查询结果按属性列或属性列组合在行方向上进行分组，每组在属性列或属性  
列组合上有相同的值。

select 籍贯 ，count(*) as人数 from 学生 group by 籍贯            -- 具有相同  
籍贯的元组分一组，对每组使用函数count进行计算，统计出每种籍贯学生的人数
select year(getdate())-year(出生年月) as年龄 ，count(*) as 人数 from 学生group   
by year(getdate())-yeat(出生年月)
select 籍贯，count(*) as 人数 from 学生 group by 籍贯 having count(*）>=3    
--查询学生表中人数在三人以上的省份   having用于组查询where用于基本表和视图。

###查询排序
19. 对结果进行排序时，应该使用order by 子句，排序可升序或降序。使用asc表示升序，desc表示降序
select 学号，姓名，性别 from 学生 order by 入学成绩   --默认使用升序
select 学号，姓名，性别 from  学生 order by 班级编号，入学成绩 desc
--先按照班级编号降序，，相同的再按照入学成绩排 
20.top最高
select top 5 学号，姓名，性别 from 学生 order by 入学成绩 desc
top 20 percent  百分之二十。

###表连接和连接查询
20.以上都是基于一个数据表的查询，数据表之间的联系是通过表的字段值来体现的，这种字段成为连接字段。连接操作的目的是通过加载连接字段的条件将多个表连接起来，以便多个表中查询数据。
表连接的方法有两种：
- 1.表之间班组一定的条件的行进行连接，此时from 子句中指明进行连接的表名
- 2. 利用关键字JOIN进行连接
select 学生.学号，姓名，课程.课程编号，课程名称，成绩 
from 学生，课程，成绩
where 学生.学号 = 成绩.学号
and 课程.课程编号 = 成绩.课程编号
order by 学号 

21.使用join是 inner join 显示符合条件的记录，被称为内连接， left join 显示符合条件  
的数据行一级左边表中不符合条件的数据行，右边显示的是NULL。称为左连接，反之称为右连接。
select 学生.学号，姓名，课程.课程编号，课程名称，成绩 
from学生 
left outer join 选课 
on 学生.学号 = 选课.学号， 
left outer join 课程  
on 课程.课程号 = 选课.课程号

-- from 学生 join 选课 on 学生.学号 = 选课.学号就等同于 from  学生 ，选课    where  
学生.学号 = 选课.学号  
###嵌套查询
22.在select语句中，将一个select..from...where语句嵌套在另一个select...form..where子句或Having短语的条件中的查询称为嵌套查询，处于内层的查询称为子查询，包含子查询的语句称为父查询或外部查询。
，嵌套查询，由内向外执行。

select 学号，姓名，性别，year(出生年月)，籍贯 from 学生 where year(出生年月) =  (select year)(出生年月)  from 学生 where 姓名 = "李平"） --查询学生表中与李平同龄的学生的信息
当子查询的结果不是一个值时，外部使用的时候需要不能直接使用比较运算符，必须在比较运算符后加any或all，也可以使用in关键字
select 姓名 from 学生 where 学号 in(select 学号 from 选课 where 课程编号 = '1211')
--in是在其中，any是任意有就行，all是全都满足才行，上一句中对于in 和any的效果一致

###数据操作

23。-使用insert，update，delete进行操作数据
insert into 学生 values('02020106','男','宁夏')

insert into 学生 (学号，姓名，性别)
values('02002109','晃晃','男')

update学生
set 政治面貌 = '党员'
where 姓名 = '王海'     --修改一行

update 成绩
set 成绩 = 成绩 + 5
where成绩 between  55 and 59   --修改多行

update成绩
set 成绩 =  (select avg(成绩) from 成绩)  --使用子查询 将所有的学生成绩改为平均成绩

delete from 学生 where 学号 = '01010110'  --注意要使用from

###视图
24.视图是一个根据数据库表而制定的虚拟罗技表，是观察表中信息的一个窗口。
25.创建视图 ： create view <视图名> <列名> as select语句 
create view 班级 010101
as 
select 学号，姓名，性别 from 学生 where 班级编号 = '010101'
26.删除视图： drop view <视图名>
27.查询视图： select * from 建筑 0202 where (year(getyear)-year(出生年月))<20 
--没有view
28.更新视图:update 建筑0202 
set 政治面貌 = '群众'
where 姓名 = '老铁'  