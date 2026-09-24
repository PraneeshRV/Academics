# Activities and their Lifecycle

## What an Activity is

An Activity is **one screen with a user interface** — the Android equivalent of a window
in a desktop app or a page in a web app.

Four properties the manual calls out:

- **Single screen unit** — each Activity manages its own window for drawing UI.
- **Independent components** — Activities are loosely coupled. One Activity does not
  directly talk to another.
- **Task participation** — Activities combine into "tasks" to form a coherent experience.
- **Entry points** — they are declared in `AndroidManifest.xml` as ways into your app.

In Compose you subclass `ComponentActivity` (not the older `AppCompatActivity`).

---

## The seven callbacks

```kotlin
class MainActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)      // ALWAYS call super first
        println("onCreate")
        enableEdgeToEdge()
        setContent {
            MyAppTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Greeting(
                        name = "World",
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }
    }

    override fun onStart()   { super.onStart();   println("onStart()") }
    override fun onResume()  { super.onResume();  println("onResume()") }
    override fun onPause()   { super.onPause();   println("onPause()") }
    override fun onStop()    { super.onStop();    println("onStop()") }
    override fun onRestart() { super.onRestart(); println("onRestart()") }
    override fun onDestroy() { super.onDestroy(); println("onDestroy()") }
}
```

`super.onX()` goes **first** in every one of them.

---

## What each callback means

| Callback | Fires when | Typical use |
|---|---|---|
| `onCreate` | Activity is created, once per instance | build the UI, `setContent` |
| `onStart` | becoming visible | start things the user must see |
| `onResume` | now in the foreground, accepting input | resume animation, camera, sensors |
| `onPause` | losing focus, still partly visible | pause, save lightweight state — keep it fast |
| `onStop` | no longer visible | release heavy resources |
| `onRestart` | coming back after `onStop` (never after `onCreate`) | re-acquire what `onStop` released |
| `onDestroy` | being destroyed for good, or recreated | final cleanup |

---

## The sequences — memorise these

**Launch the app**
```
onCreate → onStart → onResume
```

**Press Home (app goes to background)**
```
onPause → onStop
```

**Return to the app**
```
onRestart → onStart → onResume
```
Note: `onCreate` does **not** run again. This is the classic exam question.

**Press Back (app is finished)**
```
onPause → onStop → onDestroy
```

**Rotate the device**
```
onPause → onStop → onDestroy → onCreate → onStart → onResume
```
The Activity is destroyed and rebuilt from scratch. This is why a value held in
`remember` is lost on rotation but a `ViewModel` survives — see the MVVM sheet.

All five sequences above were verified on the emulator; the rotation one produces
exactly those six callbacks in that order.

---

## Watching it happen

1. Add `println(...)` to each callback, as above.
2. Open **Logcat** at the bottom of Android Studio.
3. In the filter box type `System.out`.
4. Interact with the app: press Home, come back, rotate, press Back.

`println` in Android shows up in Logcat tagged `System.out` at level `I`. That is why the
filter is `System.out` and not the app name.

### If Logcat is noisy

Filter more precisely:

```
tag:System.out
```

or filter by package:

```
package:mine tag:System.out
```

---

## A trick worth knowing

If you want the sequence visible **on screen** instead of hunting through Logcat, keep the
event list in a `companion object` so it survives the Activity being destroyed and
recreated:

```kotlin
class LifecycleActivity : ComponentActivity() {

    companion object {
        val events = mutableStateListOf<String>()
        fun log(name: String) {
            events.add(0, name)   // newest first
            println(name)
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        log("onCreate()")
        setContent { MyAppTheme { EventList() } }
    }

    override fun onStart() { super.onStart(); log("onStart()") }
    // ...and so on
}
```

A normal property would be wiped on rotation along with the Activity. A `companion object`
belongs to the class, not the instance, so it keeps the history and you can watch the
destroy-and-recreate happen live.

---

## Declaring a second Activity

Any Activity beyond the launcher must be declared in `AndroidManifest.xml`:

```xml
<activity
    android:name=".lifecycle.LifecycleActivity"
    android:exported="false"
    android:label="Lifecycle Demo" />
```

- `android:name` — the class, with a leading dot for a path relative to your package.
- `android:exported="false"` — other apps cannot launch it. Correct default for internal
  screens. Only the launcher Activity needs `exported="true"` plus the `MAIN` /
  `LAUNCHER` intent filter.

Forgetting to declare an Activity gives you `ActivityNotFoundException` at runtime, not a
compile error — so it is easy to miss.

---

## Likely exam questions

**"What is an Activity?"** — a single screen with a UI; a fundamental building block;
declared in the manifest; manages its own window.

**"Give the order of callbacks when the app starts."** — `onCreate`, `onStart`, `onResume`.

**"You press Home and come back. Which callbacks run?"** — `onPause`, `onStop`, then
`onRestart`, `onStart`, `onResume`. Emphasise that `onCreate` does *not* re-run.

**"What happens on rotation, and why is that a problem?"** — the Activity is destroyed and
recreated, so anything held in `remember` or a plain field is lost. Solve it with a
`ViewModel` (survives configuration changes) or `rememberSaveable`.

**"Difference between `onStart` and `onResume`?"** — after `onStart` the Activity is
visible; after `onResume` it is in the foreground and receiving input. A dialog over your
app puts it back to paused-but-visible.

**"Why must `onPause` be fast?"** — the next Activity cannot resume until `onPause`
returns, so slow work there makes the whole transition stutter.
