#pragma once

#include <cstdint>
#include <vector>

enum class Member :std::uint8_t {
    Yuu,
    Ayumu,
    Kasumi,
    Shizuku,
    Karin,
    Ai,
    Kanata,
    Setsuna,
    Emma,
    Rina,
    Shioriko,
    Mia,
    LanZhu,
};

const char* MemberToString(const Member member) {
    switch (member) {
    case Member::Yuu:return "Yuu";
    case Member::Ayumu:return "Ayumu";
    case Member::Kasumi:return "Kasumi";
    case Member::Shizuku:return "Shizuku";
    case Member::Karin:return "Karin";
    case Member::Ai:return "Ai";
    case Member::Kanata:return "Kanata";
    case Member::Setsuna:return "Setsuna";
    case Member::Emma:return "Emma";
    case Member::Rina:return "Rina";
    case Member::Shioriko:return "Shioriko";
    case Member::Mia:return "Mia";
    case Member::LanZhu:return "LanZhu";
    }
}

using Group = std::vector<Member>;

#include <iostream>

void PrintGroup(const Group& group) {
    for (auto& member : group) {
        std::cout << MemberToString(member);
        std::cout << "  ";
    }

    std::cout << "\n";
}

const static Group DouKouKai = {
    Member::Yuu,
    Member::Ayumu,
    Member::Kasumi,
    Member::Shizuku,
    Member::Karin,
    Member::Ai,
    Member::Kanata,
    Member::Setsuna,
    Member::Emma,
    Member::Rina,
    Member::Shioriko,
    Member::Mia,
    Member::LanZhu,
};
