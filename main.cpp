#include <bits/stdc++.h>

using namespace std;

struct Node {
    map<char, Node*> childs;
    bool is_terminal = false;
    long long term_in_sub_tree = 0;

    Node() = default;
};

struct Trie {
    Node* root = new Node();

    Trie() = default;

    void add_string(string& s) {
        if (root == nullptr)
            root = new Node();
        Node* cur = root;
        for (auto u : s) {
            cur->term_in_sub_tree++;
            if (cur->childs[u] == nullptr)
                cur->childs[u] = new Node();
            cur = cur->childs[u];
        }
        cur->is_terminal = true;
    }
    bool find(string& s) {
        Node* cur = root;
        for (auto u : s) {
            if (cur == nullptr)
                return false;
            cur = cur->childs[u];
        }
        if (cur == nullptr)
            return false;
        return cur->is_terminal;
    }

   private:
    void func(Node* cur, vector<string>& ans, string& pref) {
        if (cur == nullptr)
            return;
        if (cur->is_terminal)
            ans.push_back(pref);
        for (auto i : cur->childs) {
            char c = i.first;
            Node* next = i.second;
            if (next == nullptr)
                continue;
            if (next->term_in_sub_tree + next->is_terminal == 0)
                continue;
            pref += c;
            func(next, ans, pref);
            pref.pop_back();
        }
    }

   public:
    vector<string> all_with_this_pref(string& s) {
        Node* cur = root;
        if (root == nullptr)
            return {};
        string pref = "";
        for (auto u : s) {
            cur = cur->childs[u];
            pref += u;
            if (cur == nullptr)
                return {};
        }
        vector<string> ans;
        func(cur, ans, pref);
        return ans;
    }
    long long count(string& s) {
        Node* cur = root;
        if (root == nullptr)
            return 0;
        for (auto u : s) {
            cur = cur->childs[u];
            if (cur == nullptr)
                return 0;
        }
        return cur->term_in_sub_tree + cur->is_terminal;
    }
};

int main() {
    ifstream istr;
    istr.open("words.txt");
    string s;
    Trie t;
    while (istr >> s) {
        t.add_string(s);
    }
    cout << "Type any string and press enter. You will get all common words "
            "starting with the string you entered"
         << endl;
    while (cin >> s) {
        long long c = t.count(s);
        if (c == 0) {
            cout << "No words with entered prefix" << endl;
        } else if (c < 20) {
            auto ans = t.all_with_this_pref(s);
            for (int i = 0; i < c; i++) {
                cout << ans[i];
                i++;
                if (i >= c) {
                    cout << endl;
                    continue;
                }
                for (int j = 0; j < 20 - (int)ans[i - 1].size(); j++)
                    cout << ' ';
                cout << ans[i] << endl;
            }
        } else {
            cout << c << " possibilities, show?[Y/n]" << endl;
            char sh;
            cin >> sh;
            sh = tolower(sh);
            if (sh == 'n') {
                continue;
            } else {
                auto ans = t.all_with_this_pref(s);
                for (int i = 0; i < c; i++) {
                    cout << ans[i];
                    i++;
                    if (i >= c) {
                        cout << endl;
                        continue;
                    }
                    for (int j = 0; j < 20 - (int)ans[i - 1].size(); j++)
                        cout << ' ';
                    cout << ans[i] << endl;
                }
            }
        }
    }
    return 0;
}
