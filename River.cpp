#include <iostream>

//#define OUTPUT_DEBUG_INFO

#include "Member.h"
#include "Rules.h"

struct State {
    Group ship = {};
    Group leftShore = {};
    Group rightShore = {};

    using Steps = std::vector<Group>;
    Steps shipToRightSteps = {};
    Steps leftShoreSteps = {};
    Steps shipToLeftSteps = {};
    Steps rightShoreSteps = {};

    bool CheckRule() const {
        if (CheckRuleSet(ship, ShipRuleSet)) { return true; }
        if (CheckRuleSet(leftShore, ShoreRuleSet)) { return true; }
        if (CheckRuleSet(rightShore, ShoreRuleSet)) { return true; }

        return false;
    }

    static bool CheckRule(const State& state) { return state.CheckRule(); }

    void PrintSteps() {
        for (size_t index = 0; index < shipToRightSteps.size(); index++) {
            std::cout << "============ Step " << index << " ============\n";
            std::cout << "====== Left -> Ship ======\n";
            std::cout << "Ship:\n";
            PrintGroup(shipToRightSteps[index]);

            if (leftShoreSteps[index].empty()) {
                std::cout << "====== End ======\n";
                return;
            }
            std::cout << "Left:\n";
            PrintGroup(leftShoreSteps[index]);

            std::cout << "====== Right -> Ship ======\n";
            std::cout << "Ship:\n";
            PrintGroup(shipToLeftSteps[index]);
            std::cout << "Right:\n";
            PrintGroup(rightShoreSteps[index]);
            std::cout << "\n";
        }
    }
};

static std::vector<State> solved = {};

struct Result {
    bool bSolve = false;
    bool bValid = false;
};

static Result Solve(State prevState) {
    bool bSolve = false;
    bool bToRightValid = false; bool bToLeftValid = false;
    for (size_t fst = 0; fst < prevState.leftShore.size(); fst++) {
        for (size_t scd = fst + 1; scd < prevState.leftShore.size(); scd++) {
            State curState = prevState;
#ifdef OUTPUT_DEBUG_INFO
            std::cout << "====== Left -> Ship ======\n";
#endif
            curState.ship = { curState.leftShore[fst],curState.leftShore[scd] };
            if (CheckRuleSet(curState.ship, ShipRuleSet)) { continue; }
#ifdef OUTPUT_DEBUG_INFO
            std::cout << "Ship Valid\n";
#endif

            auto it = std::remove_if(curState.leftShore.begin(), curState.leftShore.end(),
                [&](const Member& member) {
                    for (auto& shipMember : curState.ship) {
                        if (shipMember == member) { return true; }
                    }

                    return false;
                });

            Group leftShore = curState.leftShore;
            curState.leftShore.erase(it, curState.leftShore.end());
            if (CheckRuleSet(curState.leftShore, ShoreRuleSet)) { continue; }
#ifdef OUTPUT_DEBUG_INFO
            std::cout << "Left Valid\n";
#endif

            curState.shipToRightSteps.push_back(curState.ship);
            curState.leftShoreSteps.push_back(curState.leftShore);
            bToRightValid = true;

            if (curState.leftShore.empty()) {
#ifdef OUTPUT_DEBUG_INFO
                std::cout << "============ Solve! ============\n";
                curState.PrintSteps();
#else
                solved.push_back(curState);
                std::cout << "Solved: " << solved.size() << "\n";
#endif

                bSolve = true;

                return {.bSolve = true, .bValid  = true};
            }

            for (auto& member : curState.ship) { curState.rightShore.push_back(member); }

            bToLeftValid = false;
            for (size_t idx = 0; idx < curState.rightShore.size(); idx++) {
#ifdef OUTPUT_DEBUG_INFO
                std::cout << "====== Right -> Ship ======\n";
#endif

                curState.ship = { curState.rightShore[idx] };
                if (CheckRuleSet(curState.ship, ShipRuleSet)) { continue; }
#ifdef OUTPUT_DEBUG_INFO
                std::cout << "Ship Valid\n";
#endif

                Group rightShore = curState.rightShore;
                curState.rightShore.erase(curState.rightShore.begin() + idx);
                if (CheckRuleSet(curState.rightShore, ShoreRuleSet)) { continue; }
#ifdef OUTPUT_DEBUG_INFO
                std::cout << "Right Valid\n";
#endif

                curState.leftShore.push_back(curState.ship[0]);
                curState.shipToLeftSteps.push_back(curState.ship);
                curState.rightShoreSteps.push_back(curState.rightShore);

#ifdef OUTPUT_DEBUG_INFO
                std::cout << "====== Next Step ======\n";
#endif
                const auto result = Solve(curState);
                if (result.bSolve || !result.bValid) {
                    curState.leftShore.pop_back();
                    curState.rightShore = rightShore;
                    curState.shipToLeftSteps.pop_back();
                    curState.rightShoreSteps.pop_back();

                    continue;
                }

                bToLeftValid = true;
            }

            if (bToLeftValid == false) {
                curState.leftShore = leftShore;
                curState.shipToRightSteps.pop_back();
                curState.leftShoreSteps.pop_back();
            }
        }
    }

    return { .bSolve = bSolve, .bValid = bToRightValid && bToLeftValid };
}

int main() {
    State initState = { .ship = {}, .leftShore = DouKouKai, .rightShore = {} };
    Solve(initState);

#ifndef OUTPUT_DEBUG_INFO
    for (size_t index = 0; index < solved.size(); index++) {
        std::cout << "================== Solve " << index << " ==================\n";
        solved[index].PrintSteps();
        std::cout << "\n";
    }
#endif
}
