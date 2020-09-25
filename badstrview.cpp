#include <map>
#include <string>
#include <unistd.h>
#if __cplusplus >= 201703L
#include <string_view>
using std::string_view;
#else
#include <cstring>
// AAARRGGHH! ... I can't persuade clang's scan-build to look in an
// include/ directory with <string_view> or
// <experimental/string_view>.  So I cobble together just enough
// string_view to illustrate the problem
struct string_view{
    const char *p;
    size_t s;
    string_view(const std::string& str){ p=str.data(); s=str.size(); }
    string_view(const char* ntcs) { p=ntcs; s=strlen(ntcs); }
    const char *data() const { return p; }
    size_t size() const { return s; } 
};
bool operator<(const string_view& lhs, const string_view& rhs){
    return strncmp(lhs.p, rhs.p, lhs.s) < 0;
}
#endif

using m_t = std::map<string_view, string_view>;

void func(m_t& m, const char* k, int i){
    m.emplace(k, std::to_string(i));  // BAD!!!  to_string(i) is a temporary!
}
    
int main(int argc, char **){
    m_t m;

    func(m, "foo", argc);
    string_view f = m.at("foo");
    write(0, f.data(), f.size());
    
    return 0;
}
