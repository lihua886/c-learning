#include "WordSegmentation.h"



namespace wd{



vector<string>  WordSegmentation::cut(const string & str){
  vector<string> words;
  jieba.Cut(str,words,true);
  return words;  
}






}// end of wd








