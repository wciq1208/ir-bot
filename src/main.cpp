#include <optional>
#include "handle/response.h"
#include "misc/init.h"
#include "misc/type.h"

// 初始化 App Id
CQ_INITIALIZE("com.example.demo");

// 插件入口，在静态成员初始化之后，app::on_initialize 事件发生之前被执行，用于配置 SDK 和注册事件回调
CQ_MAIN {
    cq::config.convert_unicode_emoji = true; // 配置 SDK 自动转换 Emoji 到 Unicode（默认就是 true）
    ir::init();
    app::on_enable = [] {
        // logging、api、dir 等命名空间下的函数只能在事件回调函数内部调用，而不能直接在 CQ_MAIN 中调用
        logging::debug(u8"启用", u8"插件已启动");
    };

    event::on_private_msg = ir::Response::OnPrivateMessage;

    event::on_group_msg = [](const auto &e /* 使用 C++ 的 auto 关键字 */) {
        const auto memlist = api::get_group_member_list(e.group_id); // 获取数据接口
        cq::Message msg = u8"本群一共有 "; // string 到 Message 自动转换
        msg += std::to_string(memlist.size()) + u8" 个成员"; // Message 类可以进行加法运算
        if (e.target.group_id.has_value() && e.target.group_id.value() == 594659921) {
            message::send(e.target, msg); // 使用 message 命名空间的 send 函数
            logging::debug(u8"API", u8"测试：" + std::to_string(msg));
        }
    };
}

// 添加菜单项，需要同时在 <appid>.json 文件的 menu 字段添加相应的条目，function 字段为 menu_demo_1
CQ_MENU(menu_demo_1) {
    logging::info(u8"菜单", u8"点击了示例菜单1");
    try {
        api::send_private_msg(10000, "hello");
    } catch (const cq::exception::ApiError &) {
        logging::warning(u8"菜单", u8"发送失败");
    }
}

// 不像 CQ_INITIALIZE 和 CQ_MAIN，CQ_MENU 可以多次调用来添加多个菜单
CQ_MENU(menu_demo_2) {
    logging::info(u8"菜单", u8"点击了示例菜单2");
    cq::config.convert_unicode_emoji = !cq::config.convert_unicode_emoji;
}
