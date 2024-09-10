#include <iostream>
#include "DataStream.hpp"
#include "CustomType.hpp"

int main()
{
    HW::SERIALIZE::DataStream dStream;
    int32_t a= 0x12345678;
    dStream << a;
    int32_t b;
    dStream >> b ; 
    std::cout <<std::hex<<b<<std::endl;



    // std::string str = "hello world!";
    // dStream << str;
    // std::string rstr;
    // dStream >> rstr;
    // std::cout<<rstr<<std::endl;

    // std::list<std::string> val{"abc"};
    // dStream << val;
    // std::list<std::string> out;
    // dStream.read(out); 
    // for (auto v:out)
    // {
    //    std::cout<<v<<" ";
    // }
    // std::cout<<std::endl;

    // std::map<int32_t,std::string> mp;
    // mp[1]="abc";
    // mp[2]="def";
    // mp[3]="hij";
    // dStream.write(mp);
    // std::map<int32_t,std::string> out;
    // dStream.read(out);
    // for(const auto& v:out)
    // {
    //     std::cout<<v.first<<","<<v.second<<std::endl;
    // }

    // std::set<std::string> set{"张三","李四","王五"};
    // dStream << set;
    // std::set<std::string> out;
    // dStream >> out;
    // for (const auto& v:out)
    // {
    //     std::cout<<v<<std::endl;
    // }
    // A a(1,"张三",'w');
    // dStream << a;
    // A b;
    // dStream >> b;
    // b.show();
    return 0;
}

