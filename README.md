Windows下 cpp http服务器

👩‍🚀尽量用扫描组件的方式加载各个Controller以及他们的路由，方便拓展url映射的method

因为无界面所以在可以避免使用QT，只使用了他的编译，等有空分离出来。



🤹‍♀️使用

```cpp
class DemoController : public Controller
{
public:
    DemoController();

    ~DemoController();

    void Route(std::shared_ptr<httplib::Server>) override;

    void static Demo(const httplib::Request &req, httplib::Response &res);
};

// 继承Controller类并实现方法Route，其映射的类函数必须为static
void DemoController::Route(std::shared_ptr<httplib::Server> server_ptr)
{
    server_ptr->Get("/hi", &DemoController::Demo);

    SPDLOG_INFO("add Route");
}

// 在ServerManager中注册您的Controller 他会自动调用Route函数来给Server添加路由
void ServerManager::ScanController()
{
    // 注册 Controller
    controllers_.push_back(std::make_shared<DemoController>());

    SPDLOG_INFO("Contorller size: {}", controllers_.size());
}
```

