//
// Created by benny on 2022/3/17.
//
#include "task.h"

#include "executor.h"
#include "io_utils.h"

Task<int, AsyncExecutor> simple_task2() {
  debug("task 2 start ...");
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1s);
  debug("task 2 returns after 1s.");
  co_return 2;
}

Task<int, NewThreadExecutor> simple_task3() {
  debug("in task 3 start ...");
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2s);
  debug("task 3 returns after 2s.");
  co_return 3;
}

Task<int, LooperExecutor> simple_task() {
  debug("task start ...");
  auto result2 = co_await simple_task2();
  debug("returns from task2: ", result2);
  auto result3 = co_await simple_task3();
  debug("returns from task3: ", result3);
  co_return 1 + result2 + result3;
}

void test_tasks() {
  auto simpleTask = simple_task();
  simpleTask.then([](int i) { debug("simple task end: ", i); }).catching([](std::exception &e) { debug("error occurred", e.what()); });
  try {
    auto i = simpleTask.get_result();
    debug("simple task end from get: ", i);
  } catch (std::exception &e) {
    debug("error: ", e.what());
  }
}

int main() {
  test_tasks();

  auto looper = LooperExecutor();

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1s);
  looper.shutdown(false);
  std::this_thread::sleep_for(1s);

  return 0;
}