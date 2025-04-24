#pragma once

#include "Member.h"

bool Contain(const Group& group, const Member member) {
    return std::ranges::find(group, member) != group.end();
}

bool Contain(const Group& group, const Group& members) {
    for (auto& it : members) {
        if (!Contain(group, it)) { return false; }
    }

    return true;
}

bool Contain(const Group& group, const Group& members, const size_t any) {
    size_t count = 0;
    for (auto& it : members) {
        if (Contain(group, it)) { count++; }
    }

    return count >= any;
}

// ------------------------------------------------
// return true if satisfy the rule (SOX)
// ------------------------------------------------

// 高咲侑会在步梦不在、身边只有一个人的情况下推倒除米娅以外的其他任何同好会成员。
bool Rule_1(const Group& group) {
    if (!Contain(group, Member::Yuu)) { return false; }
    if (Contain(group, Member::Ayumu)) { return false; }
    if (group.size() != 2) { return false; }
    if (Contain(group, Member::Mia)) { return false; }

    return true;
}

// 如果出现了高咲侑身边只有雪菜、小静子、ksks或仅有其中任意两个人的情况，侑都会把她们一起推倒。
bool Rule_2(const Group& group) {
    if (!Contain(group, Member::Yuu)) { return false; }
    if (group.size() != 2 && group.size() != 3) { return false; }

    const auto g = Group{ Member::Setsuna, Member::Shizuku, Member::Kasumi };
    if (group.size() == 2 && Contain(group, g, 1)) { return true; }
    if (group.size() == 3 && Contain(group, g, 2)) { return true; }

    return false;
}

// 步梦只要和高咲侑在一个区域就可以看住高咲侑杜绝其一切DD行为。
// 但如果只有她们二人在一起，高咲侑就会被她推倒。
bool Rule_3(const Group& group) {
    return Contain(group, Member::Yuu) && Contain(group, Member::Ayumu);
}
// 雪菜不会主动推倒任何人。
bool Rule_4(const Group& group) { return false; }

// ksks和高咲侑处于同一区域、身边只有她们以外的一个人
// 且这个人不是步梦或小静子的时候，她会和高咲侑偷吃
bool Rule_5(const Group& group) {
    if (group.size() == 3) {
        if (!Contain(group, Member::Yuu)) { return false; }
        if (!Contain(group, Member::Kasumi)) { return false; }
        if (Contain(group, Member::Ayumu)) { return false; }
        if (Contain(group, Member::Shizuku)) { return false; }

        return true;
    }

    return false;
}

// 小静子在和ksks独处时会把ksks推倒
bool Rule_6(const Group& group) {
    return group.size() == 2
        && Contain(group, Member::Kasumi)
        && Contain(group, Member::Shizuku);
}

// 小静子和高咲侑在同一区域时，如果该区域人数≤4且该区域没有步梦，她就会和高咲侑偷吃。
bool Rule_7(const Group& group) {
    if (group.size() > 4) { return false; }
    if (!Contain(group, Member::Shizuku)) { return false; }
    if (!Contain(group, Member::Yuu)) { return false; }
    if (Contain(group, Member::Ayumu)) { return false; }

    return true;
}

// 小静子和彼方学姐独处时会推倒她。
bool Rule_8(const Group& group) {
    return group.size() == 2
        && Contain(group, Member::Kanata)
        && Contain(group, Member::Shizuku);
}

// 果林在和雪菜独处时会把她推倒。
bool Rule_9(const Group& group) {
    return group.size() == 2
        && Contain(group, Member::Karin)
        && Contain(group, Member::Setsuna);
}

// special rule, only available on ship
// 果林独自开船会迷路（不要纠结怎么迷得路）
bool Rule_10(const Group& group) { 
    return group.size() == 1 && Contain(group, Member::Karin);
}

// 艾玛和果林独处时会把果林推倒。
bool Rule_11(const Group& group) {
    return group.size() == 2
        && Contain(group, Member::Karin)
        && Contain(group, Member::Emma);
}

// special rule, only available on ship
// 彼方一个人时会睡着，所以她不能独自开船。
bool Rule_12(const Group& group) {
    return group.size() == 1 && Contain(group, Member::Kanata);
}

