# Android Lab Viva — Question Bank

Built from the five manuals in this folder (Activities and their Lifecycle, Android
Application Notes 1, UI Controls 2/3/4, MVVM) plus the five cheatsheets, and aimed at the
app actually built in the exam: **Set 2 — Personal Study Session Tracker**.

Section A is the one to read first: those are the questions asked while looking at your
own screen.

## Syllabus coverage

| Syllabus item | Sections | Questions |
|---|---|---|
| Activities and their Lifecycle | D | 39–52 |
| Android Application Notes 1 | E, F | 53–73 |
| UI Controls 2 | F | 63–73 |
| UI Controls 3 (Modifier Café) | E, I | 57–62, 88–94 |
| UI Controls 4 (state hoisting, dropdown) | C, I | 36–38, 95–101 |
| Three Screen Explorer | G, J | 74–79, 102–112 |
| MVVM | A, B | 1–28 |

Sections I and J go deeper on the two thinnest areas: the UI Controls 3/4 patterns, and
Three Screen Explorer — whose manual is missing from this folder, so it is covered both as
Navigation Compose and as Activities with Intents.

---

## A. Your app — Study Session Tracker

**1. Walk me through your app.**
Four files. `StudyState.kt` is the Model, a data class holding `sessionCount` and
`statusMessage`. `StudyViewModel.kt` holds that state and every function that changes it.
`StudyScreen.kt` is the View — it reads the state and calls ViewModel functions on click.
`MainActivity.kt` sets the content and shows the screen inside a Scaffold.

**2. Which part is the Model, which is the View, which is the ViewModel?**
Model = `StudyState` (data). View = `StudyScreen` (the composable UI). ViewModel =
`StudyViewModel` (state + logic).

**3. Show me where the state lives.**
In the ViewModel: `var state by mutableStateOf(StudyState())` with `private set`. The
`private set` is the important half — the screen can read it but cannot assign to it.

**4. Why `private set`?**
So all mutation goes through ViewModel functions. If the View could write to the state
directly, the separation MVVM is built on would be gone. (The manual's version does the
same thing with a private `_counterState` backing field and a public read-only
`State<CounterState>` — same intent, two ways of writing it.)

**5. How does the count stop at zero?**
`(state.sessionCount + delta).coerceAtLeast(0)`. Every button routes through one private
`changeCountBy(delta)`, so the guard exists in exactly one place. A plain `if (count > 0)`
would not be enough for "Remove 2 Sessions" — from a count of 1 it would produce −1.

**6. How does the status message stay correct?**
Same single function: `if (newCount == 0) "No sessions completed" else "Study progress
active"`. Because every operation goes through it, no button can leave the message out of
sync with the count.

**7. Why do the buttons not just do `count++`?**
That puts logic in the View. It breaks the separation, cannot be unit-tested without the
UI, and duplicates the clamping rule across four buttons.

**8. How does the Progress card know to update?**
It doesn't need to know. It reads `state.sessionCount` and `state.statusMessage`. Those
come from a `mutableStateOf`, so when the ViewModel replaces the state, Compose recomposes
every composable that read it. No manual refresh, no `findViewById`.

**9. How did you get the ViewModel into the screen?**
`viewModel: StudyViewModel = viewModel()` as a default parameter. `viewModel()` comes from
`androidx.lifecycle.viewmodel.compose` and needs the `lifecycle-viewmodel-compose`
dependency added to `libs.versions.toml` and `build.gradle.kts`.

**10. What would happen if you wrote `StudyViewModel()` instead?**
A brand-new ViewModel on every recomposition, so the count would reset constantly and
would not survive rotation. `viewModel()` returns the same instance tied to the lifecycle
owner.

**11. Rotate the emulator — what happens to the count, and why?**
It is retained. Rotation destroys and recreates the Activity (`onPause → onStop →
onDestroy → onCreate → onStart → onResume`) but the ViewModel is deliberately kept alive
across the configuration change. A value in plain `remember` would have reset to 0.

**12. How does the Toast work?**
`val context = LocalContext.current` inside the composable, then
`Toast.makeText(context, "...", Toast.LENGTH_SHORT).show()` in the button's `onClick`.
`.show()` is mandatory — without it nothing appears and there is no error.

