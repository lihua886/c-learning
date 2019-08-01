#include "WordQueryServer.h"




int main(){
    wd::WordQueryServer   wQServer("../../conf/myconf.conf");
    wQServer.start();
}
