#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct User {
    int id;
    string name;
};

class SocialNetwork {
private:
    vector<User> users;
    vector< set<int> > adj;
    map<string, int> nameToID;

public:
    void addUser(const string& name) {
        if (nameToID.count(name)) return;
        int id = users.size() + 1;
        users.push_back({id, name});
        adj.push_back(set<int>());
        nameToID[name] = id;
    }

    void addFriend(const string& a, const string& b) {
        if (!nameToID.count(a) || !nameToID.count(b) || a == b) return;
        int u = nameToID[a] - 1;
        int v = nameToID[b] - 1;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    void removeFriend(const string& a, const string& b) {
        if (!nameToID.count(a) || !nameToID.count(b)) return;
        int u = nameToID[a] - 1;
        int v = nameToID[b] - 1;
        adj[u].erase(v);
        adj[v].erase(u);
    }

    void renameUser(const string& oldName, const string& newName) {
        if (!nameToID.count(oldName) || nameToID.count(newName)) return;
        int id = nameToID[oldName];
        int idx = id - 1;
        nameToID.erase(oldName);
        users[idx].name = newName;
        nameToID[newName] = id;
    }

    vector<string> suggest(const string& name) {
        vector<string> res;
        if (!nameToID.count(name)) return res;
        int u = nameToID[name] - 1;
        set<int> sug;

        for (int f : adj[u])
            for (int ff : adj[f])
                if (ff != u && !adj[u].count(ff))
                    sug.insert(ff);

        for (int x : sug) res.push_back(users[x].name);
        return res;
    }

    vector<pair<string,string>> getEdges() {
        vector<pair<string,string>> edges;
        for (int i = 0; i < adj.size(); i++)
            for (int v : adj[i])
                if (i < v)
                    edges.push_back({users[i].name, users[v].name});
        return edges;
    }

    vector<string> getUsers() {
        vector<string> res;
        for (auto &u : users) res.push_back(u.name);
        return res;
    }
};

#endif
