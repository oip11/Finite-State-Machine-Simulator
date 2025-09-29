# Finite-State-Machine-Simulator
Similates an FSM in C++ that runs both Determinstic Finite Automata (DFA) and Nondeterministic Finite Automata (NFA). Allows for user-defined states, transitions, accepting states, and input strings.

# Features
* Support for DFA and NFA automata
* Handles NFA epsilon transitions using epsilon closure
* Efficiently stores transitions using maps
* Simple input interface for testing automata

# Input File Format
Describe the FSM in a text file with the following structure:    
\<mode\> - either "deterministic" or "nondeterminstic"  
states \<N\> - N is the number of states  
inputs \<M\> - M is the number of inputs  
start \<S\> - start state S (0 to N-1)  
accepting \<a1\> \<a2\> ... \<ak\> - list accepting states space seperated after "accepting"  
transitions - header line that begins transitions list. Each transition is on its own line as three integers  
from_state to_state symbol - "from_state" and "to_state" are integers 0 to N-1. Symbol is an integer input sysmbol 0 to M-1, or -1 to denote an epsilon transition  

# Example Input File  
ondeterministic  
states 5  
inputs 2  
start 0  
accepting 1 3  
transitions  
0 1 -1  
0 3 -1  
1 1 1  
3 3 0  
1 2 0  
3 4 1  
4 3 1  
4 4 0  
2 1 0  
2 2 1  

# Supplying Test Input Strings (Stdin)  
Once program loads the input file, it will read input string fromm stdin, one per line. Each line is a sequence of space seperated integers from 0 to M-1. Output will then be accepted or rejected per input line
