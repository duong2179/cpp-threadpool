#ifndef JOB_QUEUE_HPP
#define JOB_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

typedef std::unique_lock<std::mutex> std_mtx_unq_lck;

template <typename T>
class JobQueue {
 private:
  mutable std::mutex mutex_;
  std::condition_variable cond_var_;
  std::queue<T> queue_;

 public:
  JobQueue(void){};
  ~JobQueue(void){};

  T peek() {
    std_mtx_unq_lck lock(mutex_);
    while (queue_.empty()) {
      cond_var_.wait(lock);
    }
    T item = queue_.front();
    return item;
  }

  T pick() {
    std_mtx_unq_lck lock(mutex_);
    while (queue_.empty()) {
      cond_var_.wait(lock);
    }
    T item = queue_.front();
    queue_.pop();
    return item;
  }

  void push(const T& item) {
    {
      std_mtx_unq_lck lock(mutex_);
      queue_.push(item);
    }
    cond_var_.notify_one();
  }

  void push(T& item) {
    {
      std_mtx_unq_lck lock(mutex_);
      queue_.push(item);
    }
    cond_var_.notify_one();
  }

  bool is_empty() {
    std_mtx_unq_lck lock(mutex_);
    return queue_.empty();
  }

  void clear() {
    std_mtx_unq_lck lock(mutex_);
    std::queue<T> empty_queue;
    std::swap(queue_, empty_queue);
  }

  size_t count() {
    std_mtx_unq_lck lock(mutex_);
    return size_t(queue_.size());
  }
};

#endif