# 要求

- 读懂原遗留代码
- 补充测试用例
- 重构到clean code的程度

# 构建

重构后的代码主要分为3个文件夹:include,src,test并包含Makefile,可以
在OSX和Linux上进行编译和运行:

    > make       # 构建
    > make test  # 运行测试用例

在代码中没有使用题目带的cuultralight测试框架,而是使用的Catch测试框架,
也是一个头文件即可完成测试用例的编写和测试.

工程文件中包含git文件夹,包含所有修改记录,可以通过git命令进行查询.

# 重构

原有代码,主要集中在CentralUnit这个类中,用于控制传感就Sensor,并根据
传感器状态进行蜂鸣显示等行为.

重构代码仍然是以CentralUnit为基础进行重构,将CentralUnit分离为由几个模
块组成,分别是SensorManager,CheckModule,SecurityPanel和HomeGuardView
组成:

- HomeGuardView: 显示模块,负责显示信息.
- SecurityPanel: 安全管理模块,负责设置安全码,告警等.
- SensorManager: 传感器管理器,管理所有传感器.
- CheckModule:   自检模块,对传感器进行检测,确认传感器状态.

                             +--------------------+
                             |                    |
             ----------------+    CentralUnit     +-----------------
             |               |                    |                |
             |               +--+--------------+--+                |
             |                  |              |                   |
             |                  |              |                   |
    +--------+----+   +---------+---+     +----+--------+     +----+-------+
    |HomeGuardView|   |SecurityPanel|     |SensorManager|     |CheckModule |
    |             |   |             |     |             +-----+            |
    +-------------+   +-------------+     +-------+-----+     +------------+
                                                  |
                                                  |
                                      ------------+------------
                                      |           |           |
                              +-------+-+    +----+----+    +-+-------+
                              |Sensor1  |    |Sensor2  |    |Sensor3  | ...
                              +---------+    +---------+    +---------+

# 主要修改记录

    * 568606e (HEAD -> master, dev) 修改一些代码风格,统一整个代码格式
    * 311d555 typo fix
    * 54ee39e typo fix
    * dc91a94 统一代码风格 将get,set函数放到头文件中,这样更简练一些
    * 9b74d43 清理不必要的注释,代码即注释
    * 4d4a65f typo fix
    * 65ac6bd 统一命名风格
    * 4357bcd 将SecurityPanel也修改为shared_ptr
    * 6b5bd4e 将check模块单独出来作为一个类
    * 52248a7 修改SensorManager为shared_ptr,用于组件间共享
    * 9c93d0a 将SecurityCode输入放到一个类中管理
    * 8717792 将变量修改为值
    * 664e34b 将sensor操作放到SensorManager类中
    * 91360c4 优化方法,抽取到为函数
    * c0f28c3 增加sensor test用例
    * 50b4c9b 将Sensor测试状态移动到Sensor.h文件中,并使用类表示
    * 4f702fa typo fix
    * 3025804 使用宏来简化初始化消息列表
    * bc75908 typo fix
    * 7962804 typo fix
    * bcf36de 重构获取Sensor中message的方法
    * 87436f8 统一私有变量命名为前缀下划线
    * e222391 将Sensor::Type修改为C++11 style的enum class SensorType
    * 9751c9e 做了一些重命名等操作 内部函数和变量统一以下划线开头 优化了一些函数类型信息
    * 5be3dca 将runSensorTest单独出来作为函数处理
    * df5274e 增加CentrolUnit没有注册Sensor的情况,并优化代码流程
    * f76bf71 将getSensorMessage移动到Sensor类内部
    * af86b38 增加sensor函数,触发行为
    * dd8640a 增加查询sensor的用例
    * e1c4131 使用已有的函数获取Sensor
    * e1c95e2 增加函数,分解broadcast中的packet,并增加测试用例
    * 331ee99 消除单元测试框架clang警告 overloaded-virtual
    * 8ea10aa typo fix for CentralUnit
    * c71a7ed ignore tag files
    * 052a020 统一编码格式为UTF8,换行符为LF(Unix style)
    * e583f84 增加单元测试目录
    * 25dfb4d 修改统一换行符,避免编辑器中出现^M字符
    * db1fcff 修改目录结构,增加Makefile用于构建
    * 3778d35 first commit
