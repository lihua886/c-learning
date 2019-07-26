#include <memory>
#include <string>

using std::unique_ptr;
using std::string;
using std::wstring;

namespace  wd{
wstring s2Ws(const string& str);
//wstring -> string
string ws2S(const wstring& wstr);


}//end of wd
