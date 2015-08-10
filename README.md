1、基于 cocos 3.6 修改了某些cpp文件
2、运行cocos2d/download-deps.py 完成配置
3、运行vs2013即可。若遇到问题请反馈至455786463@qq.com 或 Q群195660307 找镜子蓝玉
4、Android版本亦可正常运行（NDK-r10），设计分辨率为960*640或960*540，多分辨率匹配更新设计为BO_BORDER，可以对多种屏幕适配


版本记录：
v0.1.2:
	1、独立线程完成Coin、Obstacle等对象预生成
	2、已完成基本跳跃响应，暂未完成下滑角色模型操作，正考虑将此模块拓展为技能模块。在MoveAbleElem中增加SkillStatus相应的类型指针
	3、大修改：将controller置为scene属性，去管理Layer和对应的model数据；如后期拓展UI相关，则在对应的主Layer层增加子层MVC结构
	4、GameMainController响应游戏级别的事件处理，其他controller分别处理子游戏逻辑
	5、已优化多线程之前切换和互斥锁访问导致的性能下降
	
v0.1.1:
	1、多线程预生成Coin、Obstacle等对象（只要在ElemsPreloadManager中注册预加载即可，已移除之前静态注册的代码）；解决小部分预生成卡顿的问题：将diff计算值缓存使用，减少更新逻辑的重复工作
	2、Android版本亦可正常运行，设计分辨率为960*640，多分辨率匹配暂时未SHOW_ALL，并未对16:9进行兼容（即有黑边）
	3、已完成接触检测、接触逻辑响应、MoveAbleElem回收，
	4、可移动类型标签管理和相关常量替换，使用MoveAbleElemTypeDefines文件
	5、修复API调用问题以及Android版API兼容性代码


v0.1.0:
	1、彻底属于王敬哲的代码：C++实现放射机制
	增加怪物生成管理系统，为每种新可移动怪物增加注册机制（生成静态对象实现类型和（抽象+模板）工厂方法），使用了单个对象内存泄露方式
	2、3D场景，3D模型，实时移动角色模型和怪物模型完成游戏逻辑
	3、C++11，函数指针、目标、抽象工厂模式、管理者模式、反射机制（对，没错。因为模型位置计算有些不同，没有完成整理未绝对放射形式）
	
遗留补记：
	1、性能瓶颈在于1、线程切换以及获锁等待 2、使用elem前要生成Sprite3D，而目前未实现为多线程支持；3、纯渲染模式无逻辑模式未测试；
	2、在配置文件中增加预生成命令格式：AAA全一样则预生成一次30个量，也解决不了这个问题，只能修改Sprite3D增加多线程方式创建
	3、如果希望金币动作同步，则需要将命令格式更改为（ID，LEFT，NUM，OPER），未来中，每次解析三条命令。
	
	1、发现我忘记测试关键的模型渲染和逻辑处理的效率，导致现在难以正确把握性能瓶颈，还是说详细地逐个模块排除；可是有多线程的情况下怎么测试，目前只能先把多线程更改为全部加载elem后再开始测试性能差别
	2、多线程的切换还少应该保证损耗比线程完成的内容要小；同时在多核机子上多线程加载资源的优势才明显，要不然变成累赘。
	3、批量对象的创建不应该使用cocos的create方法，应该自己维护一个数组型内存；也就是说，我要将Ref的引用计数访问方式开放出来，不能使用release方法。同时增加个容器所以对应内存块，再次清理时应先将GameLayer等其他模块的引用计数清理，最后调用Manager的pureInstance操作，将数组指针删除掉。
	
	尝试减低GL calls的次数和跟踪内存的使用情况