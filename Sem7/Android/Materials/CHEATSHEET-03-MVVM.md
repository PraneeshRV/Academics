# MVVM

## The idea

Instead of putting everything in one file, split the app into three parts:

| Part | Job | In our counter |
|---|---|---|
| **Model** | stores data | `CounterState` data class |
| **View** | displays the UI | `CounterScreen` composable |
| **ViewModel** | manages data and logic | `CounterViewModel` class |

**The rule:** the View displays information and reports user actions. The ViewModel manages
the data and the logic. The View never changes the value itself.

---

## Setup — do this first

`gradle/libs.versions.toml`, under `[libraries]`:

```toml
androidx-lifecycle-viewmodel-compose = { group = "androidx.lifecycle", name = "lifecycle-viewmodel-compose", version.ref = "lifecycleRuntimeKtx" }
```

`app/build.gradle.kts`, under `dependencies`:

```kotlin
implementation(libs.androidx.lifecycle.viewmodel.compose)
```

Then **Sync Now**. Without this, `viewModel()` will not resolve.

Four files to create:

```
MainActivity.kt        (already exists)
CounterState.kt        the Model
CounterViewModel.kt    the ViewModel
CounterScreen.kt       the View
```

---

## Step 1 — The Model

`CounterState.kt`

```kotlin
package com.learning.countermvvm3

data class CounterState(
    val count: Int = 0
)
```

### Why a data class

A data class groups related values. The default `= 0` means `CounterState()` gives you
`count = 0` with no arguments.

Later you can add more without disturbing anything:

```kotlin
data class CounterState(
    val count: Int = 0,
    val message: String = "Start counting"
)
```

### copy() — the important part

Kotlin gives every data class a `copy()` that makes a **new** object with some values
changed:

```kotlin
val oldState = CounterState(count = 5)
val newState = oldState.copy(count = 6)
// oldState.count is still 5
// newState.count is 6
```

The ViewModel uses `copy()` to produce a new state rather than mutating the old one.
Compose compares old against new to decide what to redraw, so replacing the object is
what makes the UI update.

---

## Step 2 — The ViewModel

`CounterViewModel.kt`

```kotlin
package com.learning.countermvvm3

import androidx.compose.runtime.State
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel

class CounterViewModel : ViewModel() {

    private val _counterState = mutableStateOf(CounterState())

    val counterState: State<CounterState> = _counterState

    fun increment() {
        _counterState.value = _counterState.value.copy(
            count = _counterState.value.count + 1
        )
    }

    fun decrement() {
        if (_counterState.value.count > 0) {
            _counterState.value = _counterState.value.copy(
                count = _counterState.value.count - 1
            )
        }
    }

    fun reset() {
        _counterState.value = CounterState()
    }
}
```

### The backing-field pattern — explain this if asked

```kotlin
private val _counterState = mutableStateOf(CounterState())  // mutable, private
val counterState: State<CounterState> = _counterState       // read-only, public
```

- `_counterState` is a `MutableState`. Only the ViewModel can write to it.
- `counterState` is the same object exposed as a plain `State`, which has no setter.
- The View can **read** but cannot **write**. That is the entire point of the pattern.

The leading underscore is a naming convention for the private backing property.

### The three functions

- `increment()` — reads the current count, adds one, stores a new state via `copy()`.
  If the count is 4, it computes 4 + 1 = 5 and the new state is `count = 5`.
- `decrement()` — the same, minus one, guarded by `if (count > 0)` so it never goes
  negative. At 0, pressing Decrease leaves it at 0.
- `reset()` — assigns a fresh `CounterState()`, whose default is `count = 0`.

---

## Step 3 — The View

`CounterScreen.kt`

```kotlin
@Composable
fun CounterScreen(
    modifier: Modifier = Modifier,
    contentPadding: PaddingValues = PaddingValues(0.dp),
    counterViewModel: CounterViewModel = viewModel()
) {
    val state by counterViewModel.counterState

    Column(
        modifier = modifier
            .padding(contentPadding)
            .padding(24.dp),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(text = "MVVM Counter", fontSize = 28.sp)

        Spacer(modifier = Modifier.height(30.dp))

        Text(text = state.count.toString(), fontSize = 60.sp)

        Spacer(modifier = Modifier.height(30.dp))

        Row(horizontalArrangement = Arrangement.spacedBy(16.dp)) {
            Button(onClick = { counterViewModel.decrement() }) { Text("Decrease") }
            Button(onClick = { counterViewModel.increment() }) { Text("Increase") }
        }

        Spacer(modifier = Modifier.height(16.dp))

        Button(onClick = { counterViewModel.reset() }) { Text("Reset") }
    }
}
```