// 爱姐和果林、璃奈中任意一人独处时会把她推倒。
bool Rule_13(const Group& group) {
    if (group.size() != 2) { return false; }

    if (Contain(group, Member::Ai)) {
        if (Contain(group, Member::Karin)) { return true; }
        if (Contain(group, Member::Rina)) { return true; }
    }

    return false;
}

// 爱姐和璃奈处于同一区域时如果该区域人数≥5就会因为没人注意她们开始偷吃
// 但前提是该区域不能存在米娅、果林或高咲侑中的任意一人
bool Rule_14(const Group& group) {
    if (!Contain(group, Member::Ai)) { return false; }
    if (!Contain(group, Member::Rina)) { return false; }
    if (group.size() < 5) { return false; }
    if (Contain(group, { Member::Mia,Member::Karin,Member::Yuu }, 1)) { return false; }
    
    return true;
}

// 璃奈在和爱姐或米娅中任意一人独处时都会推倒她。且如果璃奈身边仅有此二人时会开启三人行。
bool Rule_15(const Group& group) {
    if(group.size() == 2) {
        if (Contain(group, Member::Rina)) {
            if (Contain(group, Member::Ai)) { return true; }
            if (Contain(group, Member::Mia)) { return true; }
        }
    }

    if (group.size() == 3) {
        if (Contain(group, { Member::Rina, Member::Ai, Member::Mia })) {
            return true;
        }
    }

    return false;
}

// 米娅在和璃奈独处时会开趴。
bool Rule_16(const Group& group) {
    return group.size() == 2
        && Contain(group, Member::Mia)
        && Contain(group, Member::Rina);
}

// 岚珠在和栞子、米娅、步梦中任意一人独处时会强行将其推倒。
bool Rule_17(const Group& group) {
    if (group.size() != 2) { return false; }
    if (!Contain(group, Member::LanZhu)) { return false; }
    if (Contain(group, Member::Shioriko)) { return true; }
    if (Contain(group, Member::Mia)) { return true; }
    if (Contain(group, Member::Ayumu)) { return true; }

    return false;
}

// 岚珠在身边仅有栞子和米娅时会开启三人行。
bool Rule_18(const Group& group) {
    return group.size() == 3 && Contain(group, { Member::LanZhu, Member::Shioriko, Member::Mia });
}

// 岚珠在身边仅有栞子、米娅、高咲侑时会开启四人行。（你和侑就是两个泰迪
bool Rule_19(const Group& group) {
    return group.size() == 4 && Contain(group, { Member::LanZhu, Member::Shioriko, Member::Mia, Member::Yuu });
}

// 栞子和步梦或雪菜独处时会推倒她们。
bool Rule_20(const Group& group) {
    if (group.size() != 2) { return false; }
    if (!Contain(group, Member::Shioriko)) { return false; }
    if (Contain(group, Member::Ayumu)) { return true; }
    if (Contain(group, Member::Setsuna)) { return true; }

    return false;
}

using Func = decltype(&Rule_1);
using RuleSet = std::vector<Func>;

const static RuleSet ShoreRuleSet = {
    Rule_1,
    Rule_2,
    Rule_3,
    Rule_4,
    Rule_5,
    Rule_6,
    Rule_7,
    Rule_8,
    Rule_9,
    Rule_11,
    Rule_13,
    Rule_14,
    Rule_15,
    Rule_16,
    Rule_17,
    Rule_18,
    Rule_19,
    Rule_20,
};

const static RuleSet ShipRuleSet = {
    Rule_1,
    Rule_2,
    Rule_3,
    Rule_4,
    Rule_5,
    Rule_6,
    Rule_7,
    Rule_8,
    Rule_9,
    Rule_10,
    Rule_11,
    Rule_12,
    Rule_13,
    Rule_14,
    Rule_15,
    Rule_16,
    Rule_17,
    Rule_18,
    Rule_19,
    Rule_20,
};

#include <iostream>
#include <format>

// return true if one match
bool CheckRuleSet(const Group& group,const RuleSet& ruleSet) {
#ifdef OUTPUT_DEBUG_INFO
    PrintGroup(group);
#endif

    for (size_t index = 0; index < ruleSet.size(); index++) {
        if (ruleSet[directory](group)) {
#ifdef OUTPUT_DEBUG_INFO
            std::cout << "Check Rule " << index << " Failed!" << "\n";
#endif
            return true;
        }

    }

#ifdef OUTPUT_DEBUG_INFO
    std::cout << "Pass!\n";
#endif

    return false;
}
