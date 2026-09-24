# UI Controls and Widgets

Covers **Android Application Notes 1**, **UI Controls 2**, **UI Controls 3**, **UI Controls 4**.

---

## Part 1 — The three containers

Everything in Compose is built by nesting these three. There is no ConstraintLayout by
default; you compose complex layouts out of simple pieces.

### Column — children stacked vertically

```kotlin
Column(
    modifier = Modifier
        .fillMaxSize()
        .padding(16.dp),
    verticalArrangement = Arrangement.Center,          // spacing along the main axis
    horizontalAlignment = Alignment.CenterHorizontally // alignment across it
) {
    Text("Username")
    Text("Password")
}
```

### Row — children side by side

```kotlin
Row(
    modifier = Modifier.fillMaxWidth(),
    horizontalArrangement = Arrangement.SpaceBetween,  // main axis
    verticalAlignment = Alignment.CenterVertically     // cross axis
) {
    Text("Cancel")
    Text("OK")
}
```

### Box — children layered on top of each other

```kotlin
Box(
    modifier = Modifier.fillMaxSize(),
    contentAlignment = Alignment.Center
) {
    Text("Loading...")
}
```

Use Box for overlays, backgrounds behind content, and centring one thing.

### The axis rule — get this right and the rest follows

| | main axis (arrangement) | cross axis (alignment) |
|---|---|---|
| **Column** | `verticalArrangement` | `horizontalAlignment` |
| **Row** | `horizontalArrangement` | `verticalAlignment` |
| **Box** | — | `contentAlignment` (both at once) |

Mixing these up is the single most common Compose mistake.

**Arrangement values:** `Center`, `Top`/`Start`, `Bottom`/`End`, `SpaceBetween`,
`SpaceAround`, `SpaceEvenly`, `spacedBy(16.dp)`.

**Alignment values:** `CenterHorizontally`/`CenterVertically`, `Start`/`End`, `Top`/`Bottom`.
For Box: `Alignment.Center`, `TopStart`, `BottomEnd`, `CenterStart`, and so on.

---

## Part 2 — State and recomposition

This is the concept the whole course rests on.

- **State** is the data a component holds right now — a toggle's on/off, a text box's
  contents, a list from a database.
- **Recomposition** is Compose automatically redrawing the parts of the UI that read a
  state value, when that value changes.
- **`mutableStateOf`** creates an observable value. Change it and anything reading it
  recomposes.
- **`remember`** preserves that value across recompositions. Without it, the value would be
  recreated every time the function re-runs.

```kotlin
var typedText by remember { mutableStateOf("") }

TextField(
    value = typedText,
    onValueChange = { newText -> typedText = newText }
)
Text("You typed: $typedText")
```

### The three ways to write it

```kotlin
var count by remember { mutableStateOf(0) }   // needs getValue + setValue imports
count = count + 1                             // read/write directly — cleanest

val count = remember { mutableStateOf(0) }    // no delegate
count.value = count.value + 1                 // must use .value

val (count, setCount) = remember { mutableStateOf(0) }  // destructured
setCount(count + 1)
```

Prefer the `by` form. It needs these two imports and they are easy to forget:

```kotlin
import androidx.compose.runtime.getValue
import androidx.compose.runtime.setValue
```

### remember vs rememberSaveable

- `remember` survives **recomposition**, but is wiped by a **configuration change**
  (rotation), because the Activity is destroyed and recreated.
- `rememberSaveable` survives rotation too, by writing the value into the saved-instance
  `Bundle`.

Verified: rotating an app whose screen state used plain `remember` reset that state;
switching to `rememberSaveable` fixed it.

For state that must also survive and carry logic, use a **ViewModel** — see the MVVM sheet.

### State hoisting — the UI Controls 4 lesson

A child composable should not own state that a parent needs to know about. Instead the
parent owns it, passes the value **down**, and receives changes **up** through a callback.

```kotlin
// PARENT owns the state
@Composable
fun SelectionScreen(modifier: Modifier = Modifier) {
    var selectedOption by remember { mutableStateOf("Select a Movie") }

    Column(modifier = modifier.fillMaxSize().padding(16.dp)) {
        OptionDropdown(
            selectedOption = selectedOption,           // value goes DOWN
            onOptionSelected = { selectedOption = it } // change comes UP
        )
        Spacer(modifier = Modifier.height(32.dp))
        SelectionActionButton(selectedOption = selectedOption)
    }
}

// CHILD owns nothing the parent cares about
@Composable
fun OptionDropdown(
    selectedOption: String,
    onOptionSelected: (String) -> Unit,
    modifier: Modifier = Modifier
) {
    var expanded by remember { mutableStateOf(false) }  // purely its own concern
    // ...
}
```

The rule: **state lives at the lowest common parent of everything that needs to read it.**
`expanded` stays inside the dropdown because nothing else cares. `selectedOption` is
hoisted because both the dropdown and the button read it.

---

## Part 3 — The controls

### Text