**13. Why is the header a `Surface` and not just a `Text`?**
The requirement asked for a container with a distinct background colour. `Surface` gives a
themed background across the full width; the `Row` inside it puts the icon and title on one
line, centred vertically.

**14. How are the buttons arranged two-per-line?**
A `Row` with `Arrangement.spacedBy(12.dp)`, and each button carries `Modifier.weight(1f)`
so the pair splits the width equally. `weight` only works inside a Row or Column — it is
defined on their scope.

**15. Why `Button` for one and `OutlinedButton` for the other?**
Visual hierarchy. The filled button is the primary action of the pair (Complete, Add 2),
the outlined one is the counterpart. Both are Material 3 components.

**16. If I asked you to add "Add 5 Sessions" right now, what would you change?**
One function in the ViewModel — `fun addFiveSessions() = changeCountBy(5)` — and one
button in the screen. Nothing else, because the clamping and the message rule already live
inside `changeCountBy`.

---

## B. MVVM

**17. What does MVVM stand for and what does each part do?**
Model stores data, View displays the UI, ViewModel manages the data and the logic.

**18. State the MVVM rule in one sentence.**
The View displays information and reports user actions; the ViewModel manages the data and
the logic. The View never changes the value itself.

**19. Why use MVVM at all?**
Separation of code, easier maintenance (redesign the screen without touching the logic),
easier testing (ViewModel functions test with no UI), better organisation, and state that
survives rotation.

**20. What is a data class and why use one for the Model?**
A class whose job is to hold data. It groups related values, gives default values so
`StudyState()` is already valid, and Kotlin generates `copy()`, `equals()`, `toString()`
for free.

**21. What does `copy()` do?**
Creates a **new** object with some fields changed, leaving the original untouched.
`CounterState(count = 5).copy(count = 6)` gives a new object with 6; the old one still
says 5.

**22. Why does replacing the object matter instead of mutating it?**
Compose compares the old value against the new one to decide what to redraw. A new object
signals "this changed"; mutating fields in place can leave the UI stale.

**23. Why is the exposed state typed `State` and not `MutableState`?**
`State` has no setter, so the View can read but not write. Every mutation goes through a
ViewModel function.

**24. What is the backing-field pattern?**
`private val _counterState = mutableStateOf(...)` (mutable, private) alongside
`val counterState: State<CounterState> = _counterState` (read-only, public). The leading
underscore is the naming convention for the private backing property.

**25. Where does `viewModel()` come from?**
`androidx.lifecycle.viewmodel.compose.viewModel` — **not** `androidx.lifecycle`. It
requires the `lifecycle-viewmodel-compose` dependency.

**26. What exactly did you add to Gradle for MVVM?**
In `gradle/libs.versions.toml` under `[libraries]`:
`androidx-lifecycle-viewmodel-compose = { group = "androidx.lifecycle", name = "lifecycle-viewmodel-compose", version.ref = "lifecycleRuntimeKtx" }`
and in `app/build.gradle.kts`: `implementation(libs.androidx.lifecycle.viewmodel.compose)`.
Then Sync. Without it, `viewModel()` does not resolve.

**27. What does `val state by viewModel.counterState` do, and what import does it need?**
The `by` delegate unwraps `State<T>` so you write `state.count` rather than
`state.value.count`. It needs `androidx.compose.runtime.getValue`. Missing that import is
the most common error in this topic.

**28. Can the ViewModel touch the UI directly?**
No. It has no reference to any composable. It only owns state; Compose observes that state
and redraws. That is what makes the ViewModel testable on its own.

---

## C. State and recomposition

**29. What is state in Compose?**
The data a component holds at a given moment — a toggle's on/off, a text box's contents, a
list from a database. When it changes, the UI updates to reflect it.

**30. What is recomposition?**
Compose automatically re-running and redrawing the parts of the UI that read a state value
when that value changes. It replaces `findViewById` and manual UI updates.

**31. What does `mutableStateOf` do?**
Creates an observable value. Anything that reads it recomposes when it changes.

**32. What does `remember` do, and why is it needed?**
It preserves a value across recompositions. Without it the value would be recreated every
time the composable function re-runs, so it would never appear to change.

**33. `remember` vs `rememberSaveable`?**
`remember` survives recomposition but is wiped by a configuration change such as rotation,
because the Activity is destroyed and recreated. `rememberSaveable` survives rotation too,
by storing the value in the saved-instance Bundle.