### Getting the ViewModel — the rule

```kotlin
counterViewModel: CounterViewModel = viewModel()   // CORRECT
```

**Never do this:**

```kotlin
val counterViewModel = CounterViewModel()          // WRONG
```

`viewModel()` creates the ViewModel the first time and **retrieves the same instance**
afterwards, tying it to the lifecycle owner. Constructing it by hand makes a brand-new
object on every recomposition, so the value would reset constantly and would not survive
rotation.

### Reading the state

```kotlin
val state by counterViewModel.counterState
```

The `by` delegate unwraps the `State<CounterState>` so you write `state.count` rather than
`state.value.count`. It needs:

```kotlin
import androidx.compose.runtime.getValue
```

Missing that import is the most common error in this whole topic.

Then:

```kotlin
Text(text = state.count.toString())
```

When the count changes, Compose recomposes this `Text` automatically.

### Buttons ask, they do not act

```kotlin
// AVOID — logic in the View
Button(onClick = { count++ })

// PREFER — the View asks the ViewModel
Button(onClick = { counterViewModel.increment() })
```

---

## Step 4 — MainActivity

```kotlin
class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            CounterMVVM3Theme {                 // use YOUR generated theme name
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    CounterScreen(
                        modifier = Modifier.fillMaxSize(),
                        contentPadding = innerPadding
                    )
                }
            }
        }
    }
}
```

---

## Why MVVM — the answer to "why bother"

- **Separation of code** — UI and logic sit in different classes.
- **Easier maintenance** — you can redesign the screen without touching the counter logic.
- **Easier testing** — ViewModel functions can be tested on their own, with no UI.
- **Better organisation** — each file has one job.
- **State survives rotation** — a ViewModel outlives configuration changes.

That last one is the one to demonstrate. Verified on the emulator: a count of 5 with the
message "Counter is active" stayed at 5 after rotating to landscape. A plain `remember`
would have reset to 0, because rotation destroys and recreates the Activity while the
ViewModel is deliberately kept alive.

---

## The demonstration the manual asks for

1. Run the app.
2. Click **Increase** three times → shows `3`.
3. Click **Decrease** once → shows `2`.
4. Click **Reset** → shows `0`.
5. Click **Decrease** at zero → stays `0`, does not go negative.
6. Increase the value, then rotate the emulator → the count is retained.

---

## Student exercises — likely to be asked

### Task 1 — Add 2

```kotlin
fun addTwo() {
    _counterState.value = _counterState.value.copy(
        count = _counterState.value.count + 2
    )
}
```

```kotlin
Button(onClick = { counterViewModel.addTwo() }) { Text("Add 2") }
```

### Task 2 — Subtract 2, never negative

```kotlin
fun subtractTwo() {
    val next = _counterState.value.count - 2
    _counterState.value = _counterState.value.copy(
        count = if (next < 0) 0 else next
    )
}
```

Note the guard: a plain `if (count > 0)` is not enough here, because from `count = 1`
subtracting 2 would give `-1`. Clamp the result instead.

### Task 3 — Add a message

```kotlin
data class CounterState(
    val count: Int = 0,
    val message: String = "Counter is zero"
)
```

```kotlin
private fun setCount(newCount: Int) {
    _counterState.value = _counterState.value.copy(
        count = newCount,
        message = if (newCount == 0) "Counter is zero" else "Counter is active"
    )
}
```

Then have `increment`, `decrement`, `addTwo` and `subtractTwo` all call `setCount(...)`,
so the message rule lives in exactly one place.

Display it:

```kotlin
Text(text = state.message, fontSize = 16.sp)
```

---

## Likely exam questions

**"What does MVVM stand for and what does each part do?"** — Model stores data, View
displays the UI, ViewModel manages data and logic.

**"Why `viewModel()` and not `CounterViewModel()`?"** — `viewModel()` returns the same
instance tied to the lifecycle owner, so state survives recomposition and rotation.
Constructing it directly makes a new object every time.

**"What does `copy()` do and why use it?"** — creates a new object with some fields
changed, leaving the original untouched. Compose detects the new object and recomposes.

**"Why is `counterState` typed `State` and not `MutableState`?"** — so the View can read
but not write. All mutation goes through ViewModel functions.

**"How does the counter survive rotation?"** — the ViewModel is scoped to the lifecycle
owner and is deliberately not destroyed by a configuration change, unlike the Activity.

**"Why not put `count++` in the button?"** — it puts logic in the View, breaking the
separation, and it cannot be tested without the UI.
