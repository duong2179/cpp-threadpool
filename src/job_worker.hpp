#ifndef JOB_WORKER_HPP
#define JOB_WORKER_HPP

#include <cstdint>
#include <memory>
#include "job_item.hpp"
#include "job_queue.hpp"

class JobWorker {
 private:
  std::shared_ptr<JobQueue<JobItemPtr>> job_queue_;
  uint32_t worker_id_;

 public:
  JobWorker(std::shared_ptr<JobQueue<JobItemPtr>> shared_queue,
            uint32_t worker_id)
      : job_queue_(shared_queue), worker_id_(worker_id){};
  ~JobWorker(){};

  void run() {
    bool next_job = true;
    while (next_job) {
      JobItemPtr job = job_queue_->pick();
      next_job = job->execute();
    }
  }

  uint32_t worker_id() { return worker_id_; }
};

#endif