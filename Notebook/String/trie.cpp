#include <map>
#include <string>
#include <vector>

using namespace std;

struct trie {
	struct node {
		map<char, int> children;
		int leaf;	
		node() = default;
	};

	vector<node> nodes;

	trie() {
		nodes.push_back(node());
	}

	~trie() = default;

	void insert(string &s) {
		int cur = 0; // root
		for (char c : s) {
			if (!nodes[cur].children.count(c)) {
				nodes[cur].children[c] = nodes.size();
				nodes.push_back(node());
			}
			cur = nodes[cur].children[c];
		}
		if (!nodes[cur].children.count('$')) {
			nodes[cur].children['$'] = nodes.size();
			nodes.push_back(node());
		}
		++nodes[nodes[cur].children['$']].leaf;
	}

	bool contains(string &s) {
		int cur = 0;
		for (char c : s) {
			if (!nodes[cur].children.count(c)) return false;
			cur = nodes[cur].children[c];
		}
		return nodes[cur].children.count('$');
	}
};
