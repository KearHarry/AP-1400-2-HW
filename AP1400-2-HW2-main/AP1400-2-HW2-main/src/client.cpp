#include "client.h"
#include "server.h"
#include "crypto.h"
#include <iostream>
#include <random>

/**
 * 构造函数：初始化 Client
 * @param id 客户端识别码
 * @param server 持有的服务器引用
 */
Client::Client(std::string id, const Server& server) : server(&server), id(id) {
    // 构造时自动生成 RSA 公私钥对并存储
    crypto::generate_key(public_key, private_key);
}

/**
 * 获取客户端 ID
 * @return std::string 用户名或ID
 */
std::string Client::get_id() const { return id; }

/**
 * 获取客户端公钥（用于他人验证签名）
 * @return PEM 格式公钥字符串
 */
std::string Client::get_publickey() const { return public_key; }

/**
 * 从服务器请求获取当前钱包余额
 * @return double 余额
 */
double Client::get_wallet() const { return server->get_wallet(id); }

/**
 * 使用自己的私钥为一段文本进行签名，确保不可伪造
 * @param txt 要签名的明文
 * @return Base64 格式的数字签名
 */
std::string Client::sign(std::string txt) const {
    return crypto::signMessage(private_key, txt);
}

/**
 * 发起一笔转账交易
 * @param receiver 接收方 ID
 * @param value 转账金额
 * @return 任务提交是否成功（仅表示是否被服务器接受到 pending 队列）
 */
bool Client::transfer_money(std::string receiver, double value) const {
    // 构造标准的交易字符串格式: sender-receiver-value
    std::string trx = id + "-" + receiver + "-" + std::to_string(value);
    // 生成该交易的数字签名
    std::string signature = sign(trx);
    // 将交易和签名发送到服务器的待处理队列
    return server->add_pending_trx(trx, signature);
}

/**
 * 生成用于挖矿的随机 nonce
 * @return 随机生成的 size_t 类型索引
 */
size_t Client::generate_nonce() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    // 生成 0 到 100 万之间的随机整数
    std::uniform_int_distribution<size_t> dis(0, 1000000);
    return dis(gen);
}