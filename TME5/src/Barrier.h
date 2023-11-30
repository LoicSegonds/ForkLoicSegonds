#pragma once

#include <cstdlib>
#include <mutex>
#include <condition_variable>

namespace pr{

  class Barrier{

    int counter;
    const int max;
    std::mutex m;
    std::condition_variable c;

  public:

    Barrier(int max):counter(0),max(max){}

    void done(){
      std::unique_lock<std::mutex> ul(m);
      ++counter;
      if(counter==max){
        c.notify_all();
      }
    }

    void wait_for(){
      std::unique_lock<std::mutex> ul(m);
      while(counter!=max){
        c.wait(ul);
      }
    }
  };
}
