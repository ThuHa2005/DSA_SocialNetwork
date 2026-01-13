#include "httplib.h"
#include "SocialNetwork.h"
using namespace httplib;

int main() {
    SocialNetwork sn;
    Server svr;

    svr.Post("/addUser", [&](const Request& req, Response& res) {
        sn.addUser(req.get_param_value("name"));
        res.set_content("OK", "text/plain");
    });

    svr.Post("/addFriend", [&](const Request& req, Response& res) {
        sn.addFriend(req.get_param_value("a"), req.get_param_value("b"));
        res.set_content("OK", "text/plain");
    });

    svr.Get("/suggest", [&](const Request& req, Response& res) {
        auto v = sn.suggest(req.get_param_value("name"));
        string out;
        for (auto &x : v) out += x + " ";
        res.set_content(out, "text/plain");
    });

    svr.Get("/graph", [&](const Request&, Response& res) {
        auto nodes = sn.getUsers();
        auto edges = sn.getEdges();
        string json = "{ \"nodes\": [";
        for (auto &n : nodes) json += "\"" + n + "\",";
        json.pop_back();
        json += "], \"edges\": [";
        for (auto &e : edges)
            json += "[\"" + e.first + "\",\"" + e.second + "\"],";
        if (!edges.empty()) json.pop_back();
        json += "] }";
        res.set_content(json, "application/json");
    });

    svr.listen("localhost", 8080);
}
