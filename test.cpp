#include <chrono>
#include <iostream>
#include "job_item.hpp"
#include "worker_pool.hpp"

class SayJob : public JobItem {
 private:
  std::string text_;

 public:
  SayJob(const std::string& text) : text_(text) {}
  ~SayJob() {}

  bool execute() {
    std::cout << text_ << std::endl;
    return true;
  }
};

class AddJob : public JobItem {
 private:
  int a_, b_;

 public:
  AddJob(int a, int b) : a_(a), b_(b) {}
  ~AddJob() {}

  bool execute() {
    std::cout << "" << a_ << " + " << b_ << " = " << (a_ + b_) << std::endl;
    return true;
  }
};

int main() {
  WorkerPool pool(4);
  pool.start();

  JobItemPtr job_1(new AddJob(1, 2));
  JobItemPtr job_2(new AddJob(2, 3));
  JobItemPtr job_3(new SayJob("Hello Cpp-ThreadPool #1"));
  JobItemPtr job_4(new SayJob("Hello Cpp-ThreadPool #2"));

  pool.queue_job(job_1);
  pool.queue_job(job_2);
  pool.queue_job(job_3);
  pool.queue_job(job_4);

  int counter = 3;
  while (counter > 0) {
    std::cout << "Terminating in " << counter << " seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    --counter;
  }

  pool.stop_plz();
  pool.join();

  return 0;
}