```kotlin
Text(
    text = "Welcome to my app!",
    fontSize = 24.sp,
    fontWeight = FontWeight.Bold,
    color = MaterialTheme.colorScheme.primary,
    modifier = Modifier.padding(bottom = 16.dp)
)
```

Sizes use `.sp` for text and `.dp` for everything else.

### Image

```kotlin
Image(
    painter = painterResource(id = R.drawable.myimage),
    contentDescription = "App logo",     // for screen readers; null if decorative
    modifier = Modifier.size(100.dp)
)
```

The drawable must exist in `res/drawable/` or `R.drawable.myimage` will not compile.

### TextField / OutlinedTextField / BasicTextField

```kotlin
var text by remember { mutableStateOf("") }

// Filled Material style
TextField(
    value = text,
    onValueChange = { text = it },
    label = { Text("Name") }
)

// Outlined border — preferred when a screen has several fields
OutlinedTextField(
    value = text,
    onValueChange = { text = it },
    label = { Text("Email") }
)

// No styling at all — you draw the border yourself
BasicTextField(
    value = text,
    onValueChange = { text = it }
)
```

A **disabled** field, as in UI Controls 2, takes an empty `onValueChange` because it can
never fire:

```kotlin
OutlinedTextField(
    value = "Enter your name here",
    onValueChange = {},
    label = { Text("Name") },
    enabled = false
)
```

### Button

```kotlin
Button(
    onClick = { Toast.makeText(context, "Button clicked!", Toast.LENGTH_SHORT).show() },
    modifier = Modifier.fillMaxWidth().height(56.dp),
    colors = ButtonDefaults.buttonColors(
        containerColor = MaterialTheme.colorScheme.primary,  // background
        contentColor   = MaterialTheme.colorScheme.onPrimary // text/icon
    )
) {
    Text("Click me")
}
```

The trailing lambda is the button's **content**, laid out as a Row. So an icon plus a
label is just two children with a Spacer between:

```kotlin
Button(onClick = { }) {
    Icon(
        painter = painterResource(id = R.drawable.myimage),
        contentDescription = "Icon",
        modifier = Modifier.size(24.dp)
    )
    Spacer(modifier = Modifier.width(8.dp))
    Text("Click me")
}
```

Variants: `Button` (filled), `OutlinedButton` (border), `TextButton` (flat),
`IconButton` (icon only, circular touch target).

### Icon

```kotlin
Icon(imageVector = Icons.Default.Star, contentDescription = "Star Icon")
Icon(imageVector = Icons.Filled.ShoppingCart, contentDescription = "Cart")
```

`Icons.Default` and `Icons.Filled` are the same set. Common ones: `Add`, `Delete`, `Edit`,
`Search`, `Share`, `Home`, `Close`, `Menu`, `Star`, `Person`, `Settings`, `Check`,
`ArrowDropDown`, `Favorite`, `ShoppingCart`.

Back arrows are auto-mirrored for right-to-left languages, so they live elsewhere:

```kotlin
Icon(Icons.AutoMirrored.Filled.ArrowBack, contentDescription = "Back")
```

`Icons.Default.*` needs `material-icons-core`; the wider set needs
`material-icons-extended`.

### Card

```kotlin
Card(
    modifier = Modifier.fillMaxWidth(),
    colors = CardDefaults.cardColors(containerColor = Color(0xFF795548)),
    elevation = CardDefaults.cardElevation(defaultElevation = 6.dp)
) {
    Text("Card Content", modifier = Modifier.padding(16.dp))
}
```

A Card has **no padding of its own** — pad the content inside it.

### Surface

```kotlin
Surface(
    modifier = Modifier.size(180.dp),
    shape = RoundedCornerShape(16.dp),
    tonalElevation = 16.dp,
    color = Color(0xFF8B4513)
) { /* content */ }
```

Surface is the base container that Card and Button are built on. Reach for it when you
want a themed background, elevation, or a shape.

### FloatingActionButton

```kotlin
FloatingActionButton(
    onClick = { orderCount++ },
    containerColor = Color(0xFF4CAF50),
    modifier = Modifier.size(70.dp)
) {
    Icon(Icons.Filled.ShoppingCart, contentDescription = "Place Order")
}
```

One FAB per screen, for the screen's single primary action.

### DropdownMenu

Must be anchored inside a parent — normally a `Box`.

```kotlin
var expanded by remember { mutableStateOf(false) }
val options = listOf("F1", "Jurassic World Rebirth", "Superman", "Fantastic Four")

Box(modifier = Modifier.fillMaxWidth()) {
    OutlinedButton(
        onClick = { expanded = true },
        modifier = Modifier.fillMaxWidth()
    ) {
        Text(text = selectedOption, modifier = Modifier.weight(1f))
        Icon(Icons.Default.ArrowDropDown, null)
    }

    DropdownMenu(
        expanded = expanded,
        onDismissRequest = { expanded = false },
        modifier = Modifier.fillMaxWidth()
    ) {
        options.forEach { option ->
            DropdownMenuItem(
                text = { Text(option) },
                onClick = {
                    onOptionSelected(option)
                    expanded = false
                    showToast(context, "Selected: $option")
                }
            )
        }
    }
}
```

