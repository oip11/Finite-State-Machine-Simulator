#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <stack>

struct FSM {
    bool nfa = false;  // dfa by default
    int states;
    int inputs;
    int start;
    std::set<int> accepting;
    std::vector<std::map<int, std::vector<int>>> transitions;
    // (initial,symbol) = {possible final states}
    // for dfa, there will only be one possible final state

    void setup(std::string file) {
        std::ifstream ifs(file);
        std::string mode;
        ifs >> mode;  // (non)deterministic
        nfa = (mode == "nondeterministic");
        ifs >> mode >> states;
        ifs >> mode >> inputs;
        ifs >> mode >> start; 

        std::getline(ifs, file);  // newline
        std::getline(ifs, file);  // accepting

        std::stringstream ss(file);
        ss >> mode;  // accepting
        int accepting_states;
        while (ss >> accepting_states)
            accepting.insert(accepting_states);

        getline(ifs, file);  // transitions
        transitions.assign(states, {});

        int initial, final, symbol;
        while (ifs >> initial >> final >> symbol)
            transitions[initial][symbol].push_back(final);
    }

    bool run_dfa(std::vector<int>& input) {
        int curr = start;
        for (int symbol : input) {
            auto itr = transitions[curr].find(symbol);
            if (itr == transitions[curr].end()) return false;
            curr = itr->second[0];  // only need first index for dfa
        }
        return accepting.count(curr) > 0;
    }

    std::set<int> e_closure(std::set<int> input) {
        std::stack<int> myStack;
        for (int q : input) myStack.push(q);

        while (!myStack.empty()) {
            int q = myStack.top(); myStack.pop();
            auto itr = transitions[q].find(-1);
            if (itr == transitions[q].end()) continue;
            for (int r : itr->second) {
                if (input.insert(r).second)
                    myStack.push(r);
            }
        }
        return input;
    }

    bool run_nfa(std::vector<int>& input) {
        auto curr = e_closure({start});
        for (int sym : input) {
            std::set<int> next;
            for (int q : curr) {
                auto it = transitions[q].find(sym); 
                if (it != transitions[q].end())
                    for (int r : it->second)
                        next.insert(r);
            }
            curr = e_closure(next);
            if (curr.empty()) return false;
        }
        for (int q : curr)
            if (accepting.count(q)) return true;
        return false;
    }

    bool run(std::vector<int>& input) {
        if (nfa) return run_nfa(input);
        else return run_dfa(input);
    }

};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <dfa_file>" << std::endl;
        return 1;
    }
    FSM myFSM;
    myFSM.setup(argv[1]);
    // dfa.printdfa();
    std::string line;
    
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::vector<int> input;
        int symbol;
        while (ss >> symbol) input.push_back(symbol);

        if (myFSM.run(input))
            std::cout << "accepted" << std::endl;
        else
            std::cout << "rejected" << std::endl;
    }
}