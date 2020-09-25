#include <sstream>
#include <cstdio>

int main(int, char **){
    std::ostringstream oss;
    oss << "hello world\n";
    const char *p = oss.str().c_str();
    printf("%s", p);
    return 0;
}
