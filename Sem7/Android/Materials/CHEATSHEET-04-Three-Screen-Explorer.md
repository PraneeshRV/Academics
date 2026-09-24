# Three Screen Explorer

> **The manual for this topic is missing from the Materials folder.** The other five PDFs
> are present; this one was never saved. So this sheet covers the topic **both ways**.
>
> Part 1 is **Navigation Compose** (`NavHost`) — for a Compose-based course this is almost
> certainly what was taught. **Learn this one properly.**
>
> Part 2 is **Activities and Intents** — the older approach, and the one that connects to
> the Activity Lifecycle topic. **Skim it**, and know the difference between the two.
>
> If you can get the actual manual from a classmate before the exam, do that and check it
> against this sheet.

---

# Part 1 — Navigation Compose (learn this)

## Setup

`gradle/libs.versions.toml`:

```toml
[versions]
navigationCompose = "2.7.7"

[libraries]
androidx-navigation-compose = { group = "androidx.navigation", name = "navigation-compose", version.ref = "navigationCompose" }
```

`app/build.gradle.kts`:

```kotlin
implementation(libs.androidx.navigation.compose)
```

Sync.

## The four pieces

1. `rememberNavController()` — the object that drives navigation
2. `NavHost(...)` — the container that swaps screens in and out
3. `composable("route") { }` — one destination
4. `navController.navigate("route")` / `popBackStack()` — moving

## Minimal three-screen app

```kotlin
@Composable
fun ThreeScreenExplorer(modifier: Modifier = Modifier) {
    val navController = rememberNavController()

    NavHost(
        navController = navController,
        startDestination = "home",
        modifier = modifier.fillMaxSize()
    ) {
        composable("home")    { HomeScreen(navController) }
        composable("detail")  { DetailScreen(navController) }
        composable("summary") { SummaryScreen(navController) }
    }
}
```

Moving between them:

```kotlin
Button(onClick = { navController.navigate("detail") }) { Text("Go to Screen 2") }
Button(onClick = { navController.popBackStack() })     { Text("Back") }
```

## Passing arguments

Three steps, and all three must agree.

**1. Declare a placeholder in the route**

```kotlin
composable(
    route = "detail/{name}",
    arguments = listOf(navArgument("name") { type = NavType.StringType })
) { backStackEntry ->
    val name = backStackEntry.arguments?.getString("name") ?: "Unknown"
    DetailScreen(navController, name)
}
```

**2. Send a real value**

```kotlin
navController.navigate("detail/Praneesh")
```

**3. Read it in the destination** — the `backStackEntry.arguments?.getString(...)` line above.

Types: `NavType.StringType`, `IntType`, `BoolType`, `FloatType`, `LongType`.

### Two arguments

```kotlin
composable(
    route = "summary/{name}/{topic}",
    arguments = listOf(
        navArgument("name")  { type = NavType.StringType },
        navArgument("topic") { type = NavType.StringType }
    )
) { backStackEntry ->
    val name  = backStackEntry.arguments?.getString("name")  ?: "Unknown"
    val topic = backStackEntry.arguments?.getString("topic") ?: "Unknown"
    SummaryScreen(navController, name, topic)
}
```

```kotlin
navController.navigate("summary/Praneesh/UI-Controls")
```

### Keep routes in one place

Building route strings by hand invites typos, and a typo is a **runtime crash**, not a
compile error. Centralise them:

```kotlin
object Routes {
    const val HOME    = "home"
    const val DETAIL  = "detail/{name}"
    const val SUMMARY = "summary/{name}/{topic}"

    fun detail(name: String) = "detail/$name"
    fun summary(name: String, topic: String) = "summary/$name/$topic"
}
```

Then `navController.navigate(Routes.detail(name))`.

## The back stack

`navigate()` pushes a screen on top. `popBackStack()` pops one off.

```kotlin
navController.popBackStack()                          // back one screen
navController.popBackStack("home", inclusive = false) // back to home, clearing above it
```

`inclusive = false` keeps `home` itself on the stack. `inclusive = true` would remove
`home` as well — usually not what you want.

To navigate and clear history at the same time (e.g. after login):

```kotlin
navController.navigate("home") {
    popUpTo("login") { inclusive = true }
}
```

## Full working example

