#include "Mylogger.h"
#include "stdlib.h"
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


namespace wd{
     Mylogger* Mylogger::m_logger=nullptr;//静态变量初始化
     Mylogger* Mylogger::getInstance(){  
         if(m_logger==nullptr){
             m_logger=new Mylogger;
             atexit(destory);
         }
         return m_logger;
     }
     void Mylogger::destory(){
         if(m_logger){
             delete m_logger;
             m_logger=nullptr;
         }
     }
     
     void Mylogger::error(const char *msg){
         m_root.error(msg);
     }
     void Mylogger::warn(const char *msg){
         m_root.warn(msg);
     }
     void Mylogger::info(const char *msg){
         m_root.info(msg);
     }
     void Mylogger::debug(const char *msg){
         m_root.debug(msg);
     }
     Mylogger::Mylogger()
     :m_root(log4cpp::Category::getRoot().getInstance("root"))
     {
         log4cpp::PatternLayout * ptn1=new log4cpp::PatternLayout();
         ptn1->setConversionPattern("%d [%p] %m%n");
         
         log4cpp::PatternLayout * ptn2=new log4cpp::PatternLayout();
         ptn2->setConversionPattern("%d [%p] %m%n");

         log4cpp::OstreamAppender *OstreamAppender = new log4cpp::OstreamAppender("OstreamAppender",&cout);
         OstreamAppender->setLayout(ptn1);
         
         log4cpp::FileAppender *fileAppender = new log4cpp::FileAppender("fileAppender","/home/fsq/study/c++/c-learning/spellCorrect/log/my.log");
         fileAppender->setLayout(ptn2);

         m_root.addAppender(OstreamAppender);
         m_root.addAppender(fileAppender);
         m_root.setPriority(log4cpp::Priority::DEBUG);
         
         cout<<"Mylogger()"<<endl;
     }
     Mylogger::~Mylogger(){
         
         log4cpp::Category::shutdown();
         cout<<"~Mylogger()"<<endl;
     }





}//end of wd