`onDismissRequest` is required — it is what closes the menu when you tap outside.

### Spacer

```kotlin
Spacer(modifier = Modifier.height(16.dp))  // inside a Column
Spacer(modifier = Modifier.width(8.dp))    // inside a Row
```

An invisible gap. Better than empty `Text("")` or padding hacks.

### Toggles

```kotlin
Checkbox(checked = checked, onCheckedChange = { checked = it })
Switch(checked = switched, onCheckedChange = { switched = it })
RadioButton(selected = radio == "A", onClick = { radio = "A" })
Slider(value = slider, onValueChange = { slider = it })
```

---

## Part 4 — Modifiers

Modifiers change how a composable looks and behaves. They are passed as
`modifier = Modifier.x().y()`.

| Modifier | Effect |
|---|---|
| `.padding(16.dp)` | space around the composable |
| `.padding(horizontal = 8.dp)` | left and right only |
| `.padding(bottom = 16.dp)` | one side only |
| `.fillMaxSize()` | take all available space |
| `.fillMaxWidth()` / `.fillMaxHeight()` | one dimension |
| `.fillMaxWidth(0.7f)` | 70% of the width |
| `.size(100.dp)` | exact width and height |
| `.height(56.dp)` / `.width(140.dp)` | one dimension |
| `.background(Color.Gray)` | background colour or shape |
| `.clickable { }` | makes anything tappable |
| `.weight(1f)` | share space proportionally, inside Row/Column |
| `.offset(x = 10.dp, y = 40.dp)` | nudge position |
| `.systemBarsPadding()` | avoid the status and navigation bars |
| `.align(Alignment.CenterEnd)` | position inside a Box |
| `.border(1.dp, Color.Gray)` | outline |

### Order matters

```kotlin
Modifier.padding(8.dp).background(Color.Red)   // padding OUTSIDE the red
Modifier.background(Color.Red).padding(8.dp)   // padding INSIDE the red
```

Modifiers apply left to right. This catches people out constantly.

### weight

```kotlin
Row {
    Text("A", Modifier.weight(1f))  // takes 1/3
    Text("B", Modifier.weight(2f))  // takes 2/3
}
```

`weight` only works inside a Row or Column — it is defined on their scope.

### Always accept a modifier parameter

```kotlin
@Composable
fun MyThing(modifier: Modifier = Modifier) {
    Column(modifier = modifier) { /* ... */ }
}
```

Take `modifier` as the first optional parameter, default it to `Modifier`, and apply it to
your outermost element. This lets callers position your component without you knowing how.

---

## Part 5 — Context, Toast, Preview

### Context

```kotlin
val context = LocalContext.current
```

Needed for Toasts, resources, and system services. Grab it inside a composable —
`LocalContext` is a composition-local, so it cannot be read from a plain function.

### Toast

```kotlin
Toast.makeText(context, "Saved Successfully", Toast.LENGTH_SHORT).show()
```

`.show()` is mandatory. Without it nothing appears and there is no error. Lengths are
`LENGTH_SHORT` and `LENGTH_LONG`.

A helper is worth having:

```kotlin
private fun showToast(context: Context, message: String) {
    Toast.makeText(context, message, Toast.LENGTH_SHORT).show()
}
```

Note this is a **normal function, not `@Composable`** — it takes the context as a
parameter, so it can be called from an `onClick`.

### Preview

```kotlin
@Preview(showBackground = true, showSystemUi = true)
@Composable
fun MyScreenPreview() {
    MyAppTheme {
        MyScreen()
    }
}
```

A preview function must take **no parameters**. To preview a component that needs
arguments, supply them in the preview:

```kotlin
@Preview
@Composable
fun OptionDropdownPreview() {
    MyAppTheme {
        OptionDropdown(selectedOption = "F1", onOptionSelected = {})
    }
}
```

Wrap previews in your theme or the colours will be wrong.

---

## The Modifier Café pattern (UI Controls 3)

Worth remembering as a whole, because it exercises everything at once:

```kotlin
var coffeeSize  by remember { mutableStateOf("Medium") }
var coffeeType  by remember { mutableStateOf("Latte") }
var orderCount  by remember { mutableStateOf(0) }
```

- **Cycling a value on tap** — `when` mapping each value to the next:
  ```kotlin
  Card(modifier = Modifier.size(120.dp).clickable {
      coffeeType = when (coffeeType) {
          "Latte"      -> "Cappuccino"
          "Cappuccino" -> "Espresso"
          else         -> "Latte"
      }
  })
  ```
- **Selected-state feedback** — a reusable child that compares its own value to the
  selected one and styles itself:
  ```kotlin
  val isSelected = size == selectedSize
  containerColor  = if (isSelected) Color(0xFF4CAF50) else Color(0xFFE0E0E0)
  defaultElevation = if (isSelected) 4.dp else 1.dp
  ```
- **Equal-width options** — three children each with `Modifier.weight(1f)` and Spacers
  between them.
- **Custom colours** — `Color(0xFF795548)`, in `0xAARRGGBB` form. `0xFF` is fully opaque.
