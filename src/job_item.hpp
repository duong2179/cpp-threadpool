#ifndef JOB_ITEM_HPP
#define JOB_ITEM_HPP

#include <memory>

class JobItem {
 public:
  virtual ~JobItem() {}
  virtual bool execute() = 0;
};

typedef std::shared_ptr<JobItem> JobItemPtr;

class NullJob : public JobItem {
 public:
  NullJob() {}
  ~NullJob() {}

  bool execute() { return false; }
};

#endif