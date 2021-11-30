#ifndef SERVER_SRC_BLOCKINGQUEUE_H_
#define SERVER_SRC_BLOCKINGQUEUE_H_

#include <mutex>  // NOLINT [build/c++11]
#include <condition_variable>  // NOLINT [build/c++11]
#include <queue>

/// Implementation of a Blocking Queue.
/// \tparam T Content type of the Queue.
template <typename T>
class BlockingQueue {
  std::mutex mutex_;
  std::condition_variable condition_;
  std::queue<T> queue_;
  bool closed;

 public:
  /// Creates the Blocking Queue.
  BlockingQueue();

  /// Destroys the Blocking Queue.
  virtual ~BlockingQueue() = default;

  /// Adds an element to the Queue.
  /// \throws ClosedQueueException when the Queue is closed.
  /// \param e Reference to the element to add.
  void produce(T &&e);

  /// Returns the top element from the Queue
  /// \throws ClosedQueueException when the Queue is closed and empty.
  /// \return Element
  T top();

  /// Pops the top element from the Queue
  /// \throws ClosedQueueException when the Queue is closed and empty.
  /// \return Element
  void pop();

  /// Closes the Queue.
  void close();

    T popIfNotEmpty();
};

/// Exception thrown when the Queue is already closed.
struct ClosedQueueException : public std::exception {
  const char *what() const noexcept override {
      return "The queue_ is already closed";
  }
};

/****************** IMPLEMENTATION ******************/
template<typename T>
BlockingQueue<T>::BlockingQueue()
    : mutex_(), condition_(), queue_(), closed(false) {
}

template<typename T>
void BlockingQueue<T>::produce(T &&e) {
    std::unique_lock<std::mutex> lock(mutex_);
    if (closed) {
        throw ClosedQueueException();
    }

    queue_.push(std::move(e));
    condition_.notify_all();
}

template<typename T>
T BlockingQueue<T>::popIfNotEmpty() {
    if (queue_.empty() || closed) {
        return nullptr;
    }
    std::unique_lock<std::mutex> lock(mutex_);
    T top = queue_.front();
    queue_.pop();
    return top;
}

template<typename T>
T BlockingQueue<T>::top() {
    std::unique_lock<std::mutex> lock(mutex_);
    while (queue_.empty()) {
        if (closed) {
            throw ClosedQueueException();
        }
        condition_.wait(lock);
    }

    return queue_.front();
}

template<typename T>
void BlockingQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    if (closed && queue_.empty()) {
        throw ClosedQueueException();
    }

    queue_.pop();
}

template<typename T>
void BlockingQueue<T>::close() {
    closed = true;
    condition_.notify_all();
}

#endif  // SERVER_SRC_BLOCKINGQUEUE_H_
