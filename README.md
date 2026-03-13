*This project has been created as part of the 42 curriculum by <bclairot>.*

# Codexion

## Description
Race against time in this thrilling concurrency challenge! Codexion simulates a
shared coworking space where multiple coders compete for a limited number of
USB dongles in order to compile their quantum code. Using POSIX threads,
mutexes, condition variables and a custom scheduler (FIFO or EDF), you must
coordinate resource access, avoid deadlocks, and detect "burnout" when a coder
waits too long without compiling. This project develops skills in thread 
synchronization, real‑time logging, and fair arbitration.

## Instructions
1. **Compilation**
   - Run `make` (the provided Makefile defines `all`, `clean`, `fclean`, `re`, and a `bonus` rule).

2. **Execution**
   - Usage:
     ```
     ./codexion number_of_coders time_to_burnout time_to_compile \
                 time_to_debug time_to_refactor number_of_compiles_required \
                 dongle_cooldown scheduler
     ```
   - All arguments are mandatory integers (positive) except `scheduler` which
     must be exactly `fifo` or `edf`.
   - Example:
     ```
     ./codexion 5 800 200 100 150 3 50 fifo
     ```

## Resources
* POSIX threads documentation (`pthread_create`, `pthread_mutex_*`,
  `pthread_cond_*`).
* 42 subject description and sample logs (provided in assignment text).
* Articles on dining philosophers / resource synchronization problems.
* AI was used to draft this README; all content was reviewed and refined manually. No AI-generated code
  is included in the project without understanding.

## Blocking cases handled
* **Deadlock prevention:** the scheduler and cooldown mechanism ensure that
  coders do not hold one dongle indefinitely waiting for the other. Mutual
  exclusion is handled with mutexes and a priority queue when requesting
dongles.
* **Cooldown handling:** when a coder releases a dongle, it is marked unavailable
  until the cooldown interval elapses, preventing immediate reacquisition.
* **Precise burnout detection:** a dedicated monitor thread checks each coder's
  last compile start time and logs a "burned out" message within 10 ms of the
  deadline.

## Thread synchronization mechanisms
* `pthread_mutex_t` protects the state of each dongle (available, owner, cooldown
  expiry) and the global log. Access to shared structures is always performed
  while holding the corresponding mutex.
* `pthread_cond_t` is used per dongle to allow waiting coders to sleep until the
  dongle becomes available according to the FIFO/EDF scheduler. Condition waits
  are performed with the dongle mutex held and rechecked upon wakeup to avoid
  spurious notifications.
<!-- * A custom priority queue (heap) stores waiting coder requests; the head of the
  queue is chosen according to the scheduler policy. This avoids race conditions
  between multiple threads requesting the same resource. -->
<!-- * The monitor thread communicates burnout events by setting a shared flag while
  holding a mutex; worker threads periodically check this flag before attempting
  to start a new phase, guaranteeing an orderly shutdown. -->
* Example race prevention: when two coders simultaneously try to take the same
  dongle, the first to lock the mutex inserts its request into the queue. The
  second thread blocks on the condition variable. Upon release, the mutex grants
  the dongle to the next request in the queue only, eliminating conflicting
  acquisitions.

Additional sections (usage examples, technical choices) are included above.

---

<!-- For more information, consult the project subject provided by the 42 staff or
review the source files in the `coders/` directory. -->

$ make && clear && ./codexion 4 500 200 100 150 5 0 fifo