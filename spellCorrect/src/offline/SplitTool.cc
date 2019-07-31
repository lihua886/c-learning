#include "SplitTool.h"



namespace wd{



vector<string>  SplitTool::cut(const string & str){
  vector<string> words;
  jieba.Cut(str,words,true);
  return words;  
}




}// end of wd








