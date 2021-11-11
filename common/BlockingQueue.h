#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_

#include <mutex>  // NOLINT [build/c++11]
#include <condition_variable>  // NOLINT [build/c++11]
#include <queue>

/// Implementation of a Blocking Queue.
/// \tparam T Content type of the Queue.
template <typename T> class BlockingQueue {
  std::mutex mutex;
  std::condition_variable condition;
  std::queue<T> queue;
  bool closed;

 public:
  /// Creates the Blocking Queue.
  BlockingQueue();

  /// Destroys the Blocking Queue.
  ~BlockingQueue();

  /// Adds an element to the Queue.
  /// \throws ClosedQueueException when the Queue is closed.
  /// \param e Reference to the element to add.
  void produce(T const &e);

  /// Returns and pops the top element from the Queue
  /// \throws ClosedQueueException when the Queue is closed and empty.
  /// \return Element
  T consume();

  /// Closes the Queue.
  void close();
};

/// Exception thrown when the Queue is already closed.
struct ClosedQueueException : public std::exception {
  const char *what() const noexcept override {
      return "The queue is already closed";
  }
};

/****************** IMPLEMENTATION ******************/
template<typename T>
BlockingQueue<T>::BlockingQueue()
    : mutex(), condition(), queue(), closed(false) {
}

template<typename T>
BlockingQueue<T>::~BlockingQueue() = default;

template<typename T>
void BlockingQueue<T>::produce(const T &e) {
    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->closed) {
        throw ClosedQueueException();
    }

    queue.push(e);
    this->condition.notify_all();
}

template<typename T>
T BlockingQueue<T>::consume() {
    std::unique_lock<std::mutex> lock(this->mutex);
    while (queue.empty()) {
        if (this->closed) {
            throw ClosedQueueException();
        }
        condition.wait(lock);
    }

    T v = queue.front();
    queue.pop();
    return v;
}

template<typename T>
void BlockingQueue<T>::close() {
    this->closed = true;
}

#endif  // BLOCKINGQUEUE_H_
