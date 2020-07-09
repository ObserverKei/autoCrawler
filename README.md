用来爬取网站资源
目前包括小说、
还有图片、
先是网站
然后是分页
然后是分页中的资源
然后再导入下载列表进行下载。
需要有日志显示下载进度，需要下载文件到共享文件夹。

工作内容：
	下载小说	     
  


为了加深理解，参照《代码大全》第一章，软件构建活动中的具体任务(task)，基于Linux socket套接字网络编程对爬虫软件进行重构。
软件构建活动中的具体任务(task)如下所示：  
	1. 验证有关的基础工作已经完成,因此构建活动可以顺利地进行下去。  
	2. 确定如何测试所写的代码。  
	3. 设计并编写类(class )和子程序(routine) 。  
	4. 创建并命名变量(variable)和具名常量(named constant)  
	5. 选择控制结构(control structure) ,组织语句块。  
	6. 对你的代码进行单元测试和集成测试,并排除其中的错误。  
	7. 评审开发团队其他成员的底层设计和代码,并让他们评审你的工作。  
	8. 润饰代码,仔细进行代码的格式化和注释。  
	9. 将单独开发的多个软件组件集成为一体。  
	10. 调整代码(tuning code) ,让它更快、更省资源。  

## 1. 验证有关的基础工作已经完成,因此构建活动可以顺利地进行下去。

	项目autoCrawler 是利用linux socket套接字网络编程提供的接口来发送tcp协议数据，并利用tcp来传送http协议请求，达到模拟浏览器，进而下载网页文件的目的。  
	 	1.  先是输入链接，然后利用匹配器对链接进行匹配，如果是预设http链接，则进行http内部资源获取，下载html页面，并解析html页面里面有多少待处理（http box）资源，  
	 	2.  因为http链接对应的html网页打开后可能含有多页，所以需要先对页面进行解析，把每个页面的连接解析出来，再进一步获取单页里面的（line box）资源。  
	 	3.  然后再对每个页面里面的所有资源进行解析获取，取得资源下载链接，下载资源。  
	 	4.  再对资源类型进行匹配，如果是小说/图片则进入对应的资源处理函数进一步处理。最后生成目标文件。  
	
	如图步骤所示   

<img src="https://github.com/ObserverKei/autoCrawler/tree/master/download/autoCrawler.png" width="50%">

![RUNOOB 图标](https://github.com/ObserverKei/autoCrawler/tree/master/download/autoCrawler.png)

![image](https://github.com/ObserverKei/autoCrawler/tree/master/download/autoCrawler.png)
	本程序将使用面向对象的编程思维来进行构建，如图所示，设计一种蜘蛛，专门爬取对应网络的目标数据，  
	蜘蛛在workSpace工作空间进行工作，蜘蛛具有的action执行动作，以及state自身目前的状态，蜘蛛还可以携带workData工作数据。如下图所示。  
	
![image](https://github.com/ObserverKei/autoCrawler/tree/master/download/Spider.png)
	为了给每只蜘蛛分配任务，需要一个“指挥系统”，来专门分配任务队列，控制每只蜘蛛下一步应该做什么，蜘蛛只需要照做就行。而为了使项目比较简单，将下一步要做的任务交给上一只蜘蛛布置。  
		
## 2. 确定如何测试所写的代码。
	利用控制台调试，能得到输出结果就行。  
## 3. 设计并编写类(class )和子程序(routine) 。 
## 4. 创建并命名变量(variable)和具名常量(named constant)
```c++
template<D>  
class Spider {  
public:  
	Spider(){}  
	~Spider(){}  
	bool do(void) {  
		if (m_workList == nullptr)  
		{  
			return false;  
		}  
		m_workList->front()->second(m_workList->front()->first());  
		m_workList->pop();  
		  
		return true;  
	}  
private:  
	int m_workFlag;  
	D Data;  
	queue<pair<D, workFunction> > *m_workList;  
};  
```
## 5. 选择控制结构(control structure) ,组织语句块。
```c++ 
	while (spider.do());  
```
## 6. 对你的代码进行单元测试和集成测试,并排除其中的错误。
	//待定  
## 7. 评审开发团队其他成员的底层设计和代码,并让他们评审你的工作。
	//待定  
## 8. 润饰代码,仔细进行代码的格式化和注释。
	//待定  
## 9. 将单独开发的多个软件组件集成为一体。
	//待定  
## 10. 调整代码(tuning code) ,让它更快、更省资源。
	//待定  

