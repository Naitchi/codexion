*This project has been created as part of the 42 curriculum by bclairot.*

# Codexion

## Description

Codexion is a multithreaded simulation project inspired by shared-resource
scheduling problems. Multiple coder threads compete for dongles, and each coder
must acquire two dongles before entering its work cycle:

- compiling
- debugging
- refactoring

The goal is to coordinate thread execution safely while handling real-world
concurrency risks: deadlocks, starvation pressure, cooldown constraints,
burnout detection, and race-free logging.

## Instructions

### Compilation

From the repository root:

```bash
make
```

Available targets:

- `all`
- `clean`
- `fclean`
- `re`

### Execution

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Arguments:

1. `number_of_coders`: number of coder threads (must be > 0)
2. `time_to_burnout`: max time without successful compile (ms)
3. `time_to_compile`: compile duration (ms)
4. `time_to_debug`: debug duration (ms)
5. `time_to_refactor`: refactor duration (ms)
6. `number_of_compiles_required`: required compile count per coder
7. `dongle_cooldown`: cooldown after dongle release (ms)
8. `scheduler`: `fifo` or `edf`

Validation rules implemented by parsing:

- Exactly 8 runtime arguments are required.
- All arguments except `scheduler` must be positive integers within `int` range.
- `scheduler` must be exactly `fifo` or `edf`.

Example:

```bash
./codexion 4 500 200 100 150 5 0 fifo
```

## Resources

Classic references:

- POSIX threads man pages (`pthread_create`, `pthread_join`, `pthread_mutex_*`)
- Dining Philosophers and resource-allocation literature
- Deadlock theory (Coffman conditions)
- EDF scheduling fundamentals

How AI was used in this project:

- AI was used for documentation drafting and wording improvements (README edits).
- AI assistance was used to help reorganize files and headers.
- Concurrency logic, thread behavior, and synchronization choices were reviewed
  and validated against the codebase before final integration.

## Blocking cases handled

This implementation addresses the following concurrency-related blocking cases:

- **Deadlock prevention (Coffman pressure reduction):**
  Dongle locking order is normalized through ordered index handling (lower/higher
  index strategy), reducing circular-wait risk when coders acquire two dongles.
- **Mutual exclusion on shared dongles:**
  Each dongle is protected by its own `pthread_mutex_t`, preventing concurrent
  conflicting ownership.
- **Starvation mitigation with scheduler policy:**
  `edf` mode compares elapsed waiting time and can delay less urgent coders,
  improving fairness under contention. `fifo` mode skips EDF checks.
- **Cooldown handling:**
  Released dongles are marked unavailable until `available_time` reaches
  current time, preventing immediate re-acquisition races.
- **Burnout detection:**
  A dedicated monitoring thread continuously checks coder elapsed time against
  `time_to_burnout` and sets a global stop flag when burnout occurs.
- **Log serialization:**
  All status prints are protected by `print_mutex`, preventing interleaved and
  corrupted output lines.
- **Orderly stop propagation:**
  Shared `stop` state is mutex-protected and read by worker threads so that all
  threads can terminate consistently after a stopping event.

## Thread synchronization mechanisms

### Primitives used in this implementation

- `pthread_mutex_t` (actively used):
  - one mutex per dongle (`mutex_dongle`)
  - one mutex for serialized logging (`print_mutex`)
  - one mutex for global stop state (`stop_mutex`)
  - one mutex per coder counter/timestamp
- `pthread_cond_t`:
  Not used in the current implementation.
- Custom event implementation:
  A lightweight event model is implemented via mutex-protected shared state
  (`stop` flag + monitor polling), instead of condition variables.

### How synchronization coordinates shared resources

- **Dongles:**
  Threads lock the two required dongle mutexes before checking availability,
  cooldown, and scheduler acceptance. This ensures atomic eligibility checks and
  acquisition.
- **Logging:**
  `print_mutex` wraps every output line related to thread actions or burnout,
  guaranteeing readable and race-free logs.
- **Monitor communication:**
  The monitor thread writes the stop event through `set_stop`, and worker
  threads read it through `get_stop`, both mutex-protected.

### Race-condition prevention examples

- Two coders cannot mark the same dongle as acquired simultaneously because the
  dongle state is read and written while holding the dongle mutex.
- Compilation counters (`number_of_compiles_done`) are incremented and read via
  mutex-protected accessor helpers, preventing torn or lost updates.
- Burnout signal and action output cannot race into inconsistent logs because
  stop-state updates and print operations are serialized by dedicated mutexes.
