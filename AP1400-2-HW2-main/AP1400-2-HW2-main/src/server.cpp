#include "server.h"
#include "client.h"
#include "crypto.h"
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <algorithm>

std::vector<std::string> pending_trxs;

Server::Server() {}

/**
 * 添加一个新客户端到服务器
 * @param id 期望的客户端ID
 * @return 指向新创建客户端的共享指针
 */
std::shared_ptr<Client> Server::add_client(std::string id) {
    // 检查 ID 是否已存在
    for (const auto& [client, balance] : clients) {
        if (client->get_id() == id) {
            // 如果 ID 已存在，按照要求生成 4 位随机数并拼接，递归处理直到唯一
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1000, 9999);
            return add_client(id + std::to_string(dis(gen)));
        }
    }
    
    // 创建新客户端对象
    auto new_client = std::make_shared<Client>(id, *this);
    // 每个新客户端初始赠送 5 个金币
    clients[new_client] = 5.0; 
    return new_client;
}

/**
 * 根据 ID 获取客户端对象指针
 * @param id 客户端识别码
 * @return 对应的 Client 指针，若不存在则返回 nullptr
 */
std::shared_ptr<Client> Server::get_client(std::string id) const {
    for (const auto& [client, balance] : clients) {
        if (client->get_id() == id) {
            return client;
        }
    }
    return nullptr;
}

/**
 * 获取指定客户端的钱包余额
 * @param id 客户端识别码
 * @return 余额
 */
double Server::get_wallet(std::string id) const {
    for (const auto& [client, balance] : clients) {
        if (client->get_id() == id) {
            return balance;
        }
    }
    return 0.0;
}

/**
 * 解析交易字符串 "sender-receiver-value"
 * @param trx 待解析的字符串
 * @param sender 输出发送者ID
 * @param receiver 输出接收者ID
 * @param value 输出交易金额
 * @return 成功返回 true，格式错误抛出 std::runtime_error
 */
bool Server::parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value) {
    size_t first_dash = trx.find('-');
    size_t last_dash = trx.rfind('-');
    
    // 基本格式检查：必须包含两个连字符
    if (first_dash == std::string::npos || last_dash == std::string::npos || first_dash == last_dash) {
        throw std::runtime_error("Invalid transaction format");
    }
    
    sender = trx.substr(0, first_dash);
    receiver = trx.substr(first_dash + 1, last_dash - first_dash - 1);
    try {
        value = std::stod(trx.substr(last_dash + 1));
    } catch (...) {
        throw std::runtime_error("Invalid transaction value");
    }
    return true;
}

/**
 * 验证非完整交易并加入待处理队列
 * @param trx 交易详细信息字符串
 * @param signature 发送者的数字签名
 * @return 验证通过返回 true
 */
bool Server::add_pending_trx(std::string trx, std::string signature) const {
    std::string sender, receiver;
    double value;
    
    // 1. 解析交易字符串的基本成分
    try {
        parse_trx(trx, sender, receiver, value);
    } catch (...) {
        return false;
    }
    
    // 2. 核心校验：发送者和接收者都必须存在，且不能是同一个人
    auto sender_ptr = get_client(sender);
    auto receiver_ptr = get_client(receiver);
    if (!sender_ptr || !receiver_ptr || sender == receiver) {
        return false;
    }

    // 3. 检查余额是否足够支付
    if (clients.at(sender_ptr) < value) {
        return false;
    }
    
    // 4. 使用发送者的公钥验证 RSA 签名，确保交易确实由本人发起
    bool authentic = crypto::verifySignature(sender_ptr->get_publickey(), trx, signature);
    if (authentic) {
        pending_trxs.push_back(trx);
        return true;
    }
    return false;
}

/**
 * 模拟虚拟货币“挖矿”过程
 * 计算 mempool 哈希，并转账所有待处理交易
 * @return 找到匹配哈希时所用的 nonce
 */
size_t Server::mine() {
    if (pending_trxs.empty()) return 0;
    
    // 合并所有待处理交易生成内存池(mempool)字符串
    std::string mempool = "";
    for (const auto& trx : pending_trxs) {
        mempool += trx;
    }
    
    size_t nonce = 0;
    std::shared_ptr<Client> winning_client = nullptr;
    bool solved = false;
    
    // 循环直到某个客户端生成的 nonce 使得哈希满足特定条件（前10位含 "000"）
    while (!solved) {
        for (const auto& [client, balance] : clients) {
            nonce = client->generate_nonce();
            std::string hash = crypto::sha256(mempool + std::to_string(nonce));
            
            // 挖矿难度检查 (根据 UPDATE 规则调整为 3 个连续零)
            if (hash.substr(0, 10).find("000") != std::string::npos) {
                winning_client = client;
                solved = true;
                break;
            }
        }
    }
    
    std::cout << "Miner ID: " << winning_client->get_id() << " won! Nonce: " << nonce << std::endl;
    
    // 挖矿成功，正式应用/清算所有挂起的交易
    for (const auto& trx : pending_trxs) {
        std::string s, r;
        double v;
        parse_trx(trx, s, r, v);
        
        auto sender_ptr = get_client(s);
        auto receiver_ptr = get_client(r);
        
        clients[sender_ptr] -= v;
        clients[receiver_ptr] += v;
    }
    
    // 给成功挖矿的客户端发放奖励 (6.25个金币)
    clients[winning_client] += 6.25;
    // 清空待处理队列
    pending_trxs.clear();
    
    return nonce;
}

