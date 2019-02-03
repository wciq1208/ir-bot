#include "response.h"
#include "fmt/format.h"
#include "router.h"
#include "walkure.h"

namespace ir {
    void Response::OnPrivateMessage(const cq::PrivateMessageEvent &e) {
        logging::debug(u8"消息", u8"收到私聊消息：" + e.message + u8"，发送者：" + std::to_string(e.user_id));
        try {
            //  api::send_private_msg(e.user_id, e.message + u8"test" + r + u8"test"); // echo 回去

            Router().work(e);

            // MessageSegment 类提供一些静态成员函数以快速构造消息段
            /*cq::Message msg = cq::MessageSegment::contact(cq::MessageSegment::ContactType::GROUP, 201865589);
            msg.send(e.target); */// 使用 Message 类的 send 成员函数
        } catch (const cq::exception::ApiError &err) {
            // API 调用失败
            logging::debug(u8"API", u8"调用失败，错误码：" + std::to_string(err.code));
        }

        e.block(); // 阻止事件继续传递给其它插件
    }
} // namespace ir