```kotlin
// ---------- SCREEN 1 ----------
@Composable
fun HomeScreen(navController: NavHostController) {
    var name by remember { mutableStateOf("") }

    Column(
        modifier = Modifier.fillMaxSize().padding(24.dp),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text("Screen 1 - Home", fontSize = 26.sp, fontWeight = FontWeight.Bold)
        Spacer(modifier = Modifier.height(24.dp))

        OutlinedTextField(
            value = name,
            onValueChange = { name = it },
            label = { Text("Your name") },
            modifier = Modifier.fillMaxWidth()
        )

        Spacer(modifier = Modifier.height(16.dp))

        Button(
            onClick = { navController.navigate(Routes.detail(name.ifBlank { "Guest" })) },
            modifier = Modifier.fillMaxWidth()
        ) {
            Text("Go to Screen 2")
        }
    }
}

// ---------- SCREEN 2 ----------
@Composable
fun DetailScreen(navController: NavHostController, name: String) {
    Column(
        modifier = Modifier.fillMaxSize().padding(24.dp),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text("Screen 2 - Detail", fontSize = 26.sp, fontWeight = FontWeight.Bold)
        Text("Received from screen 1:")
        Text(name, fontSize = 24.sp, fontWeight = FontWeight.Bold)

        Spacer(modifier = Modifier.height(24.dp))

        listOf("Lifecycle", "UI-Controls", "MVVM").forEach { topic ->
            Button(
                onClick = { navController.navigate(Routes.summary(name, topic)) },
                modifier = Modifier.fillMaxWidth().padding(vertical = 4.dp)
            ) { Text(topic) }
        }

        OutlinedButton(
            onClick = { navController.popBackStack() },
            modifier = Modifier.fillMaxWidth()
        ) { Text("Back to Screen 1") }
    }
}

// ---------- SCREEN 3 ----------
@Composable
fun SummaryScreen(navController: NavHostController, name: String, topic: String) {
    Column(
        modifier = Modifier.fillMaxSize().padding(24.dp),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text("Screen 3 - Summary", fontSize = 26.sp, fontWeight = FontWeight.Bold)

        Card(modifier = Modifier.fillMaxWidth()) {
            Column(modifier = Modifier.padding(16.dp)) {
                Text("Name");  Text(name,  fontSize = 20.sp, fontWeight = FontWeight.Bold)
                Text("Topic"); Text(topic, fontSize = 20.sp, fontWeight = FontWeight.Bold)
            }
        }

        Spacer(modifier = Modifier.height(24.dp))

        OutlinedButton(onClick = { navController.popBackStack() }) {
            Text("Back one screen")
        }
        Button(onClick = { navController.popBackStack(Routes.HOME, inclusive = false) }) {
            Text("Back to Screen 1")
        }
    }
}
```

Verified on the emulator: typing "Praneesh" on screen 1 and choosing "UI-Controls" on
screen 2 shows both values on screen 3, and "Back to Screen 1" returns to Home.

---

# Part 2 — Activities and Intents (skim this)

Each screen is its own Activity, declared in the manifest, and you move with an Intent.

## Declare the Activities

```xml
<activity android:name=".SecondActivity" android:exported="false" />
<activity android:name=".ThirdActivity"  android:exported="false" />
```

Miss this and you get `ActivityNotFoundException` at runtime — no compile error.

## Move to another Activity

```kotlin
val context = LocalContext.current

Button(onClick = {
    val intent = Intent(context, SecondActivity::class.java)
    intent.putExtra("extra_name", "Praneesh")   // attach data
    context.startActivity(intent)
}) {
    Text("Go to Second Activity")
}
```

## Read the data on the other side

```kotlin
class SecondActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val name = intent.getStringExtra("extra_name") ?: "Guest"

        setContent {
            MyAppTheme {
                Scaffold { padding ->
                    SecondScreen(name = name, modifier = Modifier.padding(padding))
                }
            }
        }
    }
}
```

`intent` is a property of the Activity. Getters: `getStringExtra`, `getIntExtra(key, default)`,
`getBooleanExtra(key, default)`.

## Go back

```kotlin
val activity = LocalContext.current as? Activity
OutlinedButton(onClick = { activity?.finish() }) { Text("Back") }
```

`finish()` destroys the current Activity and returns to the one beneath.

> Note: newer Compose has `LocalActivity.current`, but it needs
> `activity-compose` 1.9+. The `LocalContext.current as? Activity` cast works on every
> version — use it unless you know your version is new enough. (This exact issue broke the
> reference build on `activity-compose` 1.8.0.)

## Keys as constants

```kotlin
const val EXTRA_NAME = "extra_name"
```

A mistyped key silently returns null rather than failing loudly.

---

## The difference — likely exam question

| | Navigation Compose | Activities + Intents |
|---|---|---|
| Screens are | composable destinations | separate Activities |
| Declared in | the `NavHost` | `AndroidManifest.xml` |
| Data passed via | route arguments | Intent extras |
| Back handled by | `popBackStack()` | `finish()` |
| Lifecycle callbacks | **none fire** — one Activity throughout | **full cycle per hop** |

That last row is the key insight. With `NavHost` there is only **one** Activity, so moving
between screens fires no lifecycle callbacks at all. With Intents, launching screen 2 puts
screen 1 through `onPause` and `onStop`, while screen 2 runs `onCreate`, `onStart`,
`onResume`.

---

## Likely exam questions

**"How do you pass data between screens?"** — NavHost: put a `{placeholder}` in the route,
declare it in `arguments`, read it from `backStackEntry.arguments`. Intents:
`putExtra` on the way out, `intent.getStringExtra` on the way in.

**"What is the back stack?"** — the history of screens. `navigate()` pushes,
`popBackStack()` pops.

**"Why `rememberNavController()` rather than `NavController()`?"** — the same reason as
`viewModel()`: it survives recomposition and returns the same controller each time.

**"Why must every Activity be in the manifest?"** — Android resolves Intents through the
manifest; an undeclared Activity cannot be started and throws at runtime.
