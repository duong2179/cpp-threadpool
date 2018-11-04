#include "worker_pool.hpp"
#include <functional>

void WorkerPool::start() {
  for (size_t i = 0; i < num_threads_; i++) {
    std::shared_ptr<JobWorker> worker(new JobWorker(job_queue_, i + 1));
    std::shared_ptr<std::thread> t(
        new std::thread(std::bind(&JobWorker::run, worker)));
    thread_pool_.push_back(t);
  }
}

void WorkerPool::join() {
  for (auto& t : thread_pool_) {
    t->join();
  }
}

void WorkerPool::queue_job(JobItemPtr job) {
  job_queue_->push(job);
}

bool WorkerPool::is_empty() {
  return job_queue_->is_empty();
}

size_t WorkerPool::count_jobs() {
  return job_queue_->count();
}

void WorkerPool::stop_plz() {
  // clear all queued jobs
  job_queue_->clear();
  // enqueue NullJob to stop threads
  for (size_t i = 0; i < num_threads_; i++) {
    JobItemPtr job(new NullJob());
    queue_job(job);
  }
}
