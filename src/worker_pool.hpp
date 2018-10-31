#ifndef WORKER_POOL_HPP
#define WORKER_POOL_HPP

#include <cstdint>
#include <memory>
#include <thread>
#include "job_item.hpp"
#include "job_queue.hpp"
#include "job_worker.hpp"

using namespace std;

class WorkerPool {
 private:
  uint32_t num_threads_;
  std::shared_ptr<JobQueue<JobItemPtr>> job_queue_;
  std::vector<std::shared_ptr<std::thread>> thread_pool_;

 public:
  WorkerPool(uint32_t num_threads)
      : num_threads_(num_threads), job_queue_(new JobQueue<JobItemPtr>()) {}
  ~WorkerPool() {}

  void start();
  void join();
  void queue_job(JobItemPtr job);
  bool is_empty();
  uint32_t count_jobs();
  void stop_plz();
};

#endif