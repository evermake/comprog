/*
https://leetcode.com/problems/parsing-a-boolean-expression

Runtime: 173ms (beats 5.21%)
Memory: 84.57MB (beats 5.12%)
*/

#include <string>
#include <vector>
using namespace std;

enum NodeType {
  True = 0,
  False,
  And,
  Or,
  Not
};

class AstNode {
private:
  NodeType type;
  std::vector<AstNode> children;
public:
  AstNode(NodeType type) {
    this->type = type;
  }

  void addChild(AstNode child) {
    this->children.push_back(child);
  }

  bool eval() {
    switch (this->type) {
      case NodeType::True: return true;
      case NodeType::False: return false;
      case NodeType::And: {
        for (auto n : this->children) {
          if (!(n.eval())) return false;
        }
        return true;
      }
      case NodeType::Or: {
        for (auto n : this->children) {
          if (n.eval()) return true;
        }
        return false;
      }
      case NodeType::Not:
        return !(this->children[0].eval());
    }
  }
};

class Solution {
public:
  bool parseBoolExpr(string expression) {
    // 1. Parse to AST
    vector<AstNode> stack;
    for (char c : expression) {
      switch (c) {
        case '(': continue;
        case ',':
        case ')': {
          auto ch = stack.back();
          stack.pop_back();
          stack[stack.size() - 1].addChild(ch);
          break;
        }
        case '&': {
          stack.push_back(AstNode(NodeType::And));
          break;
        }
        case '|': {
          stack.push_back(AstNode(NodeType::Or));
          break;
        }
        case '!': {
          stack.push_back(AstNode(NodeType::Not));
          break;
        }
        case 't': {
          stack.push_back(AstNode(NodeType::True));
          break;
        }
        case 'f': {
          stack.push_back(AstNode(NodeType::False));
          break;
        }
      }
    }

    // 2. Evaluate AST
    return stack.back().eval();
  }
};

