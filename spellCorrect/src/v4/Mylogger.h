#pragma once


#include <log4cpp/Category.hh>

namespace wd{

class Mylogger
{
public:
    static Mylogger* getInstance();
    static void destory();
    void error(const char *);
    template<class...Args>
        void error(Args... args){
            m_root.error(args...);
        }
    void warn(const char *);
    template<class...Args>
        void warn(Args... args){
            m_root.warn(args...);
        }
    void info(const char *);
    template<class...Args>
        void info(Args... args){
            m_root.info(args...);
        }
    void debug(const char *);
    template<class...Args>
        void debug(Args... args){
            m_root.debug(args...);
        }

private:
    Mylogger();
    ~Mylogger();

private:
   static Mylogger* m_logger;
   log4cpp::Category & m_root;

};

}
#define prefix(msg) string("[").append(__FILE__)\
    .append(":").append(__FUNCTION__)\
    .append(":").append(std::to_string(__LINE__))\
    .append("]").append(msg).c_str()

#define LogError(msg,...) wd::Mylogger::getInstance()->error(prefix(msg),##__VA_ARGS__)
#define LogWarn(msg,...) wd::Mylogger::getInstance()->warn(prefix(msg),##__VA_ARGS__)
#define LogInfo(msg,...) wd::Mylogger::getInstance()->info(prefix(msg),##__VA_ARGS__)
#define LogDebug(msg,...) wd::Mylogger::getInstance()->debug(prefix(msg),##__VA_ARGS__)