**34. `rememberSaveable` vs a ViewModel — when do you use which?**
`rememberSaveable` for a small screen-local value (a text field, a checkbox).
A ViewModel when the state carries logic, is shared across composables, or you want it
testable.

**35. What are the three ways to write state, and which is preferred?**
`var count by remember { mutableStateOf(0) }` (needs `getValue` + `setValue`);
`val count = remember { mutableStateOf(0) }` then `count.value`;
`val (count, setCount) = remember { mutableStateOf(0) }`. Prefer the `by` form.

**36. What is state hoisting?**
Moving state up to the lowest common parent of everything that needs to read it. The
parent owns the value, passes it **down** as a parameter, and receives changes **up**
through a callback like `onOptionSelected: (String) -> Unit`.

**37. Give an example of what stays hoisted and what does not.**
In the dropdown example, `selectedOption` is hoisted to the parent because both the
dropdown and the button read it. `expanded` stays inside the dropdown because nothing else
cares about it.

**38. Why does a composable take `modifier: Modifier = Modifier` as a parameter?**
So callers can position and size your component without you knowing how. Take it as the
first optional parameter and apply it to your outermost element.

---

## D. Activities and lifecycle

**39. What is an Activity?**
One of the fundamental building blocks of an Android app: a single screen with a user
interface, like a window in a desktop app or a page in a web app.

**40. Name its four key characteristics.**
Single screen unit (manages its own window for drawing UI); independent components
(loosely coupled, one Activity does not directly talk to another); task participation
(Activities combine into "tasks"); entry points (declared in `AndroidManifest.xml`).

**41. Which class do you subclass in Compose?**
`ComponentActivity`, not the older `AppCompatActivity`.

**42. Name the seven lifecycle callbacks.**
`onCreate`, `onStart`, `onResume`, `onPause`, `onStop`, `onRestart`, `onDestroy`.

**43. Order when the app launches?**
`onCreate → onStart → onResume`.

**44. Press Home, then return. Which callbacks run?**
Going out: `onPause → onStop`. Coming back: `onRestart → onStart → onResume`.
`onCreate` does **not** run again.

**45. Press Back?**
`onPause → onStop → onDestroy`. The Activity is finished.

**46. Rotate the device?**
`onPause → onStop → onDestroy → onCreate → onStart → onResume` — destroyed and rebuilt
from scratch. That is exactly why `remember` loses its value and a ViewModel does not.

**47. Difference between `onStart` and `onResume`?**
After `onStart` the Activity is visible. After `onResume` it is in the foreground and
receiving input. A dialog on top of your app puts it back to paused-but-visible.

**48. Why must `onPause` be fast?**
The next Activity cannot resume until `onPause` returns, so slow work there makes the whole
transition stutter. Keep it to lightweight saves.

**49. What goes first in every callback override?**
`super.onX()`.

**50. How do you observe the lifecycle running?**
Put `println("onStart()")` in each callback, open Logcat, and filter on `System.out` —
`println` surfaces in Logcat tagged `System.out`, which is why the filter is not the app
name.

**51. Why would you keep the event log in a `companion object`?**
A companion object belongs to the class, not the instance, so the history survives the
Activity being destroyed and recreated. A normal property would be wiped on rotation along
with everything else.

**52. Does every Activity need to be in the manifest?**
Yes. Android resolves Intents through the manifest; an undeclared Activity throws
`ActivityNotFoundException` at runtime — not a compile error, which is why it is easy to
miss. Only the launcher Activity needs `exported="true"` plus the MAIN/LAUNCHER intent
filter.

---

## E. Layout and modifiers

**53. Name the three containers and what each does.**
`Column` stacks children vertically, `Row` places them side by side, `Box` layers them on
top of each other.

**54. Which parameter controls spacing in each?**
Column: `verticalArrangement` (main axis) and `horizontalAlignment` (cross axis).
Row: `horizontalArrangement` and `verticalAlignment`. Box: `contentAlignment` for both at
once. Mixing these up is the most common Compose mistake.

**55. Give some Arrangement values.**
`Center`, `Top`/`Start`, `Bottom`/`End`, `SpaceBetween`, `SpaceAround`, `SpaceEvenly`,
`spacedBy(16.dp)`.

