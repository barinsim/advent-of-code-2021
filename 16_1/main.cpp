#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <sstream>
#include <variant>
#include <string>

constexpr int LITERAL_ID = 4;

std::stringstream convertToBinary(std::istream& is)
{
    static std::unordered_map<char, std::string> dict = { {'0', "0000"},
                                                          {'1', "0001"},
                                                          {'2', "0010"},
                                                          {'3', "0011"},
                                                          {'4', "0100"},
                                                          {'5', "0101"},
                                                          {'6', "0110"},
                                                          {'7', "0111"},
                                                          {'8', "1000"},
                                                          {'9', "1001"},
                                                          {'A', "1010"},
                                                          {'B', "1011"},
                                                          {'C', "1100"},
                                                          {'D', "1101"},
                                                          {'E', "1110"},
                                                          {'F', "1111"} };
    std::stringstream ss;
    char hex;
    while (is >> hex) {
        ss << dict[hex];
    }
    return ss;
}

std::string readBits(std::stringstream& ss, std::size_t count)
{
    std::string bits(count + 1, '\0');
    ss.read(bits.data(), count);
    return bits;
}

struct Header {
    int version = -1;
    int typeId = -1;
    int lengthId = -1;
    int len = -1;
    std::size_t bitsRead = 0;
};

int toDec(const std::string& bin)
{
    return std::stoi(bin, nullptr, 2);
}

Header readHeader(std::stringstream& ss)
{
    Header h;
    h.version = toDec(readBits(ss, 3));
    h.bitsRead += 3;
    h.typeId = toDec(readBits(ss, 3));
    h.bitsRead += 3;
    if (h.typeId != LITERAL_ID) {
        h.lengthId = toDec(readBits(ss, 1));
        h.bitsRead += 1;
        std::size_t bits = h.lengthId == 0 ? 15 : 11;
        h.len = toDec(readBits(ss, bits));
        h.bitsRead += bits;
    }
    return h;
}

struct Literal {
    int num = 0;
    std::size_t bitsRead = 0;
};

Literal readLiteral(std::stringstream& ss)
{
    int flag;
    Literal lit;
    do {
        flag = toDec(readBits(ss, 1));
        lit.num <<= 4;
        lit.num += toDec(readBits(ss, 4));
        lit.bitsRead += 5;
    } while(flag != 0);
    return lit;
}

struct Packet;

struct Operator {
    std::vector<std::unique_ptr<Packet>> packets;
    std::size_t bitsRead() const;
};

struct Packet {
    Header header;
    std::variant<Operator, Literal> data;
    std::size_t bitsRead() const {
        std::size_t res = header.bitsRead;
        if (std::holds_alternative<Operator>(data)) {
            res += std::get<Operator>(data).bitsRead();
        } else {
            res += std::get<Literal>(data).bitsRead;
        }
        return res;
    }
};

std::size_t Operator::bitsRead() const {
    std::size_t res = 0;
    for (auto& p : packets) {
        res += p->bitsRead();
    }
    return res;
}

Operator readOperator(std::stringstream& ss, const Header& header);

Packet readPacket(std::stringstream& ss)
{
    Packet packet;
    packet.header = readHeader(ss);
    if (packet.header.typeId == LITERAL_ID) {
        packet.data = readLiteral(ss);
    } else {
        packet.data = readOperator(ss, packet.header);
    }
    return packet;
}

Operator readOperator(std::stringstream& ss, const Header& header)
{
    Operator op;
    if (header.lengthId == 1) {
        for (int i = 0; i < header.len; ++i) {
            auto child = std::make_unique<Packet>(readPacket(ss));
            op.packets.push_back(std::move(child));
        }
    } else {
        std::size_t bitsRead = 0;
        while (bitsRead < header.len) {
            auto child = std::make_unique<Packet>(readPacket(ss));
            bitsRead += child->bitsRead();
            op.packets.push_back(std::move(child));
        }
    }
    return op;
}

template <typename Func>
void traverse(Packet* root, Func func)
{
    func(root);
    if (std::holds_alternative<Operator>(root->data)) {
        auto& op = std::get<Operator>(root->data);
        for (auto& p : op.packets) {
            traverse(p.get(), func);
        }
    }
}

int main()
{
    auto ss = convertToBinary(std::cin);
    Packet root = readPacket(ss);
    int sum = 0;
    traverse(&root, [&sum](Packet* node) { sum += node->header.version; });
    std::cout << sum << std::endl;
}