**56. Why does Compose have no ConstraintLayout by default?**
Complex UIs are built by nesting Column, Row and Box instead, which keeps layouts easier to
read, debug and maintain.

**57. What is a Modifier?**
An object that changes how a composable looks and behaves — padding, size, background,
click handling, weight — chained as `Modifier.x().y()`.

**58. Does modifier order matter? Show it.**
Yes, they apply left to right. `Modifier.padding(8.dp).background(Color.Red)` puts the
padding **outside** the red; `Modifier.background(Color.Red).padding(8.dp)` puts it
**inside**.

**59. What does `.weight(1f)` do?**
Distributes available space proportionally inside a Row or Column. `weight(1f)` next to
`weight(2f)` splits the space one-third / two-thirds. It only exists inside Row/Column
scope.

**60. `dp` vs `sp`?**
`.sp` for font sizes (it scales with the user's font setting), `.dp` for everything else.

**61. What is `Modifier.fillMaxWidth(0.7f)`?**
70% of the available width.

**62. Difference between `Modifier` and `modifier`?**
Capital `Modifier` is the companion object you start a fresh chain with; lowercase
`modifier` is your function's parameter, which you apply to the outermost element.

---

## F. UI controls

**63. `TextField` vs `OutlinedTextField` vs `BasicTextField`?**
`TextField` is filled Material style; `OutlinedTextField` has a border and is preferred
when a screen has several fields; `BasicTextField` has no styling at all and leaves borders
and placeholders to you.

**64. Why does a disabled `OutlinedTextField` take an empty `onValueChange = {}`?**
It can never fire, because `enabled = false` prevents input — but the parameter is still
required.

**65. `Card` vs `Surface`?**
`Surface` is the base container that defines background colour, elevation and shape; Card
and Button are built on top of it. `Card` adds Material elevation and rounded corners for
grouping related information. A Card has no padding of its own — pad the content inside it.

**66. What are the button variants?**
`Button` (filled), `OutlinedButton` (border), `TextButton` (flat), `IconButton` (icon only,
circular touch target), and `FloatingActionButton` for a screen's single primary action.

**67. How do you put an icon and a label inside a Button?**
The trailing lambda is the button's content and is laid out as a Row, so it is just
`Icon(...)`, `Spacer(Modifier.width(8.dp))`, `Text("Click me")` as three children.

**68. How many FABs per screen?**
One, for the screen's single primary action.

**69. What must a DropdownMenu be anchored inside, and what is `onDismissRequest` for?**
Anchored inside a parent, normally a `Box`. `onDismissRequest` is what closes the menu when
the user taps outside it — it is required.

**70. What is a Spacer and why not use padding?**
An invisible gap, `Spacer(Modifier.height(16.dp))`. It is clearer than empty `Text("")` or
padding hacks, and it belongs to the layout rather than to a neighbouring component.

**71. Where does `Context` come from in a composable, and why can't a plain function read it?**
`val context = LocalContext.current`. `LocalContext` is a composition-local, so it can only
be read inside a composable. That is why a Toast helper takes the context as a parameter
and is a normal function, not a `@Composable`.

**72. What does `@Preview` do and what is its one restriction?**
Renders the composable in Android Studio's design view without running the app. The preview
function must take **no parameters** — supply any arguments inside it — and it should be
wrapped in your theme or the colours will be wrong.

**73. What is `Color(0xFF795548)`?**
An ARGB colour literal in `0xAARRGGBB` form. `0xFF` is fully opaque.

---

## G. Navigation between screens

**74. What are the four pieces of Navigation Compose?**
`rememberNavController()`, `NavHost(...)` with a `startDestination`, `composable("route") { }`
for each destination, and `navigate("route")` / `popBackStack()` to move.

**75. How do you pass an argument?**
Three steps that must agree: put `{name}` in the route, declare it in `arguments =
listOf(navArgument("name") { type = NavType.StringType })`, and read it with
`backStackEntry.arguments?.getString("name")`. Send it as `navigate("detail/Praneesh")`.

**76. What is the back stack?**
The history of screens. `navigate()` pushes, `popBackStack()` pops.
`popBackStack("home", inclusive = false)` returns to home and keeps home on the stack.

**77. Why `rememberNavController()` and not `NavController()`?**
Same reason as `viewModel()` — it survives recomposition and returns the same controller
each time.

**78. Navigation Compose vs Activities and Intents?**
NavHost: destinations are composables, declared in the NavHost, data via route arguments,
back via `popBackStack()`, and **no lifecycle callbacks fire** because there is only one
Activity. Intents: each screen is an Activity declared in the manifest, data via
`putExtra` / `getStringExtra`, back via `finish()`, and a **full lifecycle cycle runs on
every hop** — screen 1 goes through `onPause`/`onStop` while screen 2 runs
`onCreate`/`onStart`/`onResume`.

**79. Why keep routes in an object of constants?**
A mistyped route string is a runtime crash, not a compile error.

---

## H. Errors and gotchas they like to ask

**80. `Unresolved reference 'viewModel'` — cause?**
Missing `lifecycle-viewmodel-compose` dependency, or importing from `androidx.lifecycle`
instead of `androidx.lifecycle.viewmodel.compose`.

**81. `var x by remember { mutableStateOf(0) }` won't compile — why?**
Missing `androidx.compose.runtime.getValue` and `setValue` imports. (`import
androidx.compose.runtime.*` pulls in both, which is why the `by` form "just works" with the
wildcard.)

**82. `Unresolved reference 'MyAppTheme'` — why?**
The theme is named after your project, so a manual's `HelloWorldTheme` or
`CounterMVVM3Theme` will not exist in your project. Use the generated one.

**83. `@Composable invocations can only happen from the context of a @Composable function` — why?**
You called a composable from an ordinary function. Mark the caller `@Composable`, or move
the call inside one.

**84. Material vs Material3 — why does mixing them break things?**
`androidx.compose.material.*` is the older library. Mixing it with
`androidx.compose.material3.*` produces confusing type errors because they are different
types with the same names. Always Material 3 in this course.

**85. My value resets when I rotate. What happened and how do you fix it?**
Rotation destroyed and recreated the Activity, wiping `remember`. Fix with
`rememberSaveable` for a simple value, or a ViewModel when logic is involved.

**86. Toast doesn't appear and there's no error.**
`.show()` was left off `Toast.makeText(...)`.

**87. When do you need `@OptIn(ExperimentalMaterial3Api::class)`?**
Above a composable that uses an experimental Material 3 API, such as `TopAppBar`.

---

## I. UI Controls 3 and 4 — the manual patterns

### Modifier Café (UI Controls 3)

**88. What does the Modifier Café app demonstrate?**
Four things at once: state management with `remember`/`mutableStateOf`, layout composition
with Column/Row/Box, Material 3 components (Card, Surface, FAB), and the Modifier system
for styling and positioning.

**89. What three state variables does it hold?**
`coffeeSize` ("Medium"), `coffeeType` ("Latte") and `orderCount` (0) — all
`var ... by remember { mutableStateOf(...) }`.

**90. How does tapping the cup cycle the coffee type?**
`Modifier.clickable { }` on the Card, with a `when` that maps each value to the next:
Latte → Cappuccino → Espresso → back to Latte via `else`.

**91. How does a size button show that it is selected?**
`SizeOption` is a reusable composable that receives its own `size` and the current
`selectedSize`, compares them into `val isSelected = size == selectedSize`, then styles
itself: green container and white text when selected, grey and black when not, with higher
elevation (`4.dp` vs `1.dp`) for feedback.

**92. That is state hoisting in miniature — explain.**
`SizeOption` owns no selection state. The parent owns `coffeeSize`, passes the value down
as `selectedSize`, and gets the change back up through `onClick`. Three instances of the
same component stay in sync because they all read one parent value.

**93. How are the three size options made equal width?**
Each gets `Modifier.weight(1f)` inside a Row, with `Spacer(Modifier.width(8.dp))` between
them.

**94. What do `.systemBarsPadding()` and `.offset(x, y)` do in that app?**
`systemBarsPadding()` keeps content clear of the status and navigation bars.
`offset(x = 10.dp, y = 40.dp)` nudges a composable from its laid-out position — purely
visual, it does not affect the space reserved for it.

### Selection screen (UI Controls 4)

**95. What is the structure of the UI Controls 4 screen?**
`SelectionScreen` is the parent holding `selectedOption`; inside it are two custom
components, `OptionDropdown` and `SelectionActionButton`, with a Spacer between.

**96. Which state is hoisted and which is not, and why?**
`selectedOption` is hoisted to `SelectionScreen` because both the dropdown and the action
button need it. `expanded` stays inside `OptionDropdown` because only the dropdown cares
whether the menu is open.

**97. What are the signatures that make hoisting work?**
The child takes `selectedOption: String` (value down) and
`onOptionSelected: (String) -> Unit` (change up). The parent passes
`onOptionSelected = { selectedOption = it }`.

**98. Walk through what happens when a `DropdownMenuItem` is clicked.**
It calls `onOptionSelected(option)` to report the choice upward, sets `expanded = false` to
close the menu, and shows a toast confirming the selection.

**99. Why is the toast helper a normal function and not a `@Composable`?**
It takes `context: Context` as a parameter, so it can be called from inside an `onClick`
lambda — which is not a composable scope. A composable could not be called from there.

**100. Why does `OptionDropdown` need `Box` as its parent?**
A DropdownMenu must be anchored to a parent component so it knows where to appear.

**101. How do you preview a component that takes parameters?**
Supply them inside the preview function, which itself must take none:
`OptionDropdown(selectedOption = "F1", onOptionSelected = {})`, wrapped in your theme.

---

## J. Three Screen Explorer — extended

The manual for this topic is missing from the folder, so know both routes and, above all,
the difference between them (Q112).

### Navigation Compose

**102. Set up a three-screen app from scratch — what do you write?**
`val navController = rememberNavController()`, then a `NavHost(navController,
startDestination = "home")` containing `composable("home") { }`, `composable("detail") { }`
and `composable("summary") { }`.

**103. What dependency does it need?**
`androidx.navigation:navigation-compose` (2.7.7), added to `libs.versions.toml` and
`implementation(libs.androidx.navigation.compose)` in `build.gradle.kts`.

**104. Which imports come from where?**
`NavHost`, `composable` and `rememberNavController` are in `androidx.navigation.compose`;
`NavHostController`, `NavType` and `navArgument` are in `androidx.navigation`.

**105. How many Activities does a three-screen NavHost app have?**
One. All three destinations are composables inside the same Activity.

**106. So which lifecycle callbacks fire when you move from screen 1 to screen 2?**
None. There is only one Activity and it never leaves the foreground. This is the key
difference from the Intent approach.

**107. Pass two arguments between screens — show the three parts.**
Route `"summary/{name}/{topic}"`; `arguments = listOf(navArgument("name") { type =
NavType.StringType }, navArgument("topic") { type = NavType.StringType })`; read with
`backStackEntry.arguments?.getString("name") ?: "Unknown"`. Send with
`navigate("summary/Praneesh/UI-Controls")`.

**108. Which NavTypes exist?**
`StringType`, `IntType`, `BoolType`, `FloatType`, `LongType`.

**109. Difference between `popBackStack()` and `popBackStack("home", inclusive = false)`?**
The first goes back one screen. The second returns to `home`, clearing everything above it;
`inclusive = false` keeps `home` itself on the stack, `inclusive = true` would remove it
too.

**110. How do you navigate and clear the history at the same time?**
`navController.navigate("home") { popUpTo("login") { inclusive = true } }` — typical after
a login, so Back does not return to the login screen.

### Activities and Intents

**111. Move to a second Activity and carry data — show it.**
```kotlin
val intent = Intent(context, SecondActivity::class.java)
intent.putExtra("extra_name", "Praneesh")
context.startActivity(intent)
```
Read it on the other side with `intent.getStringExtra("extra_name") ?: "Guest"`. Go back
with `(LocalContext.current as? Activity)?.finish()`. Both Activities must be declared in
`AndroidManifest.xml`.

**112. Tabulate the two approaches.**

| | Navigation Compose | Activities + Intents |
|---|---|---|
| Screens are | composable destinations | separate Activities |
| Declared in | the `NavHost` | `AndroidManifest.xml` |
| Data passed via | route arguments | Intent extras |
| Back handled by | `popBackStack()` | `finish()` |
| Lifecycle callbacks | none fire — one Activity throughout | full cycle per hop |

The last row is the answer they are listening for. With Intents, launching screen 2 puts
screen 1 through `onPause` and `onStop` while screen 2 runs `onCreate`, `onStart`,
`onResume`.
